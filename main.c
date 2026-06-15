/*
 * File:   main.c
 * Author: Bhuvanachary .R
 *
 * Created on 22 April, 2026, 10:39 PM
 */

#include "black_box.h"

State_t state;
unsigned char key = 0XFF;
short index;
unsigned short log_num, from, of_flag;

void init_config()
{
    init_adc();
    init_clcd();
    init_i2c();
    init_uart();
    init_timer0();
    init_ds1307();
    init_matrix_keypad();
    state = e_dashboard;
}

void main(void) 
{
    init_config();
    while(1)
    {
        // Detect key press
        switch (state)
        {
            case e_dashboard:
                clcd_print("GR SPD   TIME   ", LINE1(0));
                view_dashboard();
                break;
            
            case e_main_menu:
                clcd_print("-> ",LINE1(0));
                clcd_print("   ",LINE2(0));
                display_main_menu();
                break;
            
            case e_view_log:
                if(!log_num) clcd_print("    Log Empty   ", LINE1(0));
                else {
                    clcd_print("#GR SPD   TIME  ", LINE1(0));
                    view_log();
                }
                break;
                
            case e_set_time:
                clcd_print("    HH:MM:SS    ", LINE1(0));
                set_time();
                break;
                
            case e_download_log:
                if(!log_num) puts("\r\nLog is EMPTY!\r\n");
                else {
                    puts("\r\n SI.NO   SPEED  GEAR    TIME  \r\n");
                    puts("------------------------------\r\n");
                    download_log();
                }
                state = e_main_menu;
                __delay_ms(3000);
                clear_clcd();
                break;
                
            case e_clear_log:
//              clear_log();                
                log_num = 0;
                clcd_print(" LOG CLEARED    ", LINE1(0));
                clcd_print("   SUCCESSFULLY ", LINE2(0));
                state = e_main_menu;
                __delay_ms(1000);
                clear_clcd();
                break;
        }   
    }    
}

void clear_clcd(void){
    clcd_print("                ", LINE1(0));
    clcd_print("                ", LINE2(0));
}