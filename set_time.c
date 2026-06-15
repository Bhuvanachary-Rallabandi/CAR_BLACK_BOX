/*
 * File:   set_time.c
 * Author: Bhuvanachary .R
 *
 * Created on 25 April, 2026, 11:57 AM
 */

#include "black_box.h"

static unsigned short hr, min, sec, field; 
extern unsigned char key;
unsigned char hr_str[3], min_str[3], sec_str[3];
extern State_t state;
short toggle;

void set_time(void)
{
    
    key = read_switches(STATE_CHANGE);
    if(key == MK_SW11) {
        
        unsigned char hour, minute, second;
        second = bcd_converter(sec);
        minute = bcd_converter(min);
        hour = bcd_converter(hr);

        write_ds1307(SEC_ADDR, second);
        write_ds1307(MIN_ADDR, minute);
        write_ds1307(HOUR_ADDR, hour);
        
        clcd_print("  TIME SET      ", LINE1(0));
        clcd_print("   SUCCESSFULLY ", LINE2(0));
        __delay_ms(1000);
        hr = min = sec = field = 0;
        state = e_main_menu;
        clear_clcd();
        return;
    }
    
    hr_str[2] = min_str[2] = sec_str[2] = '\0';
    hr_str[1] = (hr%10) + '0';  hr_str[0] = (hr/10) + '0';
    min_str[1] = (min%10) + '0';    min_str[0] = (min/10) + '0';
    sec_str[1] = (sec%10) + '0';    sec_str[0] = (sec/10) + '0';
    
    clcd_print(hr_str, LINE2(4));
    clcd_print(":", LINE2(6));
    clcd_print(min_str, LINE2(7));
    clcd_print(":", LINE2(9));
    clcd_print(sec_str, LINE2(10));
    
    if(toggle) {
        if(field == 2) clcd_print("  ",LINE2(10));
        else if(field == 1) clcd_print("  ",LINE2(7));
        else if(field == 0) clcd_print("  ",LINE2(4));
    }
    
    if(key == MK_SW1) {
        field++;
        if(field > 2) field = 0;
    }
    else if(key == MK_SW2) {
        if(field == 2) {
            sec++;
            if(sec > 59) sec = 0;
        }
        else if(field == 1) {
            min++;
            if(min > 59) min = 0;
        }
        else if(field == 0) {
            hr++;
            if(hr > 23) hr = 0;
        }
    }
}

unsigned char  bcd_converter(unsigned short num)
{
    unsigned char ch = 0;
    ch = (num/10) | ch;
    ch = ch << 4;
    ch = (num%10) | ch;
    return ch;
}