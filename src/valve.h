#ifndef __VALVE_H 
#define __VALVE_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

static enum Motors{SERVO1 = 1,SERVO2 = 2};
void initValve(uint8_t userPin1, uint8_t userPin2);
void openValve(uint32_t motor);
void closeValve(uint32_t motor);


#endif /* ifndef  */
