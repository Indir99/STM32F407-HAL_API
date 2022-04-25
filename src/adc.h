#ifndef __ADC_H
#define __ADC_H 
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void initADC1_5(void);
void initADC1_4(void);
void initADC1_0(void);
void initADC1_1(void);
uint16_t getADC(uint32_t);

#endif 
