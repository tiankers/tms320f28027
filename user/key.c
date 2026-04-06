/*
 * key.c
 *
 *  Created on: 2026年3月14日
 *      Author: 26461
 */
#include "key.h"

KEY_X KEY_1;
KEY_X KEY_2;
KEY_X KEY_3;
uint16_t gn_id = 0;

void get_key_down(void){
    KEY_1.down = key_down;
    if (adc_val[7] < 3500 && adc_val[7] > 3300)
        KEY_2.down = 1;
    else if (adc_val[7] < 4070 && adc_val[7] > 4000)
        KEY_3.down = 1;
    else{
        KEY_2.down = 0;
        KEY_3.down = 0;
    }
}

void key_even(KEY_X* key_x) {
    switch (key_x->key_even) {
        case ONE_DOWN:
            //处理单击事件
            if(key_x->key_num == 1){
                gn_id = 1;
                half_flag = !half_flag;
            }
            key_x->key_even = DONE;
            break;
        case TWO_DOWN:
            //处理双击事件
            if(key_x->key_num == 1){
                gn_id = 2;
            }
            key_x->key_even = DONE;
            break;
        case LONG_DOWN:
            //
            if(key_x->key_num == 1){
                gn_id = 3;
            }
            key_x->key_even = DONE;
			break;
        case DONE:
            return;
//        default:
//            key_x->key_even = DONE;
//			break;
    }
}

void key_get(KEY_X *key_x){
    if(key_x->down && !key_x->down_flag && XY(ms, key_x->up_ms) > UP_DOWN_TIME){
        key_x->down_flag = 1;
        key_x->down_ms = ms;
    }
    if(!key_x->down && key_x->down_flag && XY(ms, key_x->down_ms) > UP_DOWN_TIME){
		key_x->last_up = key_x->up_ms;//记录上次按键抬起时间
        key_x->down_flag = 0;
        key_x->up_ms = ms;
		key_x->even_flag = 1;
    }
    if(key_x->up_ms > key_x->down_ms && key_x->even_flag){
        if(XY(key_x->up_ms, key_x->down_ms) > LONG_DOWN_TIME){
            key_x->key_even = LONG_DOWN;
        }else if(XY(key_x->up_ms, key_x->down_ms) > SHORT_DOWN_TIME){
            key_x->key_even = SHORT_DOWN;
        }
        key_x->even_flag = 0;
    }
    if (key_x->key_even == SHORT_DOWN) {
		//如果上次按键事件是短按，并且这次按键按下的时间与上次抬起的时间间隔小于TWE_DOWN_TIME，则认为是双击事件
        if (XY(key_x->down_ms, key_x->last_up) < TWE_DOWN_TIME && (key_x->last_even == ONE_DOWN || key_x->last_even == SHORT_DOWN)) {
            key_x->key_even = TWO_DOWN;
        } else if(XY(ms, key_x->up_ms) >= TWE_DOWN_TIME)
        {
            key_x->key_even = ONE_DOWN;
		}
    }
	if(key_x->key_even != DONE) key_x->last_even = key_x->key_even;//记录上次按键事件类型
}

void key_init(void){
    GPIO_setMode(myGpio, key_1, GPIO_12_Mode_GeneralPurpose);
    GPIO_setPullUp(myGpio, key_1, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, key_1, GPIO_Direction_Input);

	//GPIO_setQualification(myGpio, key_1, GPIO_Qual_ASync);//异步输入，立即响应

	GPIO_setQualification(myGpio, key_1, GPIO_Qual_Sample_6);//滤波，采样6次
	GPIO_setQualificationPeriod(myGpio, key_1, 255);//采样周期为255个时钟周期（0.1~0.3ms*6）

	ADC_setSocChanNumber(myAdc, ADC_SocNumber_8, key_2);
	ADC_setSocSampleWindow(myAdc, ADC_SocNumber_8, ADC_SocSampleWindow_7_cycles);
	ADC_setSocTrigSrc(myAdc, ADC_SocNumber_8, ADC_SocTrigSrc_CpuTimer_0);

	//key_pie = 1;//使能按键中断

    KEY_1.key_even = DONE;
    KEY_1.down_flag = 0;
    KEY_1.key_num = 1;
    KEY_2.key_even = DONE;
    KEY_2.down_flag = 0;
    KEY_2.key_num = 2;
    KEY_3.key_even = DONE;
    KEY_3.down_flag = 0;
    KEY_3.key_num = 3;
}
