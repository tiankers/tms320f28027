/*
 * csb.h
 *
 *  Created on: 2026Äê4ÔÂ5ÈÕ
 *      Author: 26461
 */

#ifndef USER_CSB_H_
#define USER_CSB_H_

#include "Tianker.h"

#define csb_trig            (GPIO_Number_18)
#define csb_echo            (GPIO_Number_19)

#define csb_us              (62)

extern uint32_t dis;

void csb_init(void);
void trig(void);
void echo(void);

#endif /* USER_CSB_H_ */
