/*
 * uart.h
 *
 *  Created on: 2026Äê4ÔÂ6ÈÕ
 *      Author: 26461
 */

#ifndef USER_UART_H_
#define USER_UART_H_

#include "Tianker.h"

#define RX_PIN  (GPIO_Number_28)
#define TX_PIN  (GPIO_Number_29)

extern uint16_t tx_buf[50];

void uart_init(void);
void tx_byte(const uint16_t* data, uint16_t len);

#endif /* USER_UART_H_ */
