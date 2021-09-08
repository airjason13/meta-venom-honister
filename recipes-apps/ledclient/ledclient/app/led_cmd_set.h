#ifndef _LED_CMD_SET_H_
#define _LED_CMD_SET_H_
#include <stdio.h>
#include <stdlib.h>
#include <utildbg.h>
#include "udp_cmd.h"
#include "ledclient_version.h"
#include "ledlayout.h"
#include "cabinetutils.h"
#include "errno.h"


#define REPLY_OK_TAG			"ok"
#define REPLY_NG_TAG			"ng"


int get_version(char *data, char *reply_buf);
int get_pico_num(char *data, char *reply_buf);
int get_cabinet_params(char *data, char *reply_buf);


int set_led_size(char *data, char *reply_buf);
int set_cabinet_size(char *data, char *reply_buf);
int set_cabinet_params(char *data, char *reply_buf);


int spec_test(char *data, char *reply_buf);	
int set_udp_cmd_callbacks(void);

#endif
