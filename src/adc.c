#include "adc.h"

ADC_HandleTypeDef hadc1;



// Source: Data sheet
//******************************************************************************
// GPIO_PIN_5 -> PC5
// GPIO_PIN_4 -> PC4
// GPIO_PIN_0 -> PB0
// GPIO PIN_1 -> PB1
//******************************************************************************
// ADC PC5 -> ADC12_IN15
// ADC PC4 -> ADC12_IN14
// ADC PB0 -> ADC12_IN08
// ADC PB1 -> ADC12_IN09
//-----------------------------------------------------------------------------

//Global:
ADC_ChannelConfTypeDef sConfig = {0};

void initADC1_5(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	 //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 								
	 //RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 									
	 //GPIOA->MODER |= GPIO_MODER_MODER1;  								
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1; 								

	//ADC_ChannelConfTypeDef sConfig = {0};

	__HAL_RCC_ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	
	sConfig.Rank = 1;
	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

void initADC1_4(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	 //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 								
	 //RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 									
	 //GPIOA->MODER |= GPIO_MODER_MODER1;  								
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1; 								
	
	//ADC_ChannelConfTypeDef sConfig = {0};

	__HAL_RCC_ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	
	sConfig.Rank = 1;
	sConfig.Channel = ADC_CHANNEL_14;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

void initADC1_0(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	 //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 								
	 //RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 									
	 //GPIOA->MODER |= GPIO_MODER_MODER1;  								
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1; 									

	//ADC_ChannelConfTypeDef sConfig = {0};

	__HAL_RCC_ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	
	sConfig.Rank = 1;
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

void initADC1_1(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	 //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 								
	 //RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 									
	 //GPIOA->MODER |= GPIO_MODER_MODER1;  								
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1; 								
	
	//ADC_ChannelConfTypeDef sConfig = {0};

	__HAL_RCC_ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	
	sConfig.Rank = 1;
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}



uint16_t getADC(uint32_t pin)
{
	HAL_ADC_Start (&hadc1);
	if(pin==GPIO_PIN_5){
		sConfig.Channel = ADC_CHANNEL_15;
	}
	else if(pin==GPIO_PIN_4){
	    sConfig.Channel = ADC_CHANNEL_14;
	}
	else if(pin==GPIO_PIN_0){
		sConfig.Channel = ADC_CHANNEL_8;
	}
	else if(pin==GPIO_PIN_1){
		sConfig.Channel = ADC_CHANNEL_9;
	}
	while(HAL_ADC_PollForConversion(&hadc1,10000) != HAL_OK);
	// HAL_ADC_PollForConversion(&hadc1,10000);

	return HAL_ADC_GetValue(&hadc1);
}
