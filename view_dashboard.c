/*
 * File:   view_db.c
 * Author: Bhuvanachary .R
 *
 * Created on 23 April, 2026, 9:53 AM
 */

#include "black_box.h"

unsigned char clock_reg[3], time[9], gear[2], speed[4];
extern unsigned char key;
static unsigned short gr, spd, pgr = -1;
extern unsigned short log_num, from, of_flag;
extern State_t state;
extern short index;

static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

void view_dashboard(void)
{
    key = read_switches(STATE_CHANGE);
    if(key == MK_SW11) {
        index = 0;
        state = e_main_menu;
        clear_clcd();
    }
    else {
        if(key == MK_SW1 && gr < 6) gr++;
        else if(key == MK_SW2 && gr > 0) gr--;
        if(gr == 0) gear[0] = 'N';
        else if(gr == 6) gear[0] = 'R';
        else gear[0] = gr + '0';
        gear[1] = '\0';

        if(gr) spd = read_adc(CHANNEL4)/10.23;
        else spd = 0;
        speed[2] = (spd%10) + '0';
        spd = spd/10;
        short i = 1;
        while(spd > 0 && i >= 0) {
            speed[i--] = (spd%10) + '0';
            spd = spd/10;
        }
        while(i >= 0) speed[i--] = ' ';
        speed[3] = '\0';

        get_time();

        clcd_print(gear, LINE2(1));
        clcd_print(speed, LINE2(3));
        clcd_print(time, LINE2(7));
    }  
    if(gr != pgr){
        pgr = gr;
//        if(log_num == 10) {
//            char ch;
//            for(short i = 0; i < 90; i++) {
//                ch = read_internal_eeprom(i + 10);
//                write_internal_eeprom(i, ch);
//            }
//            log_num--;
//        }
//        if(log_num == 10) {
//            log_num = 0;
//            if(!of_flag)  of_flag = 1;
//        }
//        if(of_flag) {
//            if(from == 9) from = 0;
//            else from = log_num + 1;
//        }

        write_internal_eeprom(log_num * 10, gear[0]);
        write_internal_eeprom((log_num * 10) + 1, speed[0]);
        write_internal_eeprom((log_num * 10) + 2, speed[1]);
        write_internal_eeprom((log_num * 10) + 3, speed[2]);
        write_internal_eeprom((log_num * 10) + 4, time[0]);
        write_internal_eeprom((log_num * 10) + 5, time[1]);
        write_internal_eeprom((log_num * 10) + 6, time[3]);
        write_internal_eeprom((log_num * 10) + 7, time[4]);
        write_internal_eeprom((log_num * 10) + 8, time[6]);
        write_internal_eeprom((log_num * 10) + 9, time[7]);
        log_num++;
    }
}