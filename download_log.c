/*
 * File:   download_log.c
 * Author: Bhuvanachary .R
 *
 * Created on 25 April, 2026, 10:34 AM
 */

#include "black_box.h"

extern unsigned short log_num;
extern State_t state;

void download_log(void)
{
    unsigned short ind = 0;
    char si_no[10] = {"         "}, speed[8] = {"       "}, gear[7] = {"      "}, time[9] = {"        "};
    for(; ind < log_num; ind++) {
        if (ind == 9) {
            si_no[3] = '1';
            si_no[4] = '0';
        }
        else {
            si_no[3] = ind + '1';
            si_no[4] = ' ';
        }
        
        gear[1] = 'G'; 
        gear[2] = read_internal_eeprom(ind * 10);

        speed[1] = read_internal_eeprom((ind * 10) + 1);
        speed[2] = read_internal_eeprom((ind * 10) + 2);
        speed[3] = read_internal_eeprom((ind * 10) + 3);

        time[0] = read_internal_eeprom((ind * 10) + 4);
        time[1] = read_internal_eeprom((ind * 10) + 5);
        time[2] = ':';
        time[3] = read_internal_eeprom((ind * 10) + 6);
        time[4] = read_internal_eeprom((ind * 10) + 7);
        time[5] = ':';
        time[6] = read_internal_eeprom((ind * 10) + 8);
        time[7] = read_internal_eeprom((ind * 10) + 9);
        
        puts(si_no);
        puts(speed);
        puts(gear);
        puts(time);
        puts("\r\n");
    }
    puts("-------------xxx--------------\r\n");
    clcd_print(" Download       ", LINE1(0));
    clcd_print("      Completed ", LINE2(0));    
}