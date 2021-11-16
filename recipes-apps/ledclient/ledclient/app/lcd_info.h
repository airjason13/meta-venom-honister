#ifndef _LCD_INFO_H_
#define _LCD_INFO_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "utildbg.h"
#include "jtimer.h"
#include "lcdcli.h"

#define LCD_CONTENT_WIDTH           16
#define LCD_CONTENT_HEIGHT          2
#define TAG_LCD_INFO                "INFO_"
#define SUB_TAG_VERSION             "VERSION"
#define SUB_TAG_FPS                 "FPS"

#define TAG_LCD_ERROR               "ERROR_"
#define SUB_TAG_NOPICO              "NOPICO"
struct LCD_CONTENT{
    int x;
    int y0;
    int y1;
    char buf[LCD_CONTENT_HEIGHT][LCD_CONTENT_WIDTH];
    char tag[LCD_CONTENT_WIDTH];
    struct LCD_CONTENT *pre;
    struct LCD_CONTENT *next;
    bool ishead;    
};

unsigned int init_lcd_content(char *version, char *mcu_version);
int insert_lcd_content(char *data_0, char *data_1, char *tag, char *sub_tag);
int refresh_lcd_content(char *tag, char *sub_tag, char *data_0, char *data_1);
int lcd_display_handle(void);
int lcd_start_routine(void);
#endif
