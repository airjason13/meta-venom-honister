#include "rpi_mem_j.h"


int open_mbox(void){
	int fd;
	if((fd = open("/dev/vcio", 0)) < 0){
		//printf("Error: can't open VC mailbox\n");
	}
	return (fd);
}

void close_mbox(int fd){
	if (fd >= 0){
		close(fd);
	}
}

void disp_vc_msg(VC_MSG *msgp){
	int i;
	//printf("VC msg len=%X, req=%X, tag=%X, dlen=%x, data",
	//		       msgp->len, msgp->req, msgp->tag, msgp->blen, msgp->dlen);
	for(i = 0; i < msgp->blen/4;i ++){
		//printf("%08X ", msgp->uints[i]);
	}
//	printf("\n");

}


unsigned int msg_mbox(int fd, VC_MSG *msgp){
	unsigned int ret = 0, i;

	for (i = msgp->dlen/4; i <= msgp->blen/4; i+=4){
		msgp->uints[i++] = 0;
	}
	msgp->len = (msgp->blen +6) *4;
	msgp->req = 0;
	if(ioctl(fd, _IOWR(100, 0, void*), msgp) < 0){
		//printf("msgp->req = %x\n", msgp->req);
		//printf("VC IOCTL failed\n");
	}else if ((msgp->req&0x80000000) == 0){
		//printf("msgp->req = %x\n", msgp->req);
		//printf("VC IOCTL error\n");
	}else if (msgp->req == 0x80000001){
		//printf("msgp->req = %x\n", msgp->req);
		//printf("VC IOCTL partial error\n");
	}else
		ret = msgp->uints[0];

#if DEBUG
	disp_vc_msg(msgp);
#endif
	return (ret);
}

unsigned int alloc_vc_mem(int fd, unsigned int size, VC_ALLOC_FLAGS flags){
	unsigned int u32_ret = 0;
	VC_MSG msg={.tag=0x3000c, .blen=12, .dlen=12,
		.uints={PAGE_ROUNDUP(size), PAGE_SIZE, flags}};
	u32_ret = msg_mbox(fd, &msg);
	//printf("alloc_vc_mem ret = 0x%x\n", msg_mbox(fd, &msg));
	return msg_mbox(fd, &msg);
}

void *lock_vc_mem(int fd, int h){
	VC_MSG msg={.tag=0x3000d, .blen=4, .dlen=4, .uints={h}};
	return (h ? (void *)msg_mbox(fd, &msg) : 0);
}

unsigned int unlock_vc_mem(int fd, int h){
	VC_MSG msg={.tag=0x3000e, .blen=4, .dlen=4, .uints={h}};
	return (h ? msg_mbox(fd, &msg) : 0);
}

unsigned int free_vc_mem(int fd, int h){
	VC_MSG msg={.tag=0x3000f, .blen=4, .dlen=4, .uints={h}};
	return (h ? msg_mbox(fd, &msg) : 0);

}

void *map_uncached_mem(MEM_MAP *mp, int size){
	void *ret;
	mp->size = PAGE_ROUNDUP(size);
	mp->fd = open_mbox();
	ret = (mp->h = alloc_vc_mem(mp->fd, mp->size, DMA_MEM_FLAGS)) > 0 &&
		(mp->bus = lock_vc_mem(mp->fd, mp->h)) != 0 && 
		(mp->virt = map_segment(BUS_PHYS_ADDR(mp->bus), mp->size)) != 0
		? mp->virt : 0;
	//unlock_vc_mem(mp->fd, mp->h);
	//printf("mp->h = 0x%08x\n", mp->h);
	//printf("mp->size = 0x%08x\n", mp->size);
	//printf("mp->bus = 0x%08x\n", mp->bus);
	mp->phys = BUS_PHYS_ADDR(mp->bus);
	//printf("mp->phys = 0x%08x\n", mp->phys);
	//printf("mp->virt = 0x%08x\n", mp->virt);
	printf("1. mp->virt = %p\n", mp->virt);
	mp->virt = (unsigned long)mp->virt & 0x7fffffffff;
	//mp->virt = mp->bus;//(unsigned long)mp->virt & 0x7fffffffff;
	printf("2.mp->virt = %p\n", mp->virt);

	//printf("map uncached mem : %08x\n", ret);
	//printf("BUS_PHYS_ADDR(mp->bus) : %08x\n", BUS_PHYS_ADDR(mp->bus));
	//printf("mp->virt value : 0x%08x\n", *(unsigned long*)mp->virt);
	//printf("VC mem handle : %u, phys %p, virt %p\n", mp->h, mp->bus, mp->virt);
	return (ret);
}
