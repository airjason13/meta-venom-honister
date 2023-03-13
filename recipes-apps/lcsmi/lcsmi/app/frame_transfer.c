#include "frame_transfer.h"

extern struct ledparams led_params;
int frame_br_divisor = 1;//32
int frame_brightness = 100;//0~100
int frame_contrast = 0;
float f_gamma = 1.0;
unsigned char g_GammaLut[256];

int init_frame_brightness(void){
    frame_brightness = get_brightness_from_config();
    log_debug("frame_brightness : %d", frame_brightness);
    return 0;
}

int init_frame_contrast(void){
    log_debug("");
    frame_contrast = get_contrast_from_config();
    log_debug("frame_contrast : %d", frame_contrast);
    return 0;
}

int init_frame_gamma(void){
    f_gamma = get_gamma_from_config();
    log_debug("f_gamma : %f", f_gamma);
    //f_gamma = fvalue;
    int i;
    float f;
    
    for(i = 0; i < 256; i++){
        f=(i+0.5F)/256;
        f=(float)pow(f, f_gamma);
        g_GammaLut[i] = (unsigned char)(f*256 - 0.5F); 
    }
    return 0;
}

int set_frame_brightness_value(int value){
    if((value > 100) || (value < 0)){
        return -EINVAL;
    }
    frame_brightness = value;
    // write to default config
    write_brightness_config_file(value);
    return 0;
}

int get_frame_brightness_value(void){
    return frame_brightness;
}

int set_frame_br_divisor_value(int value){
    if((value > 100) || (value < 0)){
        return -EINVAL;
    }
    frame_br_divisor = value;
    return 0;
}

int get_frame_br_divisor_value(void){
    return frame_br_divisor;
}

int set_frame_contrast_value(int value){
    if((value > 255) || (value < 0)){
        return -EINVAL;
    }
    frame_contrast = value;
    write_contrast_config_file(value);
    return 0;
}

int get_frame_contrast_value(void){
    return frame_contrast;
}


int set_frame_gamma_value(float fvalue){
    int i;
    float f;
    write_gamma_config_file(fvalue);
    f_gamma = fvalue;
    for(i = 0; i < 256; i++){
        f=(i+0.5F)/256;
        f=(float)pow(f, f_gamma);
        g_GammaLut[i] = (unsigned char)(f*256 - 0.5F); 
    }
    log_debug("set gamma lut ok!\n");
    return 0;
}

int framergb32_to_ledargb32(AVFrame *pFrame, struct cabinet_params *params, int channel_count, int frame_width, int frame_height, unsigned int rgbdata[1000][16]){
	int offset = 0;
	int width = params->cabinet_width;
	int height = params->cabinet_height;
	int start_x = params->start_x;
	int start_y = params->start_y;
	unsigned int buf_size = (width*height*channel_count);
	//unsigned char *buf = malloc(buf_size);
	unsigned char *buf = rgbdata;
	int y = 0,x = 0;
	int i = 0;
	int write_len = 0;
	bool config_err = true;
	unsigned char *fake_pixel_buf = malloc(channel_count);
	switch(params->layout_type){
		case 0:
            //220928 enhanece with cabinet height out of frame height
            //0310 test limit ok
            if((start_x < 0) || (start_y < 0)){
                log_debug("case 0 params config error!");
                break;
            }
            // 
            /*if((start_y - height + 1) > frame_height){
                log_debug("case 0 params config error!");
                break;
            }*/
            //cabinet height out of frame height
            /*if((start_y + height + 1) >= frame_height){
                log_debug("case 0 params config error!");
                break; 
            }*/
            if((start_x + width) > frame_width){
                log_debug("case 0 params config error!");
                break; 
            }
            config_err = false;
            
            memset(fake_pixel_buf, 0, channel_count);
			for(y = 0; y < height; y++){
                if(start_y + y >= frame_height){
					    for(i = 0 ; i < width; i ++){
						    memcpy(buf + offset, fake_pixel_buf, channel_count);
						    offset += channel_count;
					    } 
                }else{
	                if(y % 2 == 0){ //first line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + start_x*channel_count, 
							    width*channel_count);
					    offset += width*channel_count;
				    }else{ //second line
					    for(i = 0 ; i < width; i ++){
						    memcpy(buf + offset, 
								    pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x + width - i -1)*channel_count, 
								    channel_count);
						    offset += channel_count;
					    }
				    }
                }
			}
			break;
		case 1:
            //0304 test limit ok
            if((start_x < 0) || ((start_y - height + 1) < 0)){
                log_debug("case 1 params config error!");
                break;
            }
            /*if((start_y + 1 ) > frame_height){
                log_debug("case 1 params config error!");
                break;
            }*/
            /*if((start_x + width) > frame_width){
                log_debug("case 1 params config error!");
                break; 
            }*/
            config_err = false;
			for(y = 0; y < height; y++){
                if(y % 2 == 0){
					memcpy(buf + offset, 
							pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + start_x*channel_count, 
							width*channel_count);
					offset += width*channel_count; 
                }else{
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, 
								pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x + width - i -1)*channel_count, 
								channel_count);
						offset += channel_count;
					}
                    
                }
            }    
			break;
		case 2: 
            //0304 test limit ok
            if((start_x + 1 > frame_width)||(start_y < 0)){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_x - width + 1) < 0){
                log_debug("case 2 params config error!");
                break;
            }
            /*if((start_y + height - 1) > frame_height){
                log_debug("case 2 params config error!");
                break;
            }*/
            
            config_err = false;
			for(y = 0; y < height; y++){
	            if(y % 2 == 1){ 
					memcpy(buf + offset, 
							pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count, 
							width*channel_count);
					offset += width*channel_count;
				}else{ 
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, 
								pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x - i )*channel_count, 
								channel_count);
						offset += channel_count;
					}
				}
			}
            
			break;
		case 3:
            //0310 test limit ok
            if((start_x + 1 > frame_width)||((start_y - height + 1) < 0)){
                log_debug("case 3 params config error!");
                break;
            }
            //cabinet height out of frame height
            /*if(start_y + 1 >= frame_height){
                log_debug("case 3 params config error!");
                break;
            }*/
            if((start_x - width + 1) < 0){
                log_debug("case 3 params config error!");
                break;
            }
            config_err = false;
            
			for(y = 0; y < height; y++){
                //cabinet height out of frame height
                if((start_y - y + 1) > frame_height){
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, fake_pixel_buf, channel_count);
						offset += channel_count;
					} 
                }else{
				    if(y % 2 == 0){ // first line
					    for(i = 0; i < width; i++){
						    memcpy(buf + offset,
								    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x -i)*channel_count,
								    channel_count);
						    offset += channel_count;
					    }
				    }else{ //second line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count,
							    width*channel_count);
					    offset += width*channel_count;
				    }
                }
			}
			break;
        case 4: 
            //0310 test limit ok
            if((start_x + 1 > frame_width)||(start_y < 0)){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_x - width + 1) < 0){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_y + height - 1) > frame_height){
                log_debug("case 2 params config error!");
                break;
            }
            config_err = false;
            for(x = 0;x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - 1 - y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 5: //confirm @1115 
            //0310 test limit ok
            if((start_x < 0) || ((start_y - height + 1) < 0)){
                log_debug("case 5 params config error!");
                break;
            }
            if((start_y + 1 ) > frame_height){
                log_debug("case 5 params config error!");
                break;
            }
            if((start_x + width  ) > frame_width){
                log_debug("case 5 params config error!");
                break; 
            }
            config_err = false;
            for(x = 0; x < width; x++){
                if(x % 2 == 1){
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y + 1)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 6: //confirm @1115
            //0310 test limit ok
            if((start_x + 1 > frame_width)||((start_y - height + 1) < 0)){
                log_debug("case 6 params config error!");
                break;
            }
            if((start_y + 1) > frame_height){
                log_debug("case 6 params config error!");
                break;
            
            }
            if((start_x - width + 1) < 0){
                log_debug("case 6 params config error!");
                break;
            }
            config_err = false;
            //for(x = width;x > 0;x--){
            for(x = 0;x < width;x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - height + y + 1)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 7: //confirm @1115
            //0310 test limit ok
            if((start_x < 0) || (start_y < 0)){
                log_debug("case 7 params config error!");
                break;
            }
            if((start_y + height ) > frame_height){
                log_debug("case 7 params config error!");
                break;
            }
            if((start_x + width ) > frame_width){
                log_debug("case 7 params config error!");
                break; 
            }
            config_err = false;
            for(x = 0; x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y + 1)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
	}

	if((width == 0)||(height == 0)){
		config_err = true;
	}

	if(config_err == true){
    	// fill zero to buf while config error
        log_fatal("config error!\n");
        return 0;
	}
	for(i = 0; i < offset; i ++){
		// frame_brightness : 0~100
		// frame_br_divisor : 0~100
		buf[i] =(char)((int)buf[i]*frame_brightness/(frame_br_divisor*100));
		buf[i] = g_GammaLut[buf[i]];
	}
    //log_debug("offset = %d\n", offset);
    /*for(int j = 0;j < offset/8; j++ ){
        *(ulrgbdata[j] + params->port_id) = ((buf[j+1]*256) << 24) | ((buf[j+2]*256) << 16) | (buf[j+3]*256);
    }*/
	
	return 0;
}


int framergb32_to_ledargb64(AVFrame *pFrame, struct cabinet_params *params, int channel_count, int frame_width, int frame_height, unsigned long ulrgbdata[1000][16]){
	int offset = 0;
	int width = params->cabinet_width;
	int height = params->cabinet_height;
	int start_x = params->start_x;
	int start_y = params->start_y;
	unsigned int buf_size = (width*height*channel_count);
	unsigned char *buf = malloc(buf_size);
	int y = 0,x = 0;
	int i = 0;
	int write_len = 0;
	bool config_err = true;
	unsigned char *fake_pixel_buf = malloc(channel_count);
	switch(params->layout_type){
		case 0:
            //220928 enhanece with cabinet height out of frame height
            //0310 test limit ok
            if((start_x < 0) || (start_y < 0)){
                log_debug("case 0 params config error!");
                break;
            }
            // 
            /*if((start_y - height + 1) > frame_height){
                log_debug("case 0 params config error!");
                break;
            }*/
            //cabinet height out of frame height
            /*if((start_y + height + 1) >= frame_height){
                log_debug("case 0 params config error!");
                break; 
            }*/
            if((start_x + width) > frame_width){
                log_debug("case 0 params config error!");
                break; 
            }
            config_err = false;
            
            memset(fake_pixel_buf, 0, channel_count);
			for(y = 0; y < height; y++){
                if(start_y + y >= frame_height){
					    for(i = 0 ; i < width; i ++){
						    memcpy(buf + offset, fake_pixel_buf, channel_count);
						    offset += channel_count;
					    } 
                }else{
	                if(y % 2 == 0){ //first line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + start_x*channel_count, 
							    width*channel_count);
					    offset += width*channel_count;
				    }else{ //second line
					    for(i = 0 ; i < width; i ++){
						    memcpy(buf + offset, 
								    pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x + width - i -1)*channel_count, 
								    channel_count);
						    offset += channel_count;
					    }
				    }
                }
			}
			break;
		case 1:
            //0304 test limit ok
            if((start_x < 0) || ((start_y - height + 1) < 0)){
                log_debug("case 1 params config error!");
                break;
            }
            /*if((start_y + 1 ) > frame_height){
                log_debug("case 1 params config error!");
                break;
            }*/
            /*if((start_x + width) > frame_width){
                log_debug("case 1 params config error!");
                break; 
            }*/
            config_err = false;
			for(y = 0; y < height; y++){
                if(y % 2 == 0){
					memcpy(buf + offset, 
							pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + start_x*channel_count, 
							width*channel_count);
					offset += width*channel_count; 
                }else{
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, 
								pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x + width - i -1)*channel_count, 
								channel_count);
						offset += channel_count;
					}
                    
                }
            }    
			break;
		case 2: 
            //0304 test limit ok
            if((start_x + 1 > frame_width)||(start_y < 0)){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_x - width + 1) < 0){
                log_debug("case 2 params config error!");
                break;
            }
            /*if((start_y + height - 1) > frame_height){
                log_debug("case 2 params config error!");
                break;
            }*/
            
            config_err = false;
			for(y = 0; y < height; y++){
	            if(y % 2 == 1){ 
					memcpy(buf + offset, 
							pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count, 
							width*channel_count);
					offset += width*channel_count;
				}else{ 
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, 
								pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x - i )*channel_count, 
								channel_count);
						offset += channel_count;
					}
				}
			}
            
			break;
		case 3:
            //0310 test limit ok
            if((start_x + 1 > frame_width)||((start_y - height + 1) < 0)){
                log_debug("case 3 params config error!");
                break;
            }
            //cabinet height out of frame height
            /*if(start_y + 1 >= frame_height){
                log_debug("case 3 params config error!");
                break;
            }*/
            if((start_x - width + 1) < 0){
                log_debug("case 3 params config error!");
                break;
            }
            config_err = false;
            
			for(y = 0; y < height; y++){
                //cabinet height out of frame height
                if((start_y - y + 1) > frame_height){
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, fake_pixel_buf, channel_count);
						offset += channel_count;
					} 
                }else{
				    if(y % 2 == 0){ // first line
					    for(i = 0; i < width; i++){
						    memcpy(buf + offset,
								    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x -i)*channel_count,
								    channel_count);
						    offset += channel_count;
					    }
				    }else{ //second line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count,
							    width*channel_count);
					    offset += width*channel_count;
				    }
                }
			}
			break;
        case 4: 
            //0310 test limit ok
            if((start_x + 1 > frame_width)||(start_y < 0)){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_x - width + 1) < 0){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_y + height - 1) > frame_height){
                log_debug("case 2 params config error!");
                break;
            }
            config_err = false;
            for(x = 0;x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - 1 - y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 5: //confirm @1115 
            //0310 test limit ok
            if((start_x < 0) || ((start_y - height + 1) < 0)){
                log_debug("case 5 params config error!");
                break;
            }
            if((start_y + 1 ) > frame_height){
                log_debug("case 5 params config error!");
                break;
            }
            if((start_x + width  ) > frame_width){
                log_debug("case 5 params config error!");
                break; 
            }
            config_err = false;
            for(x = 0; x < width; x++){
                if(x % 2 == 1){
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y + 1)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 6: //confirm @1115
            //0310 test limit ok
            if((start_x + 1 > frame_width)||((start_y - height + 1) < 0)){
                log_debug("case 6 params config error!");
                break;
            }
            if((start_y + 1) > frame_height){
                log_debug("case 6 params config error!");
                break;
            
            }
            if((start_x - width + 1) < 0){
                log_debug("case 6 params config error!");
                break;
            }
            config_err = false;
            //for(x = width;x > 0;x--){
            for(x = 0;x < width;x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - height + y + 1)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 7: //confirm @1115
            //0310 test limit ok
            if((start_x < 0) || (start_y < 0)){
                log_debug("case 7 params config error!");
                break;
            }
            if((start_y + height ) > frame_height){
                log_debug("case 7 params config error!");
                break;
            }
            if((start_x + width ) > frame_width){
                log_debug("case 7 params config error!");
                break; 
            }
            config_err = false;
            for(x = 0; x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y + 1)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
	}

	if((width == 0)||(height == 0)){
		config_err = true;
	}

	if(config_err == true){
    	// fill zero to buf while config error
        log_fatal("cabinet %d config error!\n", params->port_id);
        free(buf);
	    free(fake_pixel_buf);
        return 0;
	}
    //log_debug("frame_br_divisor = %d\n", frame_br_divisor);
    //log_debug("params->port_id = %d\n", params->port_id);
    
	for(i = 0; i < offset; i ++){
		// frame_brightness : 0~100
		// frame_br_divisor : 0~100
		buf[i] =(char)((int)buf[i]*frame_brightness/(frame_br_divisor*100));
		buf[i] = g_GammaLut[buf[i]];
	}
    
    for(int j = 0;j < offset/4; j++ ){
        *(unsigned long *)(ulrgbdata[j] + params->port_id) = 
                        (((unsigned long)buf[4*j + 2]*256) << 32) |  /*Red*/ 
                        (((unsigned long)buf[4*j + 1]*256) << 16) |  /*Green*/
                        ((unsigned long)buf[4*j + 0]*256);           /*Blue*/
    }
    free(buf);
	free(fake_pixel_buf);
	
	return 0;
}

int transfer_framergb_to_pico(AVFrame *pFrame, struct cabinet_params *params, int channel_count, int frame_width, int frame_height, struct libusb_device_handle *pico, char *input_uri){
	int offset = 0;
	int width = params->cabinet_width;
	int height = params->cabinet_height;
	int start_x = params->start_x;
	int start_y = params->start_y;
	unsigned int buf_size = (width*height*channel_count) + 4;
	unsigned char *buf = malloc(buf_size);
	int y = 0,x = 0;
	int i = 0;
	int write_len = 0;
    bool config_err = true;
    unsigned char *fake_pixel_buf = malloc(channel_count);
    if(pico == NULL){
        return -ENODEV;
    }
	if(buf == NULL){
		log_fatal("malloc failed!\n");
		return -ENOMEM;
	}
	sprintf(buf, "id%d:", params->port_id);
	offset +=4;

    //log_debug("frame brightness = %d\n", frame_brightness);
    //log_debug("frame gamma = %f\n", f_gamma);
    //return 2884;
    //log_debug("input uri = %s\n", input_uri);
    //log_debug("frame width = %d\n", frame_width);
    //log_debug("frame height = %d\n", frame_height);
    //log_debug("frame width = %d\n", pFrame->linesize[0]/channel_count);
	/*log_debug("port_id = %d\n", params->port_id);
	log_debug("width = %d\n", width);
	log_debug("height = %d\n", height);
	log_debug("start_x = %d\n", start_x);
	log_debug("start_y = %d\n", start_y);
	log_debug("params->layout_type = %d\n", params->layout_type);
	log_debug("led_params.pico_handle = 0x%x\n", led_params.pico_handle);
	log_debug("pico = 0x%x\n", pico);*/
	switch(params->layout_type){
		case 0:
            //220928 enhanece with cabinet height out of frame height
            //0310 test limit ok
            if((start_x < 0) || (start_y < 0)){
                log_debug("case 0 params config error!");
                break;
            }
            // 
            /*if((start_y - height + 1) > frame_height){
                log_debug("case 0 params config error!");
                break;
            }*/
            //cabinet height out of frame height
            /*if((start_y + height + 1) >= frame_height){
                log_debug("case 0 params config error!");
                break; 
            }*/
            if((start_x + width) > frame_width){
                log_debug("case 0 params config error!");
                break; 
            }
            config_err = false;
            
            memset(fake_pixel_buf, 0, channel_count);
			for(y = 0; y < height; y++){
                if(start_y + y >= frame_height){
					    for(i = 0 ; i < width; i ++){
						    memcpy(buf + offset, fake_pixel_buf, channel_count);
						    offset += channel_count;
					    } 
                }else{
	                if(y % 2 == 0){ //first line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + start_x*channel_count, 
							    width*channel_count);
					    offset += width*channel_count;
				    }else{ //second line
					    for(i = 0 ; i < width; i ++){
						    memcpy(buf + offset, 
								    pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x + width - i -1)*channel_count, 
								    channel_count);
						    offset += channel_count;
					    }
				    }
                }
			}
			break;
		case 1:
            //0304 test limit ok
            if((start_x < 0) || ((start_y - height + 1) < 0)){
                log_debug("case 1 params config error!");
                break;
            }
            /*if((start_y + 1 ) > frame_height){
                log_debug("case 1 params config error!");
                break;
            }*/
            /*if((start_x + width) > frame_width){
                log_debug("case 1 params config error!");
                break; 
            }*/
            config_err = false;
			for(y = 0; y < height; y++){
                if(y % 2 == 0){
					memcpy(buf + offset, 
							pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + start_x*channel_count, 
							width*channel_count);
					offset += width*channel_count; 
                }else{
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, 
								pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x + width - i -1)*channel_count, 
								channel_count);
						offset += channel_count;
					}
                    
                }
            }    
			break;
		case 2: 
            //0304 test limit ok
            if((start_x + 1 > frame_width)||(start_y < 0)){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_x - width + 1) < 0){
                log_debug("case 2 params config error!");
                break;
            }
            /*if((start_y + height - 1) > frame_height){
                log_debug("case 2 params config error!");
                break;
            }*/
            
            config_err = false;
			for(y = 0; y < height; y++){
	            if(y % 2 == 1){ 
					memcpy(buf + offset, 
							pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count, 
							width*channel_count);
					offset += width*channel_count;
				}else{ 
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, 
								pFrame->data[0] + ((start_y + y)*pFrame->linesize[0]) + (start_x - i )*channel_count, 
								channel_count);
						offset += channel_count;
					}
				}
			}
            
			break;
		case 3:
            //0310 test limit ok
            if((start_x + 1 > frame_width)||((start_y - height + 1) < 0)){
                log_debug("case 3 params config error!");
                break;
            }
            //cabinet height out of frame height
            /*if(start_y + 1 >= frame_height){
                log_debug("case 3 params config error!");
                break;
            }*/
            if((start_x - width + 1) < 0){
                log_debug("case 3 params config error!");
                break;
            }
            config_err = false;
            
			for(y = 0; y < height; y++){
                //cabinet height out of frame height
                if((start_y - y + 1) > frame_height){
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, fake_pixel_buf, channel_count);
						offset += channel_count;
					} 
                }else{
				    if(y % 2 == 0){ // first line
					    for(i = 0; i < width; i++){
						    memcpy(buf + offset,
								    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x -i)*channel_count,
								    channel_count);
						    offset += channel_count;
					    }
				    }else{ //second line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count,
							    width*channel_count);
					    offset += width*channel_count;
				    }
                }
			}
			break;
        case 4: 
            //0310 test limit ok
            if((start_x + 1 > frame_width)||(start_y < 0)){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_x - width + 1) < 0){
                log_debug("case 2 params config error!");
                break;
            }
            if((start_y + height - 1) > frame_height){
                log_debug("case 2 params config error!");
                break;
            }
            config_err = false;
            for(x = 0;x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - 1 - y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 5: //confirm @1115 
            //0310 test limit ok
            if((start_x < 0) || ((start_y - height + 1) < 0)){
                log_debug("case 5 params config error!");
                break;
            }
            if((start_y + 1 ) > frame_height){
                log_debug("case 5 params config error!");
                break;
            }
            if((start_x + width  ) > frame_width){
                log_debug("case 5 params config error!");
                break; 
            }
            config_err = false;
            for(x = 0; x < width; x++){
                if(x % 2 == 1){
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y + 1)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 6: //confirm @1115
            //0310 test limit ok
            if((start_x + 1 > frame_width)||((start_y - height + 1) < 0)){
                log_debug("case 6 params config error!");
                break;
            }
            if((start_y + 1) > frame_height){
                log_debug("case 6 params config error!");
                break;
            
            }
            if((start_x - width + 1) < 0){
                log_debug("case 6 params config error!");
                break;
            }
            config_err = false;
            #if 1
            //for(x = width;x > 0;x--){
            for(x = 0;x < width;x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - y)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y - height + y + 1)*pFrame->linesize[0] + (start_x - x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            #else
			for(y = 0; y < height; y++){
                //cabinet height out of frame height
                if((start_y - y + 1) > frame_height){
					for(i = 0 ; i < width; i ++){
						memcpy(buf + offset, fake_pixel_buf, channel_count);
						offset += channel_count;
					} 
                }else{
				    if(y % 2 == 0){ // first line
					    memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count,
							    width*channel_count);
					    offset += width*channel_count;
					    /*for(i = 0; i < width; i++){
						    memcpy(buf + offset,
								    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x -i)*channel_count,
								    channel_count);
						    offset += channel_count;
					    }*/
				    }else{ //second line
					    for(i = 0; i < width; i++){
						    memcpy(buf + offset,
								    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x -i)*channel_count,
								    channel_count);
						    offset += channel_count;
					    }
					    /*memcpy(buf + offset, 
							    pFrame->data[0] + ((start_y - y)*pFrame->linesize[0]) + (start_x - width + 1)*channel_count,
							    width*channel_count);
					    offset += width*channel_count;*/
				    }
                }
			}
            
            #endif
            break;
        case 7: //confirm @1115
            //0310 test limit ok
            if((start_x < 0) || (start_y < 0)){
                log_debug("case 7 params config error!");
                break;
            }
            if((start_y + height ) > frame_height){
                log_debug("case 7 params config error!");
                break;
            }
            if((start_x + width ) > frame_width){
                log_debug("case 7 params config error!");
                break; 
            }
            config_err = false;
            for(x = 0; x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y + 1)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + x)*channel_count,
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
	}


    if((width == 0)||(height == 0)){
        config_err = true;
    }

    if(config_err == true){
        // send zero while config error
        free(buf);
	    unsigned int tmp_buf_size = (1024*channel_count) + 4;
	    unsigned char *tmp_buf = malloc(tmp_buf_size);
	    sprintf(tmp_buf, "id%d:", params->port_id);
	    offset +=4;
        for(i = offset; i < tmp_buf_size; i ++){
            tmp_buf[i] = 0;
        }
	    if(pico != NULL){
            write_len = picousb_out_transfer(pico, tmp_buf, tmp_buf_size);
        }else{
            log_error("no pico");
            write_len = -ENODEV;
        }
        free(tmp_buf);
	    //free(buf);
	    free(fake_pixel_buf);
        log_debug(" id : %d, write_len : %d, params config error!\n", params->port_id, write_len);
        return write_len;
    }
    for(i = 4; i < offset; i ++){
        // frame_brightness : 0~100
        // frame_br_divisor : 0~100
        buf[i] =(char)((int)buf[i]*frame_brightness/(frame_br_divisor*100));
        buf[i] = g_GammaLut[buf[i]];
    }
	if(pico != NULL){
        //log_debug("ready to write pico!\n");
        write_len = picousb_out_transfer(pico, buf, buf_size);
        if(write_len < 0){
            int iret_reset_usb = reset_usb_device(pico);
            log_debug("reset pico error : %d\n", iret_reset_usb); 
            //pico = NULL;
            //free(pico);
            //pico = picousb_init();
        }
    }else{
        log_error("no pico");
        write_len = -ENODEV;
        if(write_len < 0){
            int iret_reset_usb = reset_usb_device(pico);
            log_debug("reset pico error : %d\n", iret_reset_usb);
        } 
    }
	free(buf);
	free(fake_pixel_buf);
	return write_len;
}
