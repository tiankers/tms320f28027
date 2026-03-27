/*
 * key.h
 *
 *  Created on: 2026年3月14日
 *      Author: 26461
 */

#ifndef USER_KEY_H_
#define USER_KEY_H_

#include "Tianker.h"

#define key_1               GPIO_Number_12
#define key_2               ADC_SocChanNumber_A0        //预留按键2，连接到ADC输入引脚上，读取ADC值来判断按键状态

#define key_down            !(GPIO_getData(myGpio, key_1))     //读取按键状态(按键按下时为低电平)

#define UP_DOWN_TIME        (50)
#define SHORT_DOWN_TIME     (50)
#define TWE_DOWN_TIME       (200)
#define LONG_DOWN_TIME      (1000)

extern uint16_t gn_id;

typedef enum
{
    DONE    =   0,
    ONE_DOWN,
    TWO_DOWN,
    LONG_DOWN,
    SHORT_DOWN
} KEY_EVEN;

typedef struct _KEY_X_
{
    uint16_t key_num;
    bool down_flag;
	bool even_flag;
    KEY_EVEN key_even;
    KEY_EVEN last_even;
    uint32_t down_ms;
    uint32_t up_ms;
    uint32_t last_up;
} KEY_X;

extern KEY_X KEY_1;

void key_init(void);
void key_get(KEY_X *key_x);
void key_even(KEY_X *key_x);

#endif /* USER_KEY_H_ */
