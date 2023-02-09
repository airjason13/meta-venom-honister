#ifndef _RPI_SMI_J_
#define _RPI_SMI_J_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "rpi_smi_defs.h"
#include "rpi_mem_j.h"

int init_rpi_smi(void);
int rpi_set_smi_chan_led_count(int led_count);
int rpi_start_smi(void);
void smi_terminate(int sig);
void set_test_buffer(int color);
#endif
