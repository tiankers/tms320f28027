/*
 * isr.c
 *
 *  Created on: 2026年3月14日
 *      Author: 26461
 */

#include "isr.h"

bool key_pie = 0;
bool rx_pie = 0;

interrupt void XINT1_isr(void){

    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

interrupt void timer0_isr(void){
    ++ms;
    static uint32_t kkk = 0;
    if(ms - kkk > 10){
        //
        uint16_t i = 0;
        for (; i < 8; ++i) {
            adc_val[i] = ADC_readResult(myAdc, (ADC_ResultNumber_e)(i + 1));
        }
        a5 = ADC_readResult(myAdc, ADC_ResultNumber_0);
        //
        get_key_down();
        key_get(&KEY_1);
        key_get(&KEY_2);
        key_get(&KEY_3);
        key_even(&KEY_1);
        key_even(&KEY_2);
        key_even(&KEY_3);
        //
        kkk = ms;
    }

    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

interrupt void timer1_isr(void) {
    time1_us++;
}

interrupt void timer2_isr(void) {
    time2_us++;
}

interrupt void pwm3(void){

	PWM_clearIntFlag(myPwm3); //清除PWM3的中断标志
	PIE_clearInt(myPie, PIE_GroupNumber_3);
}
interrupt void pwm4(void){

    PWM_clearIntFlag(myPwm4); //清除PWM4的中断标志
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

void pie_init(void){
    if(key_pie){
		PIE_setExtIntPolarity(myPie, CPU_ExtIntNumber_1, PIE_ExtIntPolarity_RisingEdge);//设置外部中断1为上升沿触发
		GPIO_setExtInt(myGpio, key_1, CPU_ExtIntNumber_1);//将GPIO引脚与外部中断1关联

		PIE_enableExtInt(myPie, CPU_ExtIntNumber_1);//使能外部中断1
		PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_XINT_1);//使能PIE组1的外部中断1
		CPU_enableInt(myCpu, CPU_IntNumber_1);//使能CPU中断1（对应PIE组1）
    }
    //注册外部中断1的中断服务函数
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_4, (intVec_t)XINT1_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_7, (intVec_t)timer0_isr);
    PIE_registerSystemIntHandler(myPie, PIE_SystemInterrupts_TINT1, (intVec_t)timer1_isr);
    PIE_registerSystemIntHandler(myPie, PIE_SystemInterrupts_TINT2, (intVec_t)timer2_isr);


	CPU_enableGlobalInts(myCpu);//使能全局中断
}

