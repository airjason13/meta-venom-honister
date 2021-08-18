#ifndef _UDP_CMD_H_
#define _UDP_CMD_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utildbg.h>
#include <errno.h>
#define MSGBUFSIZE 				256
#define IP_BUF_SIZE				64

typedef int (*cmd_callback_t)(char *, char *);


//CMD ID
#define CMD_CALLBACK_START				0
#define CMD_CALLBACK_GET_VERSION 		0
#define CMD_CALLBACK_GET_PICO_NUM 		1

#define CMD_CALLBACK_SET_LED_SIZE		2
#define CMD_CALLBACK_SET_CABINET_SIZE	3
#define CMD_CALLBACK_SPEC_TEST			4

#define CMD_CALLBACK_MAX				CMD_CALLBACK_SPEC_TEST
#define CMD_CALLBACK_SIZE				CMD_CALLBACK_MAX + 1

//CMD_NAME_TAG
#define CMD_TAG_GET_VERSION				"get_version"
#define CMD_TAG_GET_PICO_NUM			"get_pico_num"

#define CMD_TAG_SET_LED_SIZE			"set_led_size"
#define CMD_TAG_SET_CABINET_SIZE		"set_cabinet_size"
#define CMD_TAG_SPEC_TEST				"spec_test"


#define MAX_CMD_NAME					64

typedef struct udp_cmd_handle{
	int cmd_id;//for callback function id
	char cmd_name[MAX_CMD_NAME];
	int (*cmd_callback)(char *, char *);
	
}udp_cmd_handle_t;


typedef struct udp_cmd_params{
	int socketfd;
	char ip[IP_BUF_SIZE];//ANY
	int port;//recv port
	pthread_t t;//recv cmd thread
	udp_cmd_handle_t udp_cmd_handle[CMD_CALLBACK_SIZE];
};


int register_udp_cmd_callback(unsigned int func_num, cmd_callback_t callback);
int udp_cmd_init( int port);

#endif
