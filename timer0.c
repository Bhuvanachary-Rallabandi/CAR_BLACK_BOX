/*
 * File:   timer0.c
 * Author: Bhuvanachary .R
 *
 * Created on 25 April, 2026, 1:07 PM
 */

#include "black_box.h"

extern State_t state;
extern short toggle;
static unsigned int count = 0;

void init_timer0(void) {
    /*
     * Setting instruction cycle clock (Fosc / 4) as the source of
     * timer0
     */
    /*Setting 8 bit timer register*/
    T08BIT = 1;
    /* Selecting internal clock source */
    T0CS = 0;
    /* Enabling timer0*/
    TMR0ON = 1;
    /* disabling prescaler*/
    PSA = 1;
    TMR0 = 6;
    /* Clearing timer0 overflow interrupt flag bit */
    TMR0IF = 0;
    /* Enabling timer0 overflow interrupt */
    TMR0IE = 1;
}

void __interrupt() isr(){
    if(TMR0IF) {
        TMR0 = TMR0 + 8;
        if(state == e_set_time) {
            count++;
            if(count < 10000)
                toggle = 1;
            else if(count < 20000)
                toggle = 0;
            else
                count = 0;
        }
        else {
            count = 0;
            toggle = 0;
        }
        TMR0IF=0;
    }
}