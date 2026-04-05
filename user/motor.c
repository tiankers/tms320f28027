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
    // Two groups of four PWM outputs: ePWM1(A/B), ePWM2(A/B), ePWM3(A/B), ePWM4(A/B)
    // Map GPIO0..7 to EPWM1A..EPWM4B
    //GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_EPWM1A);
    //GPIO_setMode(myGpio, GPIO_Number_1, GPIO_1_Mode_EPWM1B);
    //GPIO_setMode(myGpio, GPIO_Number_2, GPIO_2_Mode_EPWM2A);
    //GPIO_setMode(myGpio, GPIO_Number_3, GPIO_3_Mode_EPWM2B);
    GPIO_setMode(myGpio, GPIO_Number_4, GPIO_4_Mode_EPWM3A);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_EPWM3B);
    GPIO_setMode(myGpio, GPIO_Number_6, GPIO_6_Mode_EPWM4A);
    GPIO_setMode(myGpio, GPIO_Number_7, GPIO_7_Mode_EPWM4B);

    // Disable pull-ups and set direction/qualification (explicit, safe)
    int pin;
    for (pin = GPIO_Number_4; pin <= GPIO_Number_7; ++pin) {
        GPIO_setPullUp(myGpio, (GPIO_Number_e)pin, GPIO_PullUp_Disable);
        GPIO_setDirection(myGpio, (GPIO_Number_e)pin, GPIO_Direction_Output);
        GPIO_setQualification(myGpio, (GPIO_Number_e)pin, GPIO_Qual_ASync);
    }

    // Disable TBCLK sync while configuring
    CLK_disableTbClockSync(myClk);

    // Common PWM parameters
    const uint16_t TBPRD = 6000; // example: 6000 TBCLK -> ~100us (verify with SYSCLK/TBCLK)
    /* Configure ePWM1..ePWM4 similarly */
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

        // Default safe output: keep outputs low at start
        PWM_setActionQual_Zero_PwmA(pwmList[i], PWM_ActionQual_Clear);
        PWM_setActionQual_CntUp_CmpA_PwmA(pwmList[i], PWM_ActionQual_Set);
        PWM_setActionQual_Zero_PwmB(pwmList[i], PWM_ActionQual_Clear);
        PWM_setActionQual_CntUp_CmpB_PwmB(pwmList[i], PWM_ActionQual_Set);

        // Ensure period event clears outputs
        PWM_setActionQual_Period_PwmA(pwmList[i], PWM_ActionQual_Clear);
        PWM_setActionQual_Period_PwmB(pwmList[i], PWM_ActionQual_Clear);

        // Initialize compare registers to TBPRD so effective duty is 0% at startup
        PWM_setCmpA(pwmList[i], PWM_getPeriod(pwmList[i]));
        PWM_setCmpB(pwmList[i], PWM_getPeriod(pwmList[i]));
    }

    // Re-enable TBCLK sync after configuration
    CLK_enableTbClockSync(myClk);

    // Interrupts: keep original behaviour for ePWM3/4 if used elsewhere
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1, &pwm3);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_2, &pwm4);

    PWM_enableInt(myPwm3);
    PWM_enableInt(myPwm4);
    PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM3);
    PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM4);

    CPU_enableInt(myCpu, CPU_IntNumber_3);
}


