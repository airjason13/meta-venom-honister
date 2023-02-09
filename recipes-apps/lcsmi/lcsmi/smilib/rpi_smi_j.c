#include "rpi_smi_j.h"

//rpi4 register base address
#define RPI4_REG_PHY_ADDR 	0xfe000000
	
#define RPI4_GPIO_OFFSET	0x00200000
#define RPI4_DMA_OFFSET		0x00007000
#define RPI4_SMI_OFFSET		0x00600000
#define RPI4_CLK_OFFSET		0x00101000

#define SHOW_DEBUG_MEM	false//true

#define SMI_TIMING 	10, 15, 30, 15
//#define SMI_TIMING 	12, 19, 34, 19

#define LED_D0_PIN	8
#define LED_NCHANS	8
#define LED_NBITS	24
#define LED_PREBITS	4
#define LED_POSTBITS	4
#define BIT_NPULSES	3	//how many pulses in one bit
#define CHAN_MAXLEDS	1000
#define CHASE_MSEC	100
#define REQUEST_THRESH	2
#define DMA_CHAN	6//10	//DMA channel to use?? 7~15 DMA CHAN is DMA lite(64k only)

int chan_ledcount= 960;
int rgb_data[CHAN_MAXLEDS][LED_NCHANS];

// DMA channels and data requests
#define DMA_CHAN_A		10
#define DMA_CHAN_B		11
#define DMA_PWM_DREQ		5
#define DMA_SPI_TX_DREQ		6
#define DMA_SPI_RX_DREQ		7
#define DMA_BASE		(PHY_REG_BASE + 0x007000)
#define DMA_CS			0x00
#define DMA_CONBLK_AD		0x04
#define DMA_TI			0x08
#define DMA_SRCE_AD		0x0c
#define DMA_DEST_AD		0x10
#define DMA_TXFR_LEN		0x14
#define DMA_STRIDE		0x18
#define DMA_NEXTCONBK		0x1C
#define DMA_DEBUG		0x20
#define DMA_REG(ch, r)		((r)==DMA_ENABLE ? DMA_ENABLE : (ch)*0x100+(r))
#define DMA_ENABLE		0xff0

//DMA register values
/*#define DMA_WAIT_RESP		(1 << 3)
#define DMA_CB_DEST_INC		(1 << 4)
#define DMA_DEST_DREQ		(1 << 6)
#define DMA_CB_SRCE_INC		(1 << 8)*/


int on_rgbs[16] = { 0xff0000, 0x00ff00, 0x0000ff, 0xffffff,
		    0xff4040, 0x40ff40, 0x4040ff, 0x404040, 
		    0xff0000, 0x00ff00, 0x0000ff, 0xffffff,
		    0xff4040, 0x40ff40, 0x4040ff, 0x404040
			};
int off_rgbs[16];

#define CLK_PASSWD	0x5a000000

#define BUS_REG_BASE	0x7e000000

#define PAGE_SIZE	0x1000

#define REQUEST_THRESH	2


#define GPIO_IN		0	
#define GPIO_ALT1	5	

#define PAGE_ROUNDUP(n)	((n)%PAGE_SIZE==0 ? (n) : ((n)+PAGE_SIZE)&~(PAGE_SIZE-1))

#define REG8(m, x)	((volatile unsigned char *)((unsigned int)(m.virt)+(unsigned int)(x)))
//#define REG32(m, x)	((volatile unsigned int *)((unsigned int)(m.virt)+(unsigned int)(x)))
#define REG32(m, x)	((volatile unsigned int *)(m.virt+x))

//typedef struct {
//	int fd, h, size;
//	void *bus, *virt, *phys;
//} MEM_MAP;


MEM_MAP gpio_regs, dma_regs, clk_regs, pwm_regs, smi_regs, kclk_regs, vc_mem;



#define LED_DLEN		(LED_NBITS * BIT_NPULSES)  //24*3

#if LED_NCHANS > 8
#define TXDATA_T		unsigned short
#else
#define TXDATA_T		unsigned char
#endif

#define LED_TX_OSET(n) 		(LED_PREBITS + (LED_DLEN * (n)))  // 4 + (24*3)*n 

#define TX_BUFF_LEN(n) 		(LED_TX_OSET(n) + LED_POSTBITS)   // 4 + (24*3)*n + 4
#define TX_BUFF_SIZE(n)		(TX_BUFF_LEN(n) * sizeof(TXDATA_T))  

#define VC_MEM_SIZE		(PAGE_SIZE + TX_BUFF_SIZE(CHAN_MAXLEDS))

volatile SMI_CS_REG *smi_cs;
volatile SMI_L_REG *smi_l;
volatile SMI_A_REG *smi_a;
volatile SMI_D_REG *smi_d;
volatile SMI_DMC_REG *smi_dmc;
volatile SMI_DSR_REG *smi_dsr;
volatile SMI_DSW_REG *smi_dsw;
volatile SMI_DCS_REG *smi_dcs;
volatile SMI_DCA_REG *smi_dca;
volatile SMI_DCD_REG *smi_dcd;

#define TX_TEST		0//1

#if TX_TEST
#define tx_test_len 23040*3//16384//8192
//TXDATA_T tx_test_data[] = {1, 2, 3, 4, 5, 6, 7, 0};
//TXDATA_T tx_test_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0x55};
//TXDATA_T tx_test_data[] = {0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77};
//TXDATA_T tx_test_data[] = {0xff, 0xfe, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8};
TXDATA_T tx_zero_data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
TXDATA_T tx_test_data[tx_test_len];
#endif


TXDATA_T *txdata;
TXDATA_T tx_buffer[TX_BUFF_LEN(CHAN_MAXLEDS)];


void rgb_txdata(int *rgbs, TXDATA_T *txd){
	int i, n, msk;
	for (n=0; n<LED_NBITS; n++){
		msk = n==0? 0x8000: n==8 ? 0x800000 : n==16 ? 0x80 : msk>>1;
		txd[0] = (TXDATA_T)0xffff;
		txd[1] = txd[2] = 0;
		for (i = 0; i < LED_NCHANS; i++){
			if(rgbs[i] & msk){
				txd[1] |= (1<<i);
			}
		}
		txd += BIT_NPULSES;
	}
}


void *map_segment(void *addr, int size){
	int fd;
	void *mem;
	size = PAGE_ROUNDUP(size);

	if ((fd = open("/dev/mem", O_RDWR|O_SYNC|O_CLOEXEC)) < 0){
		printf("Error: can't open /dev/mem!\n");
	}
	mem = mmap(0, size, PROT_WRITE|PROT_READ, MAP_SHARED, fd, (unsigned int)addr);
	//printf("Map %p --> %p\n", (void *)addr, mem);
	//printf("*(unsigned int*)mem = %08x\n", *(unsigned int*)mem);
	if (mem == MAP_FAILED){
		printf("Error, can't map memory!\n");
	}
	return mem;
}

void unmap_segment(void *mem, int size){
	if(mem){
		munmap(mem, PAGE_ROUNDUP(size));
	}
}

void *map_periph(MEM_MAP *mp, void *phys, int size){
	mp->phys = phys;
	mp->size = PAGE_ROUNDUP(size);
	mp->bus = (void *)((uint32_t)phys - RPI4_REG_PHY_ADDR + BUS_REG_BASE);
	mp->virt = map_segment(phys, mp->size);
	return (mp->virt);
}


void unmap_periph_mem(MEM_MAP *mp){
	if(mp){
		if(mp->fd){
			unmap_segment(mp->virt, mp->size);
			unlock_vc_mem(mp->fd, mp->h);
			free_vc_mem(mp->fd, mp->h);
			close_mbox(mp->fd);
		}else{
			unmap_segment(mp->virt, mp->size);
			
		}

	}
}

unsigned int* get_periph_virt_addr_by_mmap(unsigned int periph_phy_addr){
	//1.get /dev/mem fd first
	int mem_fd = open("/dev/mem", O_RDWR);
	if(mem_fd < 0){
		printf("Error:%d opening /dev/mem\n", mem_fd);
		return NULL;
	}
	unsigned int *periph_virt_addr = (unsigned int*)mmap(0, 4096, PROT_READ, MAP_SHARED, mem_fd, periph_phy_addr );
	close(mem_fd);
	//printf("periph_virt_addr = %p\n", periph_virt_addr);
	if(periph_virt_addr == MAP_FAILED){
		printf("Error on mmap failed!\n");
		return NULL;
	}
	return periph_virt_addr;
}



int test_mmap_gpio_regs(int argc, char* argv[]){
	unsigned int gpio_phy_addr = RPI4_REG_PHY_ADDR + RPI4_GPIO_OFFSET;
	unsigned int *gpio_virt_addr = get_periph_virt_addr_by_mmap(gpio_phy_addr);

	if(SHOW_DEBUG_MEM){
		for(int i = 0; i < 6; i ++){
			printf("@%x:%08x\n", gpio_phy_addr+i*4, gpio_virt_addr[i]);
		}
	}

	return 0;
}


int map_devices(void){
	unsigned int gpio_phy_addr = RPI4_REG_PHY_ADDR + RPI4_GPIO_OFFSET;	
	map_periph(&gpio_regs, (void *)gpio_phy_addr, PAGE_SIZE);
	unsigned int dma_phy_addr = RPI4_REG_PHY_ADDR + RPI4_DMA_OFFSET;	
	map_periph(&dma_regs, (void *)dma_phy_addr, PAGE_SIZE);
	unsigned int clk_phy_addr = RPI4_REG_PHY_ADDR + RPI4_CLK_OFFSET;	
	map_periph(&kclk_regs, (void *)clk_phy_addr, PAGE_SIZE);
	unsigned int smi_phy_addr = RPI4_REG_PHY_ADDR + RPI4_SMI_OFFSET;	
	map_periph(&smi_regs, (void *)smi_phy_addr, PAGE_SIZE);


	
	return 0;
}

void enable_dma(int chan){
	*REG32(dma_regs, DMA_ENABLE) |= (1 << chan);
	*REG32(dma_regs, DMA_REG(chan, DMA_CS)) = 1 << 31;
}


void gpio_mode(int pin, int mode){
	volatile unsigned int *reg = REG32(gpio_regs, 0) + pin /10, shift = (pin % 10) *3;
	*reg = (*reg & ~(7 << shift)) | (mode << shift);
}

//
void init_smi(int width, int ns, int setup, int strobe, int hold){
	int i, divi = ns/2;

	smi_cs = (SMI_CS_REG *)REG32(smi_regs, SMI_CS);
	smi_l  = (SMI_L_REG *)REG32(smi_regs, SMI_L);
	smi_a  = (SMI_A_REG *)REG32(smi_regs, SMI_A);
	smi_d  = (SMI_D_REG *)REG32(smi_regs, SMI_D);
	smi_dmc  = (SMI_DMC_REG *)REG32(smi_regs, SMI_DMC);
	smi_dsr  = (SMI_DSR_REG *)REG32(smi_regs, SMI_DSR0);
	smi_dsw  = (SMI_DSW_REG *)REG32(smi_regs, SMI_DSW0);
	smi_dcs  = (SMI_DCS_REG *)REG32(smi_regs, SMI_DCS);
	smi_dca  = (SMI_DCA_REG *)REG32(smi_regs, SMI_DCA);
	smi_dcd  = (SMI_DCD_REG *)REG32(smi_regs, SMI_DCD);
	//printf("smi_cs->value = %8x\n", smi_cs->value);
	smi_cs->value = smi_l->value = smi_a->value = 0;
	smi_dsr->value = smi_dsw->value = smi_dcs->value = smi_dca->value = 0;
	//printf("smi_l->value = %8x\n", smi_l->value);	
	if (*REG32(kclk_regs, CLK_SMI_DIV) != divi << 12){
		*REG32(kclk_regs, CLK_SMI_CTL) = CLK_PASSWD | (1 << 5);
		usleep(10);
		while (*REG32(kclk_regs, CLK_SMI_CTL) & (1 << 7));
		usleep(10);
		*REG32(kclk_regs, CLK_SMI_DIV) = CLK_PASSWD | (divi << 12);
		usleep(10);
		*REG32(kclk_regs, CLK_SMI_CTL) = CLK_PASSWD | 6 | (1 << 4);
		usleep(10);
		while((*REG32(kclk_regs, CLK_SMI_CTL) & (1 << 7)) == 0);
		usleep(10);
	}
	if (smi_cs->seterr){
		smi_cs->seterr = 1;
	}
	smi_dsr->rsetup = smi_dsw->wsetup = setup;
	smi_dsr->rstrobe = smi_dsw->wstrobe = strobe;
	smi_dsr->rhold = smi_dsw->whold = hold;
	smi_dmc->panicr = smi_dmc->panicw = 8;
	smi_dmc->reqr = smi_dmc->reqw = REQUEST_THRESH;
	smi_dsr->rwidth = smi_dsw->wwidth = width;
}

void set_gpio_smi_mode(void){
	//set gpio to alt1 mode	
	for(int i = 0; i < LED_NCHANS; i++){
		gpio_mode(LED_D0_PIN+i, GPIO_ALT1);
	}
	usleep(1000);

	//printf("smi cs addr = %08x\n", REG32(smi_regs, SMI_L));
	//printf("smi cs value = %08x\n", *REG32(smi_regs, SMI_L));

}

void setup_smi_dma(MEM_MAP *mp, int nsamp){
	//unsigned int test_len = 0x10000;
	//printf("setup_smi_dma!\n");
	//printf("mp->virt = %08x\n", mp->virt);
	DMA_CB *cbs=mp->virt;
	txdata = (TXDATA_T *)(cbs + 1);
	smi_dmc->dmaen = 1;
	smi_cs->enable = 1;
	smi_cs->clear = 1;
	smi_cs->pxldat = 1;
	smi_l->len = nsamp*sizeof(TXDATA_T);
	//smi_l->len = test_len;//nsamp*sizeof(TXDATA_T);
	printf("smi_l->len = 0x%08x\n", smi_l->len);
	smi_cs->write = 1;
	//printf("enable dma!\n");
	enable_dma(DMA_CHAN);
	//printf("enable dma ok!\n");
	//printf("mp->virt = %p\n", mp->virt);
	//printf("mp->phys = %p\n", mp->phys);
	//printf("mp->bus = %p\n", mp->bus);
#if 0
	for(int i = 0; i < 6; i ++){
		printf("mp->virt @%x:%08x\n", (unsigned int*)mp->virt +i*4, *(unsigned int *)(mp->virt + 4*i));
	}
	printf("ti : %08x\n", DMA_DEST_DREQ | (DMA_SMI_DREQ << 16) | DMA_CB_SRCE_INC | DMA_WAIT_RESP);
	*(unsigned long*)mp->virt = DMA_DEST_DREQ | (DMA_SMI_DREQ << 16) | DMA_CB_SRCE_INC | DMA_WAIT_RESP;
	//cbs[0].tfr_len = nsamp * sizeof(TXDATA_T);
	//cbs[0].srce_ad = MEM_BUS_ADDR(mp, txdata);
	//cbs[0].dest_ad = REG_BUS_ADDR(smi_regs, SMI_D);
#else
	//cbs[0].ti = DMA_DEST_DREQ | (DMA_SMI_DREQ << 16) | DMA_CB_SRCE_INC | DMA_WAIT_RESP;
	cbs[0].ti = DMA_DEST_DREQ | (DMA_SMI_DREQ << 16) | DMA_CB_SRCE_INC ;
	cbs[0].tfr_len = nsamp * sizeof(TXDATA_T);
	//cbs[0].tfr_len = nsamp * sizeof(TXDATA_T) + 4;
	//cbs[0].tfr_len = test_len;//nsamp * sizeof(TXDATA_T);
	cbs[0].srce_ad = MEM_BUS_ADDR(mp, txdata);
	cbs[0].dest_ad = REG_BUS_ADDR(smi_regs, SMI_D);
#endif	
	//printf("end of setup smi dma!\n");
}

void start_dma(MEM_MAP *mp, int chan, DMA_CB *cbp, unsigned int csval){
	*REG32(dma_regs, DMA_REG(chan, DMA_CONBLK_AD)) = MEM_BUS_ADDR(mp, cbp);
	*REG32(dma_regs, DMA_REG(chan, DMA_CS)) = 2;
	*REG32(dma_regs, DMA_REG(chan, DMA_DEBUG)) = 7;
	*REG32(dma_regs, DMA_REG(chan, DMA_CS)) = 1 | csval;
}

void stop_dma(int chan){
	if (dma_regs.virt){
		//printf("stop_dmai\n");
		*REG32(dma_regs, DMA_REG(chan, DMA_CS)) = 1 << 31;
	}
}

void rpi_start_dma(MEM_MAP *mp){
	DMA_CB *cbs = mp->virt;
	start_dma(mp, DMA_CHAN, &cbs[0], 0);
}


void start_smi(MEM_MAP *mp){
	//DMA_CB *cbs = mp->virt;
	//start_dma(mp, DMA_CHAN, &cbs[0], 0);
	//usleep(1000*90);
    //stop_dma(DMA_CHAN);
	//usleep(1000*90);
	smi_cs->start = 1;
    //stop_dma(DMA_CHAN);
}

void stop_smi(){
	//stop_dma(DMA_CHAN);
	//usleep(1000*90);
	smi_cs->start = 0;
	usleep(10);
}

unsigned int dma_transfer_len(int chan){
	return (*REG32(dma_regs, DMA_REG(chan, DMA_TXFR_LEN)));
}

unsigned int dma_active(int chan){
	return ((*REG32(dma_regs, DMA_REG(chan, DMA_CS))) & 1);
}

void swap_bytes(void *data, int len){
	unsigned short *wp = (unsigned short *)data;
	len = (len + 1)/2;
	while (len-- > 0){
		*wp = __builtin_bswap16(*wp);
		wp ++;
	}
}

void smi_terminate(int sig){
	int i;
	printf("closing\n");
	if(gpio_regs.virt){
		for(i = 0; i < LED_NCHANS; i++){
			gpio_mode(LED_D0_PIN+i, GPIO_IN);
		}
	}
	if(smi_regs.virt){
		*REG32(smi_regs, SMI_CS) =0;
	}
	stop_dma(DMA_CHAN);
	unmap_periph_mem(&vc_mem);
	unmap_periph_mem(&smi_regs);
	unmap_periph_mem(&dma_regs);
	unmap_periph_mem(&gpio_regs);
	//exit(0);
}


int init_rpi_smi(void){
	map_devices(); 
	signal(SIGINT, smi_terminate);
	init_smi(LED_NCHANS>8 ? SMI_16_BITS : SMI_8_BITS, SMI_TIMING);	
	set_gpio_smi_mode();
	usleep(1000);
    printf("set gpio mode ok!\n");
	map_uncached_mem(&vc_mem, VC_MEM_SIZE);
	setup_smi_dma(&vc_mem, TX_BUFF_LEN(chan_ledcount));
    printf("setup smi dma ok!\n");
    return 0;
}

/***************************************************************
param : int led_count
return : always zero
purpose : set how many leds in one chan
***************************************************************/
int rpi_set_smi_chan_led_count(int led_count){
	chan_ledcount = led_count;
    return 0;   
}


void set_test_buffer(int color){
	for(int m = 0; m < LED_NCHANS; m ++){
		for(int q = 0; q < CHAN_MAXLEDS; q ++){
			rgb_data[q][m] = color;
		}
	}
    
	for(int n = 0; n < chan_ledcount; n++){
		rgb_txdata(rgb_data[n], &tx_buffer[LED_TX_OSET(n)]);
	}
#if LED_NCHAN <= 8
	swap_bytes(tx_buffer, TX_BUFF_SIZE(chan_ledcount));
#endif
	memcpy(txdata, tx_buffer, TX_BUFF_SIZE(chan_ledcount));
    /*rpi_start_dma(&vc_mem);
	usleep(1000*90);
	stop_dma(DMA_CHAN);
	usleep(1000*90);*/
}

/***************************************************************
param : void
return : always zero
purpose : trigger the smi and dma
***************************************************************/
#define TEST_RGB    0
int rpi_start_smi(void){
    stop_smi();
#if TEST_RGB
    int color_shift = 0;
    int k = 0;
    
	for(int m = 0; m < LED_NCHANS; m ++){
		for(int q = 0; q < CHAN_MAXLEDS; q ++){
			rgb_data[q][m] = k << color_shift;
		}
	}
	/*for (int z=0; z< 8; z ++ ){
		printf("rgb data = 0x%08x\n", *(unsigned int*)(rgb_data + z*4));
	}*/
	/*k++;
	if(k > 0x80){
		k = 0;	
		color_shift += 8;
		if(color_shift >= 24){
			color_shift = 0;
		}
	}*/
	for(int n = 0; n < chan_ledcount; n++){
		rgb_txdata(rgb_data[n], &tx_buffer[LED_TX_OSET(n)]);
	}
	//usleep(10);
	//memcpy(txdata, tx_buffer, TX_BUFF_SIZE(chan_ledcount));

#endif
	//memcpy(txdata, tx_buffer, TX_BUFF_SIZE(chan_ledcount));
    rpi_start_dma(&vc_mem);
	usleep(1000);
	//stop_dma(DMA_CHAN); //-->wrong wave 
    
    start_smi(&vc_mem);
	//stop_dma(DMA_CHAN);
	//usleep(1000*90);
    //stop_smi();
    return 0;
} 

int main_test_code(int argc, char* argv[]){
	int n, oset = 0;
	map_devices();
	printf("map devices ok!\n");
	
	signal(SIGINT, smi_terminate);
	init_smi(LED_NCHANS>8 ? SMI_16_BITS : SMI_8_BITS, SMI_TIMING);	
	set_gpio_smi_mode();
	usleep(1000);
	printf("VC_MEM_SIZE = %d\n", VC_MEM_SIZE);
	map_uncached_mem(&vc_mem, VC_MEM_SIZE);
	//memset(txdata, 0, VC_MEM_SIZE);
#if TX_TEST
		
	oset = oset;
	printf("ready to setup smi dma\n");
	printf("sizeof(tx_test_data)/sizeof(TXDATA_T) = %d\n", sizeof(tx_test_data)/sizeof(TXDATA_T));
	setup_smi_dma(&vc_mem, sizeof(tx_test_data)/sizeof(TXDATA_T));
	int test_value = 0xa5;
	printf("sizeof(tx_test_data) = %d\n", sizeof(tx_test_data));
	for(int k = 0; k < sizeof(tx_test_data); k ++){
		//tx_test_data[k] = 0xa5-(k);
		if((k%2) == 0){
			tx_test_data[k] = 0xff;
		}else{
			tx_test_data[k] = 0x88;
		}
	
	}
	for(int i = 0; i < 1000; i ++){
	//init_smi(LED_NCHANS>8 ? SMI_16_BITS : SMI_8_BITS, SMI_TIMING);	
	//map_uncached_mem(&vc_mem, VC_MEM_SIZE);
	//setup_smi_dma(&vc_mem, sizeof(tx_test_data)/sizeof(TXDATA_T));

	
#if LED_NCHAN <= 8
	swap_bytes(tx_test_data, sizeof(tx_test_data));
#endif
	
	//memcpy(txdata, tx_test_data, sizeof(tx_test_data));
	//usleep(10);
	//printf("start smi\n");
	memcpy(txdata, tx_test_data, sizeof(tx_test_data));
	start_smi(&vc_mem); // 1. start DMA 2. start SMI
	//memcpy(txdata, tx_test_data, sizeof(tx_test_data));
	//printf("end smi\n");
	//usleep(10);
	//while(dma_active(DMA_CHAN)){
	//	usleep(10);
	//}
	//usleep(CHASE_MSEC*100);
	//*REG32(smi_regs, SMI_CS) = 0;
	//stop_dma(DMA_CHAN);
	//stop_smi();
		//usleep(CHASE_MSEC*1000);
	memcpy(txdata, tx_zero_data, sizeof(tx_zero_data));


	}
	//stop_smi();
#else
	setup_smi_dma(&vc_mem, TX_BUFF_LEN(chan_ledcount));
	int color_shift = 0;
	int k = 0;
	while(1){
		for(int m = 0; m < LED_NCHANS; m ++){
			for(int q = 0; q < CHAN_MAXLEDS; q ++){
				rgb_data[q][m] = k << color_shift;
			}
		}
		/*for (int z=0; z< 8; z ++ ){
			printf("rgb data = 0x%08x\n", *(unsigned int*)(rgb_data + z*4));
		}*/
		//break;
		k++;
		if(k > 0x80){
			k = 0;	
			color_shift += 8;
			if(color_shift >= 24){
				color_shift = 0;
				//break;
			}
		}
		for(n = 0; n < chan_ledcount; n++){
			//rgb_txdata(n==oset%chan_ledcount ? on_rgbs : off_rgbs, &tx_buffer[LED_TX_OSET(n)]);
			rgb_txdata(rgb_data[n], &tx_buffer[LED_TX_OSET(n)]);
		}
		
		oset++;
#if  LED_NCHAN <= 8
		swap_bytes(tx_buffer, TX_BUFF_SIZE(chan_ledcount));
#endif
		memcpy(txdata, tx_buffer, TX_BUFF_SIZE(chan_ledcount));
		start_smi(&vc_mem);
		usleep(1000*3);
		//usleep(CHASE_MSEC*1000);
	}
	//usleep(10);
#endif
	smi_terminate(0);
	return 0;
}
