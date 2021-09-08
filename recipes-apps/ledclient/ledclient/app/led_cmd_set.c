#include "led_cmd_set.h"

extern struct ledparams led_params;
#define led_params_items	7

bool StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}


void dump_led_params(int port_id){
	log_debug("led_params[%d].cabinet_width = %d\n", port_id, led_params.cab_params[port_id].cabinet_width);
	log_debug("led_params[%d].cabinet_height = %d\n", port_id, led_params.cab_params[port_id].cabinet_height);
	log_debug("led_params[%d].start_x = %d\n", port_id, led_params.cab_params[port_id].start_x);
	log_debug("led_params[%d].start_y = %d\n", port_id, led_params.cab_params[port_id].start_y);
	log_debug("led_params[%d].layout_type = %d\n", port_id, led_params.cab_params[port_id].layout_type);
}

int handle_set_cabinet_params(char *cmd_params){
	char param[1024] = {0};
	memcpy(param, cmd_params, strlen(cmd_params));
	char *token = strtok(&param, ",");
    char tmp_param[led_params_items][1024] = {0};
    char *tagtoken;
    char *valuetoken;
    int i = 0;
	int port_id, cab_width, cab_height, start_x, start_y, layout_type;
	//while(token != NULL){
    for(i = 0 ; i < led_params_items; i ++){
		if(token == NULL){
			break;
		}
		printf("token = %s\n", token);
        memcpy(tmp_param[i], token, strlen(token));
        token = strtok(NULL, ",");
    }   
    for(i = 0 ; i < led_params_items; i ++){
        printf("tmp_param[%d] = %s\n", i, tmp_param[i]);
        if(StartsWith(tmp_param[i], "port_id")){
            tagtoken = strtok(tmp_param[i], "=");
            valuetoken = strtok(NULL, ","); 
			port_id = atoi(valuetoken);
            printf("port id : %d\n", port_id);
        }else if(StartsWith(tmp_param[i], "cabinet_width")){
            tagtoken = strtok(tmp_param[i], "=");
            valuetoken = strtok(NULL, ","); 
			cab_width = atoi(valuetoken);
            printf("cabinet_width : %d\n", cab_width);
        }else if(StartsWith(tmp_param[i], "cabinet_height")){
            tagtoken = strtok(tmp_param[i], "=");
            valuetoken = strtok(NULL, ","); 
			cab_height = atoi(valuetoken);
            printf("cabinet_height : %d\n", cab_height);
        }else if(StartsWith(tmp_param[i], "start_x")){
            tagtoken = strtok(tmp_param[i], "=");
            valuetoken = strtok(NULL, ","); 
			start_x = atoi(valuetoken);
            printf("start_x : %d\n", start_x);
        }else if(StartsWith(tmp_param[i], "start_y")){
            tagtoken = strtok(tmp_param[i], "=");
            valuetoken = strtok(NULL, ","); 
			start_y = atoi(valuetoken);
            printf("start_y : %d\n", start_y);
        }else if(StartsWith(tmp_param[i], "layout_type")){
            tagtoken = strtok(tmp_param[i], "=");
            valuetoken = strtok(NULL, ","); 
			layout_type = atoi(valuetoken);
            printf("layout_type : %d\n", layout_type);
        }   

    }

	led_params.cab_params[port_id].cabinet_width = cab_width;
	led_params.cab_params[port_id].cabinet_height = cab_height;
	led_params.cab_params[port_id].start_x = start_x;
	led_params.cab_params[port_id].start_y = start_y;
	led_params.cab_params[port_id].layout_type = layout_type;
	dump_led_params(port_id);
	write_cabinet_params_config_file(port_id, &led_params.cab_params[port_id]);
	return 0;

}

int get_version(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
	 log_debug("seq_id = %d\n", seq_id);
	 log_debug("cmd = %s\n", cmd);
	 log_debug("param = %s\n", param);
	 sprintf(reply_buf,"cmd_seq_id:%d;cmd:%s;reply:%s", seq_id, cmd, LEDCLIENT_VERSION);
     log_debug("reply buf = %s\n", reply_buf);
	 	
    return strlen(reply_buf);
}

int get_pico_num(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd:%s;reply:%d", seq_id, cmd, 1);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}

int get_cabinet_params(char *data, char *reply_buf){
    log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[256];
	char param[256];
	char tmp[256];
	int port_id;
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
	log_debug("seq_id = %d\n", seq_id);
	log_debug("cmd = %s\n", cmd);
	log_debug("param : %s\n", param);
	sscanf(param, "%[0-9a-z|^_]:%d", &tmp, &port_id);
	
	log_debug("port_id = %d\n", port_id);

	int cabinet_width = led_params.cab_params[port_id].cabinet_width;
	int cabinet_height = led_params.cab_params[port_id].cabinet_height;
	int start_x = led_params.cab_params[port_id].start_x;
	int start_y = led_params.cab_params[port_id].start_y;
	int layout_type = led_params.cab_params[port_id].layout_type;
	
	sprintf(tmp, "port_id=%d,cabinet_width=%d,cabinet_height=%d,start_x=%d,start_y=%d,layout_type=%d",
				  port_id, cabinet_width, cabinet_height, start_x, start_y, layout_type);	

	sprintf(reply_buf,"cmd_seq_id:%d;cmd:%s;reply:%s", seq_id, cmd, tmp);
	
		
	return strlen(reply_buf);	
}

int set_led_size(char *data, char *reply_buf){
     log_debug("data = %s\n", data);
	 int seq_id = 0;
	 char cmd[64];
	 char param[64];

	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
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
	 sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
	 /*To be implemented*/

	 sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
     log_debug("reply buf = %s\n", reply_buf);
	 	
     return strlen(reply_buf);
}

int set_cabinet_params(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
	
	log_debug("param = %s\n", param);
	if(handle_set_cabinet_params(param) < 0){
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
	}else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
	
	}	
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
	
	/*set get_cabinet_size callback*/
	ret = register_udp_cmd_callback(CMD_CALLBACK_GET_CABINET_PARAMS, &get_cabinet_params);
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
	
	/*set set_cabinet_size callback*/
	ret = register_udp_cmd_callback(CMD_CALLBACK_SET_CABINET_PARAMS, &set_cabinet_params);
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
