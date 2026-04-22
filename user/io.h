/*
 * io.h
 *
 *  Created on: 2026Äê3ÔÂ13ÈÕ
 *      Author: 26461
 */

#ifndef USER_IO_H_
#define USER_IO_H_

#include "Tianker.h"
#include "F2802x_Component/include/gpio.h"

#define LED_L_F     GPIO_Number_3
#define LED_L_B     GPIO_Number_1
#define LED_R_F     GPIO_Number_2
#define LED_R_B     GPIO_Number_0

extern GPIO_Number_e led[4];
extern bool half_flag;
extern bool led_mode;
extern uint16_t HXD_BC;

void io_init(bool mode);
void led_duty(GPIO_Number_e led, uint32_t duty);
void led_on(GPIO_Number_e led);
void led_off(GPIO_Number_e led);
void led_toggle(GPIO_Number_e led);
void all_led_on(void);
void all_led_off(void);
void half_led(void);
void hxd(void);

#endif /* USER_IO_H_ */
