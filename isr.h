/*
 * isr.h
 *
 *  Created on: 2026Äê3ÔÂ14ÈÕ
 *      Author: 26461
 */

#ifndef ISR_H_
#define ISR_H_

#include "Tianker.h"

extern bool key_pie;
extern bool rx_pie;

void pie_init(void);
interrupt void XINT1_isr(void);
interrupt void timer0_isr(void);
interrupt void timer1_isr(void);
interrupt void timer2_isr(void);
interrupt void pwm3(void);
interrupt void pwm4(void);
#endif /* ISR_H_ */
