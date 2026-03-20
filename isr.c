/*
 * isr.c
 *
 *  Created on: 2026年3月14日
 *      Author: 26461
 */

#include "isr.h"

bool key_pie = 0;

interrupt void KEY_XINT1_isr(void){

    motor_flag = (motor_flag) ? 0 : 1;

    static uint16_t aaa = 0;
    led_on(led[aaa]);
    if(aaa == 0)led_off(led[3]);
    else led_off(led[aaa - 1]);
    aaa = (aaa < 3) ? aaa + 1 : 0;

    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

interrupt void timer0_isr(void){
    led_toggle(LED_R_F);

    PIE_clearInt(myPie, PIE_GroupNumber_1);
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
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_4, (intVec_t)KEY_XINT1_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_7, (intVec_t)timer0_isr);



	CPU_enableGlobalInts(myCpu);//使能全局中断
}

