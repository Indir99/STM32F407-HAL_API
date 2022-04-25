#include "DCmotor.h"

TIM_HandleTypeDef TIM4_HandleStruct;
uint32_t userPin; //Proizvoljan broj koji zapravo predstavlja pin
void Custom_initPWM(uint32_t CustomPin)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pin
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = userPin; // Definisanje PIN-a preko proizvoljnog broja kojeg user bira
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer
	//-------------------------------------------------------------------------------
	__HAL_RCC_TIM4_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 0x0054 - 0x001;
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 0x03E8;
	TIM_Base_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	TIM4_HandleStruct.Instance = TIM4;
	TIM4_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_PWM_Init(&TIM4_HandleStruct);

	TIM_OC_InitTypeDef TIM_OC_InitStruct;
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.Pulse = 500;
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM4_HandleStruct, TIM_CHANNEL_1);
}
void setPWM(uint32_t ccr1)
{
	__HAL_TIM_SET_COMPARE(&TIM4_HandleStruct, TIM_CHANNEL_1, ccr1);
}

void run_DCmotor(uint32_t speed, uint32_t MotorPin)
{
	//Set pin which user defined for motor
	userPin = MotorPin;

	//Now initialize pwm with custom pin which user defined
	Custom_initPWM(userPin);

	//We will write mapping function for value speed 850-999-> 0-100

	//Map value (mapping function)
	speed = 300 / 100 * speed + 700;

	//Check if entered value is beyond min|max value and in that case set speed to min|max
	if (speed >= 999)
	{
		speed = 999;
	}
	else if (speed <= 700)
	{
		speed = 0;
	}

	setPWM(speed);
}
