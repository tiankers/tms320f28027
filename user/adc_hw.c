/*
 * adc_hw.c
 *
 *  Created on: 2026年3月19日
 *      Author: 26461
 */

#include "adc_hw.h"

/* 7 路传感器的 ADC 通道映射（按项目驱动头文件调整这些常量） */
static const ADC_SocChanNumber_e sensor_adc_channel[7] = {
    ADC_SocChanNumber_A7,  /* sensor 0 -> A7 */
    ADC_SocChanNumber_B1,  /* sensor 1 -> B1 */
    ADC_SocChanNumber_B2,  /* sensor 2 -> B2 */
    ADC_SocChanNumber_B3,  /* sensor 3 -> B3 */
    ADC_SocChanNumber_B4,  /* sensor 4 -> B4 */
    ADC_SocChanNumber_B6,  /* sensor 5 -> B6 */
    ADC_SocChanNumber_B7   /* sensor 6 -> B7 */
};

/* 每一路 SOC 使用的编号：0..6 */
static const uint16_t sensor_soc_index[7] = {
    0, 1, 2, 3, 4, 5, 6
};

/* 采样窗口长度（根据平台调整） */
#define ADC_SAMPLE_WINDOW  ADC_SocSampleWindow_7_cycles   /* 示例值 */

/* 结果缓存（7 路） */
volatile uint16_t ir_values[7] = {0};

/* 初始化 ADC 并配置 7 路 SOC */
static void adc_hw_init(void)
{
    int i;

    /* 1) ADC handle should be initialized elsewhere (config). Use global myAdc. */

    /* 2) 根据映射设置每一路 SOC */
    for (i = 0; i < 7; ++i)
    {
        ADC_SocNumber_e soc = (ADC_SocNumber_e)sensor_soc_index[i];
        ADC_SocChanNumber_e ch  = (ADC_SocChanNumber_e)sensor_adc_channel[i];

        /* 设置 SOC：指定 SOC 编号、通道、采样窗口、触发源
         * 使用组件驱动 API
         */
        ADC_setSocChanNumber(myAdc, soc, ch);
        ADC_setSocSampleWindow(myAdc, soc, ADC_SocSampleWindow_7_cycles);
        /* Use software trigger for simplicity; trigger in adc_hw_start_all_by_sw() */
        ADC_setSocTrigSrc(myAdc, soc, ADC_SocTrigSrc_Sw);
    }

    /* 3) 清除中断标志（若需要） - 使用 ADC_clearIntFlag/ADC_readResult as needed */
    /* No global helper available in this component API; leave interrupt setup to caller */

    /* 4) 如果需要，将对应引脚设置为模拟模式（GPIO -> ADC 引脚） */
    /* 下面示例假定驱动中有 GPIO_setAnalogMode 接口并有引脚常量 */
#ifdef GPIO_setAnalogMode
    GPIO_setAnalogMode(PIN_ADCINA7, true);
    GPIO_setAnalogMode(PIN_ADCINB1, true);
    GPIO_setAnalogMode(PIN_ADCINB2, true);
    GPIO_setAnalogMode(PIN_ADCINB3, true);
    GPIO_setAnalogMode(PIN_ADCINB4, true);
    GPIO_setAnalogMode(PIN_ADCINB6, true);
    GPIO_setAnalogMode(PIN_ADCINB7, true);
#endif

    /* 5) 最后清空缓存 */
    for (i = 0; i < 7; ++i) ir_values[i] = 0;
}

/* 在 hw_init 中调用，初始化 GPIO 并启动 ADC 配置 */
void hw_init(void) {
    GPIO_setMode(myGpio, HW_EN, GPIO_0_Mode_GeneralPurpose);
    GPIO_setPullUp(myGpio, HW_EN, GPIO_PullUp_Disable);
    GPIO_setDirection(myGpio, HW_EN, GPIO_Direction_Output);
    //使能红外传感器
    GPIO_setLow(myGpio, HW_EN);

    // 初始化 ADC 相关并配置 7 路 SOC
    adc_hw_init();
}

/* 软件触发：触发所有 SOC 的采样（如果硬件触发不可用或需要软件触发） */
void adc_hw_start_all_by_sw(void)
{
    int i;
    ADC_Obj *adc = (ADC_Obj *)myAdc;

    /* Force SOC conversions by writing to ADCSOCFRC1 register bits */
    for (i = 0; i < 7; ++i) {
        uint16_t soc = sensor_soc_index[i];
        adc->ADCSOCFRC1 = (uint16_t)(1u << soc);
    }
}

/* 读取所有 SOC 的结果并存入 ir_values[]（调用前确保转换完成） */
void adc_hw_update_values(void)
{
    int i;
    for (i = 0; i < 7; ++i)
    {
        ADC_SocNumber_e soc = (ADC_SocNumber_e)sensor_soc_index[i];
        ADC_Obj *adc = (ADC_Obj *)myAdc;
        /* 等待该 SOC 的转换完成（轮询 ADCSOCFLG1 的相应位） */
        while ((adc->ADCSOCFLG1 & (1u << soc)) == 0) { /* 空等待或添加超时 */ }

        /* 读取结果存入缓存 */
        ir_values[i] = (uint16_t)ADC_readResult(myAdc, (ADC_ResultNumber_e)sensor_soc_index[i]);
        /* 清除该 SOC 标志 */
        adc->ADCSOCFLG1 = (uint16_t)(1u << soc);
    }
}

/* 单路读取接口（返回指定传感器的数值） */
uint16_t adc_hw_read_sensor(uint16_t index)
{
    if (index >= 7) return 0;
    return ir_values[index];
}
