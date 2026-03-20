/*
 * adc_hw.h
 *
 *  Created on: 2026Äê3ÔÂ19ÈÕ
 *      Author: 26461
 */

#ifndef USER_ADC_HW_H_
#define USER_ADC_HW_H_

#include "Tianker.h"


#define HW_EN           (GPIO_Number_34)

void hw_init(void);
uint16_t adc_hw_read_sensor(uint16_t index);
void adc_hw_update_values(void);
void adc_hw_start_all_by_sw(void);


#endif /* USER_ADC_HW_H_ */
