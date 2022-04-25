#include "valve.h"


TIM_HandleTypeDef TIM3_HandleStruct;
uint8_t userPinServo1;
uint8_t userPinServo2;

void initValve(uint8_t userPin1, uint8_t userPin2)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pins
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructServo1;
	GPIO_InitStructServo1.Pin = userPin1;
	GPIO_InitStructServo1.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructServo1.Pull = GPIO_NOPULL;
	GPIO_InitStructServo1.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructServo1.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructServo1);

	GPIO_InitTypeDef GPIO_InitStructServo2;
	GPIO_InitStructServo2.Pin = userPin2;
	GPIO_InitStructServo2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructServo2.Pull = GPIO_NOPULL;
	GPIO_InitStructServo2.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructServo2.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructServo2);
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer
	//-------------------------------------------------------------------------------
	__HAL_RCC_TIM3_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 84 - 1;
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 20000;
	TIM_Base_InitStruct.ClockDivision =	TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	TIM3_HandleStruct.Instance = TIM3;
	TIM3_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_PWM_Init(&TIM3_HandleStruct);

	TIM_OC_InitTypeDef TIM_OC_InitStruct;
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.Pulse = 0;
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	
	HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM3_HandleStruct,TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TIM3_HandleStruct,TIM_CHANNEL_2);


}


void openValve(uint32_t motor) {
	if(motor == SERVO1) {
		__HAL_TIM_SET_COMPARE(&TIM3_HandleStruct,TIM_CHANNEL_1,1500);
	} else if (motor == SERVO2) {
		__HAL_TIM_SET_COMPARE(&TIM3_HandleStruct,TIM_CHANNEL_2,1500);
	}
}

void closeValve(uint32_t motor) {
	if(motor == SERVO1) {
		__HAL_TIM_SET_COMPARE(&TIM3_HandleStruct,TIM_CHANNEL_1,2400);
	} else if (motor == SERVO2) {
		__HAL_TIM_SET_COMPARE(&TIM3_HandleStruct,TIM_CHANNEL_2,2400);
	}
}