/**
 * main.c
 */
#include "Tianker.h"

void main(void)
{
    //系统初始化
    config();

    //用户初始化
    adc_init();
    io_init();
    key_init();
    motor_init();
    hw_init();
    csb_init();

    time_pie_us(myTimer0, 1000);
    time_pie_us(myTimer1, 3);
    time_pie_us(myTimer2, 7);
    //中断
    pie_init();
    for(;;){
        //code begin
        trig();
        echo();

        switch (gn_id) {
            case 1:
                half_led();
                break;
            case 2:
                all_led_on();
                break;
            case 3:
				all_led_off();
                break;
			default:
				break;
        }

        //code end
    }
}
