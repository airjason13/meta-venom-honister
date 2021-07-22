#ifndef _LEDLAYOUT_H_
#define _LEDLAYOUT_H_

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

char led_layout[LED_PANELS] = {	1, 1, 1, 1,	3, 3, 3, 3};

#endif
