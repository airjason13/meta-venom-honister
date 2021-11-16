#ifndef _PICOUSB_H_
#define _PICOUSB_H_
#include <stdio.h>
#include "libusb.h"

#define BULK_EP_OUT     0x01
#define BULK_EP_IN      0x82


struct libusb_device_handle *picousb_init(void);
int picousb_out_transfer(struct libusb_device_handle *h, unsigned char *data, int len);
int picousb_in_transfer(struct libusb_device_handle *h, unsigned char *data, int len);
#endif
