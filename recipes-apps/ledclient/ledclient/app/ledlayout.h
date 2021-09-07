#ifndef _LEDLAYOUT_H_
#define _LEDLAYOUT_H_

#include "picousb.h"
#include "cabinetutils.h"
/*******************************************************************
* LED layout configuration
* 0 :
*  		 ---------------------------< start
*		 |
*		 >---------------------------
*	 								|
*	end	 ---------------------------<
*
* 1:
*	start >---------------------------
*									 |
*		 ----------------------------< 
*		 |
*		 >---------------------------- end
*
* 2:	
*		 >---------------------------- end
*		 |
*		 ----------------------------<
*		 							 |
*  start >----------------------------
*
* 3:
*	end	 ----------------------------<
*									 | 
*		 >----------------------------	
*		 |
*		 ----------------------------< start	
*
*****************************************/

typedef enum{
	e_vertsatrtuprightenddownleft = 0,
	e_vertstartupleftenddownright,
	e_vertstartdownleftendupright,
	e_vertstartdownrightendupleft,
};

#define LED_PANELS		8
#define PER_PIXEL_PANEL	960
#define LED_WIDTH		40
#define LED_HEIGHT		24
#define LED_CHANNELS	3


//int led_fps = 0;


typedef struct ledparams{
	struct libusb_device_handle *pico_handle;
	struct cabinet_params cab_params[LED_PANELS];
	int i_ledpanelsi;// = 8;
	int i_pixelsperpanel;// = 960;
	int i_widthperpanel;// = 40;
	int i_heightperpanel;// = 24;
	int i_widthtotal;// = 80;
	int i_heighttotal;// = 96;
	int i_startx;// = 0;
	int i_start_y;
	int i_ledchannels;// = 3;
	int i_ledic;// = 0;
	pthread_t udp_cmd_tid;
	pthread_t udpbr_tid;
	pthread_t udpmr_tid;
}ledparams_t;


#endif
