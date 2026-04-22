/*
 * io.c
 *
 *  Created on: 2026年3月13日
 *      Author: 26461
 */
#include "io.h"

GPIO_Number_e led[4] = {LED_R_B, LED_L_B, LED_R_F, LED_L_F};
bool half_flag = 0;
bool led_mode = 0;
uint16_t HXD_BC = 1;

void hxd(void){
    static uint32_t lll = 0;
    static bool llf = 1;
    led_duty(GPIO_Number_0, lll);
    led_duty(GPIO_Number_1, lll);
    led_duty(GPIO_Number_2, lll);
    led_duty(GPIO_Number_3, lll);
    if(llf){
        if(lll < 5000) lll += HXD_BC;
        else llf = !llf;
    }else{
        if(lll > 10) lll -= HXD_BC;
        else llf = !llf;
    }
}

void half_led(void) {
    if (half_flag) {
        led_on(LED_R_B);
        led_on(LED_L_B);
        led_off(LED_R_F);
        led_off(LED_L_F);
    } else {
        led_off(LED_R_B);
        led_off(LED_L_B);
        led_on(LED_R_F);
		led_on(LED_L_F);
    }
}

void all_led_on(void) {
    uint16_t i;
    for (i = 0; i < 4; ++i) {
        led_on(led[i]);
    }
}

void all_led_off(void) {
    uint16_t i;
    for (i = 0; i < 4; ++i) {
        led_off(led[i]);
	}
}

void led_duty(GPIO_Number_e led, uint32_t duty){
    if(led == GPIO_Number_0) PWM_setCmpA(myPwm1, duty);
    else if(led == GPIO_Number_1) PWM_setCmpB(myPwm1, duty);
    else if(led == GPIO_Number_2) PWM_setCmpA(myPwm2, duty);
    else if(led == GPIO_Number_3) PWM_setCmpB(myPwm2, duty);
}

void led_on(GPIO_Number_e led){
    if(led_mode) GPIO_setLow(myGpio, led);
    else led_duty(led, 5000);
}
void led_off(GPIO_Number_e led){
    if(led_mode) GPIO_setHigh(myGpio, led);
    else led_duty(led, 0);
}
void led_toggle(GPIO_Number_e led){
    if(led_mode) GPIO_toggle(myGpio, led);
}

void io_init(bool mode){
    if(!mode){
        //设置GPIO为通用输入输出模式
        GPIO_setMode(myGpio, LED_R_B, GPIO_0_Mode_GeneralPurpose);
        GPIO_setMode(myGpio, LED_L_B, GPIO_1_Mode_GeneralPurpose);
        GPIO_setMode(myGpio, LED_R_F, GPIO_2_Mode_GeneralPurpose);
        GPIO_setMode(myGpio, LED_L_F, GPIO_3_Mode_GeneralPurpose);
        //设置GPIO为推挽输出
        GPIO_setPullUp(myGpio, LED_R_B, GPIO_PullUp_Disable);
        GPIO_setPullUp(myGpio, LED_L_B, GPIO_PullUp_Disable);
        GPIO_setPullUp(myGpio, LED_R_F, GPIO_PullUp_Disable);
        GPIO_setPullUp(myGpio, LED_L_F, GPIO_PullUp_Disable);
        //设置GPIO为输出
        GPIO_setDirection(myGpio, LED_R_B, GPIO_Direction_Output);
        GPIO_setDirection(myGpio, LED_L_B, GPIO_Direction_Output);
        GPIO_setDirection(myGpio, LED_R_F, GPIO_Direction_Output);
        GPIO_setDirection(myGpio, LED_L_F, GPIO_Direction_Output);

    }else{
        GPIO_setMode(myGpio, LED_R_B, GPIO_0_Mode_EPWM1A);
        GPIO_setMode(myGpio, LED_L_B, GPIO_1_Mode_EPWM1B);
        GPIO_setMode(myGpio, LED_R_F, GPIO_2_Mode_EPWM2A);
        GPIO_setMode(myGpio, LED_L_F, GPIO_3_Mode_EPWM2B);

        int pin;
        for (pin = GPIO_Number_0; pin <= GPIO_Number_3; ++pin) {
            GPIO_setPullUp(myGpio, (GPIO_Number_e)pin, GPIO_PullUp_Disable);
            GPIO_setDirection(myGpio, (GPIO_Number_e)pin, GPIO_Direction_Output);
            GPIO_setQualification(myGpio, (GPIO_Number_e)pin, GPIO_Qual_ASync);
        }

        CLK_disableTbClockSync(myClk);

        const uint16_t TBPRD = 6000;
        PWM_Handle pwmList[] = { myPwm1, myPwm2, myPwm3, myPwm4 };
        int i;
        for (i = 0; i < 2; ++i) {
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

        PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1, &pwm1);
        PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_2, &pwm2);

        PWM_enableInt(myPwm1);
        PWM_enableInt(myPwm2);
        PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM1);
        PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM2);

        CPU_enableInt(myCpu, CPU_IntNumber_3);

    }

    led_mode = !mode;

    led_off(LED_R_B);
    led_off(LED_L_B);
    led_off(LED_R_F);
    led_off(LED_L_F);

}


