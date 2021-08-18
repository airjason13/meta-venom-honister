#include "led_cmd_set.h"



int get_version(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z];param:%s", &seq_id, &cmd, &param);

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, LEDCLIENT_VERSION);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}

int get_pico_num(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z];param:%s", &seq_id, &cmd, &param);

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%d", seq_id, cmd, 1);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}


int set_led_size(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];

	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z];param:%s", &seq_id, &cmd, &param);
	 /*To be implemented*/

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}


int set_cabinet_size(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z];param:%s", &seq_id, &cmd, &param);
	 /*To be implemented*/

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}

int spec_test(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z];param:%s", &seq_id, &cmd, &param);
	 /*To be implemented*/

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}


int set_udp_cmd_callbacks(void){
	/*initial udp cmd callback test*/
	int ret = register_udp_cmd_callback(CMD_CALLBACK_GET_VERSION, &get_version);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   

	/*set get_pico_num callback*/
	ret = register_udp_cmd_callback(CMD_CALLBACK_GET_PICO_NUM, &get_pico_num);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   


	/*set set_led_size callback*/
	ret = register_udp_cmd_callback(CMD_CALLBACK_SET_LED_SIZE, &set_led_size);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   
	/*set set_cabinet_size callback*/
	ret = register_udp_cmd_callback(CMD_CALLBACK_SET_CABINET_SIZE, &set_cabinet_size);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   
	
	/*set spec_test callback*/
	ret = register_udp_cmd_callback(CMD_CALLBACK_SPEC_TEST, &spec_test);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   
	
	return 0;
}
