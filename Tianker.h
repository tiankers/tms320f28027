/*
 * Tianker.h
 *
 *  Created on: 2026年3月13日
 *      Author: 26461
 */

#ifndef TIANKER_H_
#define TIANKER_H_

//官方驱动层
#include "F2802x_Component/include/adc.h"
#include "F2802x_Component/include/clk.h"
#include "F2802x_Component/include/flash.h"
#include "F2802x_Component/include/gpio.h"
#include "F2802x_Component/include/pie.h"
#include "F2802x_Component/include/pll.h"
#include "F2802x_Component/include/timer.h"
#include "F2802x_Component/include/wdog.h"
#include "F2802x_Component/include/pwm.h"
#include "F2802x_Component/include/cap.h"
#include "F2802x_Component/include/sci.h"

//用户层
#include "Delay.h"
#include "isr.h"
#include "time.h"
#include "io.h"
#include "key.h"
#include "motor.h"
#include "adc_hw.h"

extern CLK_Handle myClk;
extern CPU_Handle myCpu;
extern PLL_Handle myPll;
extern PIE_Handle myPie;
extern ADC_Handle myAdc;
extern PWM_Handle myPwm1;
extern PWM_Handle myPwm2;
extern PWM_Handle myPwm3;
extern PWM_Handle myPwm4;
extern WDOG_Handle myWDog;
extern GPIO_Handle myGpio;
extern TIMER_Handle myTimer0;
extern TIMER_Handle myTimer1;
extern TIMER_Handle myTimer2;

void config(void);

#endif /* TIANKER_H_ */
