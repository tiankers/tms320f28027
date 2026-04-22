/**
 * main.c
 */
#include "Tianker.h"

//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void main(void)
{
    //系统初始化
    config();

    //用户初始化
    adc_init();
    io_init(1);
    key_init();
    motor_init();
    hw_init();
    csb_init();
    uart_init();
    jdy_init();

    time_pie_us(myTimer0, 1000);
    time_pie_us(myTimer1, 10);
    time_pie_us(myTimer2, 10000);

    //中断
    pie_init();
    for(;;){
        //code begin
        trig();
        echo();

//		tx_buf[0] = gn_id;
//		tx_byte(tx_buf, 1);

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
