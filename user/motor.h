/*
 * motor.h
 *
 *  Created on: 2026Äê3ÔÂ15ÈÕ
 *      Author: 26461
 */

#ifndef USER_MOTOR_H_
#define USER_MOTOR_H_

#include "Tianker.h"

#define RMIN1       (GPIO_Number_4)
#define RMIN2       (GPIO_Number_5)
#define LMIN1       (GPIO_Number_6)
#define LMIN2       (GPIO_Number_7)

void motor_init(void);
void motor1(int32_t duty);
void motor2(int32_t duty);

#endif /* USER_MOTOR_H_ */
