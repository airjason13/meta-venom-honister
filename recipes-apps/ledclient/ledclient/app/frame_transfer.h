#ifndef _FRAME_TRANSFER_H_
#define _FRAME_TRANSFER_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utildbg.h"
#include "cabinetutils.h"
#include "frame.h"
#include "picousb.h"
#include "ledlayout.h"
#include "math.h"

int transfer_framergb_to_pico(AVFrame *pFrame, struct cabinet_params *params, int channel_count, int frame_width, int frame_height, struct libusb_device_handle *pico, char *input_uri);
int set_frame_brightness_value(int value);
int get_frame_brightness_value();
int set_frame_br_divisor_value(int value);
int get_frame_br_divisor_value();
int set_frame_gamma_value(float fvalue);
#endif
