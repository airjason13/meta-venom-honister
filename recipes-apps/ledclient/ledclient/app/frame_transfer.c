#include "frame_transfer.h"

extern struct ledparams led_params;
int divisor = 32;

int transfer_framergb_to_pico(AVFrame *pFrame, struct cabinet_params *params, int channel_count, struct libusb_device_handle *pico){
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
	if(buf == NULL){
		log_fatal("malloc failed!\n");
		return -ENOMEM;
	}
	sprintf(buf, "id%d:", params->port_id);
	offset +=4;
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
			for(y = 0; y < height; y++){
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
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			for(y = 0; y < height; y++){
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
			break;
#if 0
        case 4:
            for(x = 0; x < width; x++){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x + x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 5: 
            for(x = width; x > 0; x--){
                if(x % 2 == 0){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x + width -x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + width - x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            break;
        case 6:
            for(x = width; x > 0; x--){
                if(x % 2 == 1){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x + width -x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + width - x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    } 
                }
            }
            
            break;
        case 7:
            for(x = 0; x < width; x++){
                if(x % 2 == 1){
                    for(y = 0; y < height; y++){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + y)*pFrame->linesize[0] + (start_x + x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    }
                }else{
                    for(y = height; y > 0; y--){
                        memcpy(buf + offset,
                                pFrame->data[0] + (start_y + height - y)*pFrame->linesize[0] + (start_x + x)*channel_count),
                                channel_count);
                        offset += channel_count;
                    
                    } 
                }
            }
            
            break;
#endif
	}
    for(i = 4; i < offset; i ++){
        buf[i] = buf[i]/divisor;
    }
	if(pico != NULL){
		//log_debug("offset = %d\n", offset);
        write_len = picousb_out_transfer(pico, buf, buf_size);
        //log_debug("write_len = %d\n", write_len);
    }else{
        log_error("no pico");
    }
	free(buf);
	return 0;
}