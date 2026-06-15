/*
 * File:   display_main_menu.c
 * Author: Bhuvanachary .R
 *
 * Created on 24 April, 2026, 10:51 AM
 */

#include "black_box.h"

extern unsigned char key;
extern State_t state;
extern short index;

void display_main_menu()
{
    unsigned char *menu[] = {"View Log     ", "Set Time     ", "Download Log ", "Clear Log    ", "     "};
    key = read_switches(STATE_CHANGE);
    if(key == MK_SW12){
        state = e_dashboard;
        clear_clcd();
        return;
    }
    if(key == MK_SW11){
        clear_clcd();
        state = index + 2;
        return;
    }
    if(key == MK_SW1 && index < 3) index++;
    else if(key == MK_SW2 && index > 0) index--;
    clcd_print(menu[index], LINE1(3));
    clcd_print(menu[index + 1], LINE2(3));  
}