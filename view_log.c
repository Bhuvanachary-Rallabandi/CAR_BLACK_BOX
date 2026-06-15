/*
 * File:   view_log.c
 * Author: Bhuvanachary .R
 *
 * Created on 24 April, 2026, 6:50 PM
 */

#include "black_box.h"

extern unsigned char time[9], gear[2], speed[4], key;
extern unsigned short log_num, from, of_flag;
extern State_t state;
static short ind, pind = -1, flag = 0, count;

void view_log(void)
{
    key = read_switches(STATE_CHANGE);
//    if(key == MK_SW1 && count  > 0) count--;
//    else if(key == MK_SW2 && of_flag && count < 9) count++; 
//    else if(key == MK_SW2 && count < (log_num - 1)) count++;
//    else if(key == MK_SW12) {
//        count = 0;
//        state = e_main_menu;
//        clear_clcd();
//        return;
//    }
//    if(from) flag = from + count;
    
    if(key == MK_SW1 && ind  > 0) ind--;
    else if(key == MK_SW2 && ind < (log_num - 1)) ind++;
    else if(key == MK_SW12) {
        pind = -1;
        ind = 0;
        state = e_main_menu;
        clear_clcd();
        return;
    }
    if(ind == 9 )   clcd_putch('A', LINE2(0));
    else    clcd_putch((ind + '1'), LINE2(0));
    
    if(ind != pind) {
        pind = ind;
        gear[0] = read_internal_eeprom(ind * 10);
    
        speed[0] = read_internal_eeprom((ind * 10) + 1);
        speed[1] = read_internal_eeprom((ind * 10) + 2);
        speed[2] = read_internal_eeprom((ind * 10) + 3);

        time[0] = read_internal_eeprom((ind * 10) + 4);
        time[1] = read_internal_eeprom((ind * 10) + 5);
        time[2] = ':';
        time[3] = read_internal_eeprom((ind * 10) + 6);
        time[4] = read_internal_eeprom((ind * 10) + 7);
        time[5] = ':';
        time[6] = read_internal_eeprom((ind * 10) + 8);
        time[7] = read_internal_eeprom((ind * 10) + 9);

        clcd_print(gear, LINE2(2));
        clcd_print(speed, LINE2(4));
        clcd_print(time, LINE2(8));
    }
}