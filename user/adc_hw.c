/*
 * adc_hw.c
 *
 *  Created on: 2026年3月19日
 *      Author: 26461
 */

#include "adc_hw.h"

void adc_init(void) {
	ADC_powerUp(myAdc);
	ADC_enableBandGap(myAdc);
	ADC_enableRefBuffers(myAdc);
    ADC_enable(myAdc);
	ADC_setVoltRefSrc(myAdc, ADC_VoltageRefSrc_Int);
	ADC_enableTempSensor(myAdc);//启用内部温度传感器

	ADC_setSocChanNumber(myAdc, ADC_SocNumber_0, ADC_SocChanNumber_A5); 
	ADC_setSocSampleWindow(myAdc, ADC_SocNumber_0, ADC_SocSampleWindow_7_cycles);
	ADC_setSocTrigSrc(myAdc, ADC_SocNumber_0, ADC_SocTrigSrc_CpuTimer_0); //设置触发源为CPU定时器0

}




/* 在 hw_init 中调用，初始化 GPIO 并启动 ADC 配置 */
void hw_init(void) {
    GPIO_setMode(myGpio, HW_EN, GPIO_0_Mode_GeneralPurpose);
    GPIO_setPullUp(myGpio, HW_EN, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, HW_EN, GPIO_Direction_Output);
    //使能红外传感器
    GPIO_setLow(myGpio, HW_EN);

}
