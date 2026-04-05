/*
 * time.h
 *
 *  Created on: 2026Äê3ÔÂ15ÈÕ
 *      Author: 26461
 */

#ifndef USER_TIME_H_
#define USER_TIME_H_

#include "Tianker.h"

extern uint32_t time1_us;
extern uint32_t time2_us;

void timer_init(TIMER_Handle Timerx, uint32_t us);
void time_pie_us(TIMER_Handle Timerx, uint32_t us);

#endif /* USER_TIME_H_ */
