/*
 * csb.c
 *
 *  Created on: 2026Äê4ÔÂ5ÈÕ
 *      Author: 26461
 */

#include "csb.h"

uint32_t dis = 0;

void trig(void){
    volatile uint16_t i;

    GPIO_setHigh(myGpio, csb_trig);
    for (i = 0; i < csb_us; i++) {
    }
    GPIO_setLow(myGpio, csb_trig);
}

void echo(void){
    static uint32_t time_start = 0;
    static uint32_t time_end = 0;
    uint32_t count = 0;
    while(!GPIO_getData(myGpio, csb_echo)){
        ++count;
        if(count > 100) break;
    }
    time_start = time1_us;
    while(GPIO_getData(myGpio, csb_echo)){
        if(time1_us - time_start > 10000) break;
    }
    time_end = time1_us;

    if(time_end != time_start)dis = time_end - time_start;
}

void csb_init(void){
    GPIO_setMode(myGpio, csb_trig, GPIO_18_Mode_GeneralPurpose);
    GPIO_setPullUp(myGpio, csb_trig, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, csb_trig, GPIO_Direction_Output);

    GPIO_setMode(myGpio, csb_echo, GPIO_19_Mode_GeneralPurpose);
    GPIO_setPullUp(myGpio, csb_echo, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, csb_echo, GPIO_Direction_Input);
    GPIO_setQualification(myGpio, csb_echo, GPIO_Qual_ASync);

    GPIO_setLow(myGpio, csb_trig);
}
