/*
 * jdy.c
 *
 *  Created on: 2026Äê4ÔÂ8ÈÕ
 *      Author: 26461
 */

#include "jdy.h"

void jdy_init(void) {
	ADC_setSocChanNumber(myAdc, ADC_SocNumber_10, JDY_STAT);
	ADC_setSocSampleWindow(myAdc, ADC_SocNumber_10, ADC_SocSampleWindow_7_cycles);
	ADC_setSocTrigSrc(myAdc, ADC_SocNumber_10, ADC_SocTrigSrc_CpuTimer_0);

    GPIO_setMode(myGpio, JDY_PWRC, GPIO_17_Mode_GeneralPurpose);
    GPIO_setPullUp(myGpio, JDY_PWRC, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, JDY_PWRC, GPIO_Direction_Output);

	GPIO_setLow(myGpio, JDY_PWRC);
}



