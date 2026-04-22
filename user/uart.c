/*
 * uart.c
 *
 *  Created on: 2026年4月6日
 *      Author: 26461
 */
#include "uart.h"

uint16_t tx_buf[50];
uint16_t rx_buf[50];
uint16_t rx_len = 0;
bool rx_isr_flag = 0;
bool rx_end_flag = 0;

void rx_byte(void) {
    uint16_t data;

    data = SCI_getData(mySci);
    tx_byte(&data, 1);
    if (rx_isr_flag == 0 && data == BEGIN_DATA) rx_isr_flag = 1;

    if (rx_isr_flag) {
        rx_buf[rx_len] = data;
        rx_len++;
    }

    if (rx_isr_flag == 1 && data == END_DATA) {
        rx_isr_flag = 0;
        rx_end_flag = 1;
    }
    if(rx_end_flag) rx_cl();
}

void rx_cl(void){

    rx_clear();
    rx_end_flag = 0;
}

void rx_clear(void){
    uint16_t i = 0;
    for(; i < rx_len; ++i) rx_buf[i] = 0;
    rx_len = 0;
}

void tx_byte(const uint16_t* data, uint16_t len) {
    uint16_t* p = (uint16_t*)&data[0];
	uint16_t i = 0;

    for (; i < len; ++i) {
		SCI_putData(mySci, *(p + i));//发送数据
    }
}

void uart_init(void){
    uint16_t i = 0;
    GPIO_setMode(myGpio, TX_PIN, GPIO_29_Mode_SCITXDA);
    GPIO_setPullUp(myGpio, TX_PIN, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, TX_PIN, GPIO_Direction_Output);

    GPIO_setMode(myGpio, RX_PIN, GPIO_28_Mode_SCIRXDA);
    GPIO_setPullUp(myGpio, RX_PIN, GPIO_PullUp_Enable);
    GPIO_setDirection(myGpio, RX_PIN, GPIO_Direction_Input);
    GPIO_setQualification(myGpio, RX_PIN, GPIO_Qual_ASync);

//    SCI_setBaudRate(mySci, SCI_BaudRate_115_2_kBaud);
    SCI_setBaudRate(mySci, SCI_BaudRate_9_6_kBaud);
	SCI_disableParity(mySci);
	SCI_setNumStopBits(mySci, SCI_NumStopBits_One);
	SCI_setCharLength(mySci, SCI_CharLength_8_Bits);

	SCI_enableTx(mySci);
	SCI_enableRx(mySci);
	// 使能 SCI 接收中断（外设级中断使能），否则不会触发 PIE 中断回调
	SCI_enableRxInt(mySci);

	SCI_enable(mySci);

	for(; i < 50; ++i) rx_buf[i] = 0;

    rx_pie = 1;
}


