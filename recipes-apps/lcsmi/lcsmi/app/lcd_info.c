#include "lcd_info.h"


struct LCD_CONTENT *lcd_content_head = NULL;
struct LCD_CONTENT *lcd_content_current = NULL;

/************************************************************************
* function name :  unsigned int init_lcd_content(void)
* purpose       :  init the lcd_content with version at linking list head
* parameters    :  void
* return value  :  < 0 --> fail 
*                  > 0 pointer of the lcd_content
************************************************************************/
unsigned int init_lcd_content(char *version, char *mcu_version){
    lcd_content_head = malloc(sizeof(struct LCD_CONTENT));
    struct LCD_CONTENT *lcd_content = lcd_content_head;
    lcd_content->x = 0;
    lcd_content->y0 = 0;
    lcd_content->y1 = 1;
    sprintf(lcd_content->buf[0], "%s", version);
    sprintf(lcd_content->buf[1], "%s", mcu_version); 
    sprintf(lcd_content->tag, "%s%s", TAG_LCD_INFO, SUB_TAG_VERSION);
    lcd_content->pre = NULL;
    lcd_content->next = NULL;
    lcd_content->ishead = true;
    lcd_content_current = lcd_content_head;
    return lcd_content;
}

/************************************************************************
* function name :  int insert_lcd_content(char *data_0, char *data_1, char *tag, char *sub_tag)
* purpose       :  insert lcd content in linking list
* parameters    :  data_0 : line 0 content
                   data_1 : line 1 content
                   tag : lcd tag(info or error)
                   sub_tag :lcd sub tag(fps, version,...etc)
* return value  :  < 0 --> fail 
*                  > 0 pointer of the lcd_content
************************************************************************/
int insert_lcd_content(char *data_0, char *data_1, char *tag, char *sub_tag){
    log_debug("%s%s\n", tag, sub_tag);
    struct LCD_CONTENT *lc = lcd_content_head;
    if(lc == NULL){
        log_debug("no lcd1602 device!");
        return -ENODEV;
    }
    if((tag == NULL)||(sub_tag == NULL)){
        log_fatal("tag & sub_tag should not be NULL!\n");
        return -EINVAL;
    }
    struct LCD_CONTENT *lcd_content = malloc(sizeof(struct LCD_CONTENT));
    
    lcd_content->x = 0;
    lcd_content->y0 = 0;
    lcd_content->y1 = 1;
    if(data_0 != NULL){
        sprintf(lcd_content->buf[0], "%s", data_0);
    }
    if(data_1 != NULL){
        sprintf(lcd_content->buf[1], "%s", data_1);
    } 
    sprintf(lcd_content->tag, "%s%s", tag, sub_tag);
    
    for(;;){
        if(lc->next == NULL){
            lc->next = lcd_content;
            lcd_content->pre = lc;
            lcd_content->next = NULL;
            return 0;
        }else{
            lc = lc->next;
            if(lc == lcd_content_head){
                break;
            } 
        }     
    } 
    return -EINVAL;
}



/************************************************************************
* function name :  int refresh_lcd_content(char *tag, char *sub_tag, char *data_0, char *data_1)
* purpose       :  refresh lcd content in linking list
* parameters    :  data_0 : line 0 content
                   data_1 : line 1 content
                   tag : lcd tag(info or error)
                   sub_tag :lcd sub tag(fps, version,...etc)
* return value  :  < 0 --> fail 
*                  > 0 pointer of the lcd_content
************************************************************************/
int refresh_lcd_content(char *tag, char *sub_tag, char *data_0, char *data_1){
    struct LCD_CONTENT *lc = lcd_content_head;
    char buf[LCD_CONTENT_WIDTH];
    if(lc == NULL){
        log_debug("no lcd1602");
        return -ENODEV;
    }    
    sprintf(buf, "%s%s", tag, sub_tag);    
    for(;;){
        if(strstr(lc->tag, buf) != 0){
            if(data_0 != NULL){
                sprintf(lc->buf[0], "%s", data_0);
            }
            if(data_1 != NULL){
                sprintf(lc->buf[1], "%s", data_1);
            }
            return 0;
        }
        lc = lc->next;
        if(lc == NULL){
            return -EINVAL;
        }
    }
}


/************************************************************************
* function name :  int remove_lcd_content(char *tag, char *sub_tag)
* purpose       :  remove lcd content with tag
* parameters    :  tag : lcd tag(info or error)
*                  sub_tag :lcd sub tag(fps, version,...etc)
* return value  :  < 0 --> fail 
*                  > 0 pointer of the lcd_content
************************************************************************/
int remove_lcd_content(char *tag, char *sub_tag){
    struct LCD_CONTENT *lc = lcd_content_head;
    struct LCD_CONTENT *lc_pre, *lc_next;
    char buf[LCD_CONTENT_WIDTH];
    sprintf(buf, "%s%s", tag, sub_tag);    
    
    for(;;){
        if(strstr(lc->tag, buf) != 0){
            lc_pre = lc->pre;
            lc_next = lc->next;
            lc_pre->next = lc_next;
            lc_next->pre = lc_pre;
            free(lc);
            return 0;
        }
    
        lc = lc->next;
        if(lc == NULL){
            return -EINVAL;
        }
    }
}

/************************************************************************
* function name :  int lcd_display_handle(void)
* purpose       :  put this function into timer for lcd display routine
* parameters    :  void
* return value  :  < 0 --> fail 
*                  > 0 pointer of the lcd_content
************************************************************************/
int lcd_display_handle(void){
    struct LCD_CONTENT *lc = NULL;
    //if something error, only show the error content
    lc = lcd_content_head;
    for(;;){
        if(strstr(lc->tag, TAG_LCD_ERROR)){
            lcd_send_command(lc->x, lc->y0, lc->buf[0]);
            lcd_send_command(lc->x, lc->y1, lc->buf[1]);
            return 0;
        }
        if(lc->next == NULL){
            break;
        }else{
            lc = lc->next;
        }
    }

    //normal status
    lc = lcd_content_current;
    lcd_send_command(lc->x, lc->y0, lc->buf[0]);
    lcd_send_command(lc->x, lc->y1, lc->buf[1]);
    if(lc->next != NULL){
        lcd_content_current = lc->next;
    }else{
        lcd_content_current = lcd_content_head;
    }
    return 0;
}

/************************************************************************
* function name :  int lcd_start_routine(void)
* purpose       :  put lcd_display_handle into timer
* parameters    :  void
* return value  :  < 0 --> fail 
*                  > 0 pointer of the lcd_content
************************************************************************/
int lcd_start_routine(void){
    timer_t lcd_display_tid = jset_timer(1, 0, 3, 0, &(lcd_display_handle), 99);
    return 0;
}
