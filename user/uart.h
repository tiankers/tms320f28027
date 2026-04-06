/*
 * uart.h
 *
 *  Created on: 2026Äê4ÔÂ6ÈÕ
 *      Author: 26461
 */

#ifndef USER_UART_H_
#define USER_UART_H_

#include "Tianker.h"

#define RX_PIN				(GPIO_Number_28)
#define TX_PIN				(GPIO_Number_29)

#define BEGIN_DATA			(0xFE)
#define END_DATA			(0xFF)

extern uint16_t tx_buf[50];
extern uint16_t rx_buf[50];
extern uint16_t rx_len;
extern bool rx_isr_flag;
extern bool rx_end_flag;

void uart_init(void);
void tx_byte(const uint16_t* data, uint16_t len);
void rx_byte(void);
void rx_clear(void);
void rx_cl(void);

#endif /* USER_UART_H_ */
