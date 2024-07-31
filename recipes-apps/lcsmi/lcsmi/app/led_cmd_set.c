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
    
    //not a good method,but we need it temp
    if(port_id == 0){
        if((cab_width != 0)||(cab_height != 0)){
            char cmd_buf[64] = {0};
            char reply_buf[64] = {0};
            sprintf(cmd_buf,"cmd:set_port_res,%d,%d", led_params.cab_params[i].cabinet_width, led_params.cab_params[i].cabinet_height);
            int iret = picousb_set_cmd(led_params.pico_handle, cmd_buf, reply_buf);
            log_debug("iret = %d, recv_buf = %s\n", iret, reply_buf);
        }
    }
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
    //log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[256];
	char param[256];
	char tmp[256];
	int port_id;
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
	//log_debug("seq_id = %d\n", seq_id);
	//log_debug("cmd = %s\n", cmd);
	//log_debug("param : %s\n", param);
	sscanf(param, "%[0-9a-z|^_]:%d", &tmp, &port_id);
	
	//log_debug("port_id = %d\n", port_id);

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

int get_icled_type(char *data, char *reply_buf){
    log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[256];
	char param[256];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    //need to be implement
	sprintf(reply_buf,"cmd_seq_id:%d;cmd:%s;reply:%s", seq_id, cmd, LEDCLIENT_VERSION);
    log_debug("reply buf = %s\n", reply_buf);
	 	
    return strlen(reply_buf);
}

int get_icled_current_gain(char *data, char *reply_buf){
    log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[256];
	char param[256];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    //not implemented yet
	sprintf(reply_buf,"cmd_seq_id:%d;cmd:%s;reply:%s", seq_id, cmd, LEDCLIENT_VERSION);
    log_debug("reply buf = %s\n", reply_buf);
	 	
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

int set_frame_brightness(char *data, char *reply_buf){
	//log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    if(set_frame_brightness_value(atoi(param)) < 0){
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
    }else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    }
    //log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int get_frame_brightness(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}


int set_frame_br_divisor(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    if(set_frame_br_divisor_value(atoi(param)) < 0){
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
    }else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    }
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int get_frame_br_divisor(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int set_frame_contrast(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    if(set_frame_contrast_value(atoi(param)) < 0){
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
    }else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    }
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int get_frame_contrast(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int set_frame_gamma(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    log_debug("param = %s\n", param);

    log_debug(" params to float = %f\n", atof(param));
    if(set_frame_gamma_value(atof(param)) < 0){
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
    }else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    }
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int get_frame_gamma(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
   
    log_debug("param = %s\n", param);
    return strlen(reply_buf); 
}

int set_pixel_interval(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
    char pico_cmd_buf[64];
    char pico_reply_buf[64];
    int i_pico_ret = -1;
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    
    sprintf(pico_cmd_buf, "cmd:set_pixel_interval,%s", param);
    log_debug("pico_cmd_buf = %s\n", pico_cmd_buf);
    i_pico_ret = picousb_set_cmd(led_params.pico_handle, pico_cmd_buf, pico_reply_buf);
    log_debug("pico_reply_buf = %s\n", pico_reply_buf);
    if(i_pico_ret < 0){
        if(strstr(pico_reply_buf, "OK")){
	 	    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
        }else{
	 	    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
        }
    }else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    }
    return strlen(reply_buf);
}

int get_pixel_interval(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
    char pico_cmd_buf[64];
    char pico_reply_buf[64];
    int i_pico_ret = -1;
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    
    //get command no implemented yet!
    if(i_pico_ret > 0){
        if(strstr(pico_reply_buf, "OK")){
	 	    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
        }else{
	 	    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
        }
    }else{
	 	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    }
    return strlen(reply_buf);
}

int set_client_id(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
    
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    led_params.i_clientid = atoi(param);
    log_debug("led_params.i_clientid = %d\n", led_params.i_clientid);	
    char id_data[16] = {0};
    sprintf(id_data, "ID=%d", led_params.i_clientid);
    refresh_lcd_content(TAG_LCD_INFO, SUB_TAG_IP_ID, NULL, id_data);
    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    return strlen(reply_buf);
}

int set_icled_type(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    if(!strcmp(param, TAG_ICLED_TYPE_AOS) 
        && !strcmp(param, TAG_ICLED_TYPE_ANAPEXL)
        && !strcmp(param, TAG_ICLED_TYPE_ANAPEXM)){
        sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
        log_debug("reply_buf = %s\n", reply_buf);
        return strlen(reply_buf); 

    }
    // write icled_type_config
    write_icled_type_config_file(param);  
 
    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    log_debug("reply_buf = %s\n", reply_buf);
    return strlen(reply_buf); 
}

int set_icled_current_gain(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];
    int rgain, ggain, bgain;
    
	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    sscanf(param, "rgain=%d,ggain=%d,bgain=%d", &rgain, &ggain, &bgain);
    log_debug("rgain = %d, ggain = %d, bgain = %d\n", rgain, ggain, bgain);
    write_icled_current_gain_config_file(rgain, ggain, bgain); 
    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
    log_debug("reply_buf = %s\n", reply_buf);
    return strlen(reply_buf); 
}

int get_client_id(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
	int seq_id = 0;
	char cmd[1024];
	char param[1024];

	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
	sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_NG_TAG);
    return strlen(reply_buf);
}

int set_start_test(char *data, char *reply_buf){
	log_debug("data = %s\n", data);
    
	int seq_id = 0;
	char cmd[1024];
	char param[1024];

	sscanf(data, "cmd_seq_id:%d;cmd:%[1-9a-z|^_];param:%s", &seq_id, &cmd, &param);
    
	log_debug("need to be implemented!\n");
    
    char pico_cmd_buf[64] = {0};
    char pico_reply_buf[64] = {0};
    sprintf(pico_cmd_buf,"cmd:set_test_color_start,%s", param);
    int iret = picousb_set_cmd(led_params.pico_handle, pico_cmd_buf, pico_reply_buf);
    log_debug("iret = %d, pico_reply_buf = %s\n", iret, pico_reply_buf);
    sprintf(reply_buf,"cmd_seq_id:%d;cmd=%s;reply:%s", seq_id, cmd, REPLY_OK_TAG);
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
    log_debug(" ");
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
	
    /*set set_client_brightness callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_FRAME_BRIGHTNESS, &set_frame_brightness);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   
	
    /*set get_client_brightness callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_FRAME_BRIGHTNESS, &get_frame_brightness);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   
    
    /*set set_client_br_divisor callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_FRAME_BR_DIVISOR, &set_frame_br_divisor);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }   
	
    /*set get_client_br_divisor callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_FRAME_BR_DIVISOR, &get_frame_br_divisor);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }  
 
    /*set set_client_contrast callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_FRAME_CONTRAST, &set_frame_contrast);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }  
 
    /*set get_client_contrast callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_FRAME_CONTRAST, &get_frame_contrast);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    } 
 
    /*set set_client_gamma callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_FRAME_GAMMA, &set_frame_gamma);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }  
 
    /*set get_client_contrast callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_FRAME_GAMMA, &get_frame_gamma);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    } 
    /*set set_pixe_interval callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_PIXEL_INTERVAL, &set_pixel_interval);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }  

    /*set get_pixe_interval callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_PIXEL_INTERVAL, &get_pixel_interval);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    } 
 
    /*set set_client_id callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_CLIENT_ID, &set_client_id);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }
  
    /*get set_client_id callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_CLIENT_ID, &get_client_id);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }

    /*get set_icled_type callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_ICLED_TYPE, &get_icled_type);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }
    
    /*get set_icled_type callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_ICLED_TYPE, &set_icled_type);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }

    /*get set_icled_rgb_current_gain callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_GET_ICLED_CURRENT_GAIN, &get_icled_current_gain);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }

    /*get set_icled_rgb_current_gain callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_ICLED_CURRENT_GAIN, &set_icled_current_gain);
    if(ret != 0){
        log_error("callback register failed!\n");
		return ret;
    }
    /*get set_start_test callback*/
    ret = register_udp_cmd_callback(CMD_CALLBACK_SET_START_TEST, &set_start_test);
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
