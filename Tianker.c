/*
 * Tianker.c
 *
 *  Created on: 2026年3月13日
 *      Author: 26461
 */
#include "Tianker.h"

CLK_Handle myClk;//    =   (CLK_Handle)0x00007010;
CPU_Handle myCpu;//    =   (CPU_Handle)0x00000000;
PLL_Handle myPll;//    =   (PLL_Handle)0x00007011;
PIE_Handle myPie;//	=	(PIE_Handle)0x00000CE0;
SCI_Handle mySci;
ADC_Handle myAdc;
PWM_Handle myPwm1;
PWM_Handle myPwm2;
PWM_Handle myPwm3;
PWM_Handle myPwm4;
WDOG_Handle myWDog;//  =   (WDOG_Handle)0x00007022;
GPIO_Handle myGpio;//	=	(GPIO_Handle)0x00006F80;
TIMER_Handle myTimer0;
TIMER_Handle myTimer1;
TIMER_Handle myTimer2;

uint32_t ms = 0;

void config(void){
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    mySci = SCI_init((void *)SCIA_BASE_ADDR, sizeof(SCI_Obj));
    myTimer0 = TIMER_init((void *)TIMER0_BASE_ADDR, sizeof(TIMER_Obj));
    myTimer1 = TIMER_init((void *)TIMER1_BASE_ADDR, sizeof(TIMER_Obj));
    myTimer2 = TIMER_init((void *)TIMER2_BASE_ADDR, sizeof(TIMER_Obj));
    myPwm1 = PWM_init((void *)PWM_ePWM1_BASE_ADDR, sizeof(PWM_Obj));
    myPwm2 = PWM_init((void *)PWM_ePWM2_BASE_ADDR, sizeof(PWM_Obj));
    myPwm3 = PWM_init((void *)PWM_ePWM3_BASE_ADDR, sizeof(PWM_Obj));
    myPwm4 = PWM_init((void *)PWM_ePWM4_BASE_ADDR, sizeof(PWM_Obj));
    myAdc = ADC_init((void *)ADC_BASE_ADDR, sizeof(ADC_Obj));

    WDOG_disable(myWDog);
    CPU_disableGlobalInts(myCpu);
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);
    PLL_setup(myPll, PLL_Multiplier_12, PLL_DivideSelect_ClkIn_by_2);

	CLK_enableGpioInputClock(myClk);//使能GPIO输入时钟
	CLK_enableAdcClock(myClk);
	CLK_enableCpuTimerClock(myClk, CLK_CpuTimerNumber_0);
	CLK_enableCpuTimerClock(myClk, CLK_CpuTimerNumber_1);
	CLK_enableCpuTimerClock(myClk, CLK_CpuTimerNumber_2);
    CLK_enablePwmClock(myClk, PWM_Number_1);
    CLK_enablePwmClock(myClk, PWM_Number_2);
    CLK_enablePwmClock(myClk, PWM_Number_3);
    CLK_enablePwmClock(myClk, PWM_Number_4);
    CLK_enableHrPwmClock(myClk);
    CLK_enableEcap1Clock(myClk);
    CLK_enableI2cClock(myClk);
    CLK_enableSciaClock(myClk);
    CLK_enableSpiaClock(myClk);
    CLK_enableCompClock(myClk, CLK_CompNumber_1);
    CLK_enableCompClock(myClk, CLK_CompNumber_2);
    CLK_enableCompClock(myClk, CLK_CompNumber_3);

	PIE_disable(myPie);//禁止PIE
	PIE_disableAllInts(myPie);//禁止PIE中断
	CPU_disableGlobalInts(myCpu);//CPU全局中断禁止
	CPU_clearIntFlags(myCpu);//CPU中断标志位清零
	PIE_setDefaultIntVectorTable(myPie);//中断入口地址赋予默认值
	PIE_enable(myPie);//使能PIE
}
