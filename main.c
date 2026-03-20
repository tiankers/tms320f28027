/**
 * main.c
 */
#include "Tianker.h"

void main(void)
{
    //系统初始化
    config();

    //用户初始化
    io_init();
    key_init();
    motor_init();
    hw_init();

    time_pie_us(myTimer0, 1000000);
    //中断
    pie_init();

    for(;;){
        //code begin
        if(motor_flag){
            motor1(1000);
            motor2(1000);
        }else{
            motor1(0);
            motor2(0);

        }
//        led_toggle(LED_R_F);
//        delay_ms(50);
//        if(key_down) led_on(LED_R_F);
//        else led_off(LED_R_F);
        //code end
    }
}
