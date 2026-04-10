/*
 * motor.c
 *
 *  Created on: 2026Äê3ÔÂ15ÈÕ
 *      Author: 26461
 */
#include "motor.h"

void motor1(int32_t duty) {
	if (duty >= 0) {
        PWM_setCmpA(myPwm3, 0);
        PWM_setCmpB(myPwm3, (uint16_t)(-duty));
	}
	else {
        PWM_setCmpA(myPwm3, (uint16_t)duty);
        PWM_setCmpB(myPwm3, 0);
	}
}
void motor2(int32_t duty) {
	if (duty >= 0) {
        PWM_setCmpA(myPwm4, 0);
        PWM_setCmpB(myPwm4, (uint16_t)(-duty));
	}
	else {
        PWM_setCmpA(myPwm4, (uint16_t)duty);
        PWM_setCmpB(myPwm4, 0);
	}
}

void motor_init(void){
    GPIO_setMode(myGpio, GPIO_Number_4, GPIO_4_Mode_EPWM3A);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_EPWM3B);
    GPIO_setMode(myGpio, GPIO_Number_6, GPIO_6_Mode_EPWM4A);
    GPIO_setMode(myGpio, GPIO_Number_7, GPIO_7_Mode_EPWM4B);

    int pin;
    for (pin = GPIO_Number_4; pin <= GPIO_Number_7; ++pin) {
        GPIO_setPullUp(myGpio, (GPIO_Number_e)pin, GPIO_PullUp_Disable);
        GPIO_setDirection(myGpio, (GPIO_Number_e)pin, GPIO_Direction_Output);
        GPIO_setQualification(myGpio, (GPIO_Number_e)pin, GPIO_Qual_ASync);
    }

    CLK_disableTbClockSync(myClk);

    const uint16_t TBPRD = 6000; 
    PWM_Handle pwmList[] = { myPwm1, myPwm2, myPwm3, myPwm4 };
    int i;
    for (i = 2; i < 4; ++i) {
        PWM_setHighSpeedClkDiv(pwmList[i], PWM_HspClkDiv_by_1);
        PWM_setClkDiv(pwmList[i], PWM_ClkDiv_by_1);
        PWM_setCounterMode(pwmList[i], PWM_CounterMode_Up);
        PWM_setPeriod(pwmList[i], TBPRD);
        PWM_setPeriodLoad(pwmList[i], PWM_PeriodLoad_Shadow);

        PWM_setShadowMode_CmpA(pwmList[i], PWM_ShadowMode_Shadow);
        PWM_setShadowMode_CmpB(pwmList[i], PWM_ShadowMode_Shadow);
        PWM_setLoadMode_CmpA(pwmList[i], PWM_LoadMode_Zero);
        PWM_setLoadMode_CmpB(pwmList[i], PWM_LoadMode_Zero);

        PWM_setActionQual_Zero_PwmA(pwmList[i], PWM_ActionQual_Clear);
        PWM_setActionQual_CntUp_CmpA_PwmA(pwmList[i], PWM_ActionQual_Set);
        PWM_setActionQual_Zero_PwmB(pwmList[i], PWM_ActionQual_Clear);
        PWM_setActionQual_CntUp_CmpB_PwmB(pwmList[i], PWM_ActionQual_Set);

        PWM_setActionQual_Period_PwmA(pwmList[i], PWM_ActionQual_Clear);
        PWM_setActionQual_Period_PwmB(pwmList[i], PWM_ActionQual_Clear);

        PWM_setCmpA(pwmList[i], PWM_getPeriod(pwmList[i]));
        PWM_setCmpB(pwmList[i], PWM_getPeriod(pwmList[i]));
    }

    CLK_enableTbClockSync(myClk);

    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1, &pwm3);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_2, &pwm4);

    PWM_enableInt(myPwm3);
    PWM_enableInt(myPwm4);
    PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM3);
    PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM4);

    CPU_enableInt(myCpu, CPU_IntNumber_3);
}


