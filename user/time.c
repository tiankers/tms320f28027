/*
 * time.c
 *
 *  Created on: 2026Äê3ÔÂ15ÈÕ
 *      Author: 26461
 */
#include "time.h"

uint32_t time1_us = 0;
uint32_t time2_us = 0;

void timer_init(TIMER_Handle Timerx, uint32_t us){
    TIMER_stop(Timerx);
    TIMER_setPreScaler(Timerx, 1);
    TIMER_setPeriod(Timerx, (60L * us) - 1);
    TIMER_reload(Timerx);
    TIMER_start(Timerx);
}

void time_pie_us(TIMER_Handle Timerx, uint32_t us){
    timer_init(Timerx, us);

    TIMER_enableInt(Timerx);

    if (Timerx == myTimer0) {
            PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_TIMER_0);
            CPU_enableInt(myCpu, CPU_IntNumber_1);
    }else if (Timerx == myTimer1) {
        CPU_enableInt(myCpu, CPU_IntNumber_13);
    }else if (Timerx == myTimer2) {
        CPU_enableInt(myCpu, CPU_IntNumber_14);
    }
}


