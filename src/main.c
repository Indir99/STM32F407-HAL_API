#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"
#include "adc.h"
#include "DCmotor.h"
#include "valve.h"
#include "lcd.h"

#define LCD_D6_Pin GPIO_PIN_2
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D7_Pin GPIO_PIN_3
#define LCD_D7_GPIO_Port GPIOE
#define LCD_RS_Pin GPIO_PIN_4
#define LCD_RS_GPIO_Port GPIOE
#define LCD_RW_Pin GPIO_PIN_5
#define LCD_RW_GPIO_Port GPIOE
#define LCD_E_Pin GPIO_PIN_6
#define LCD_E_GPIO_Port GPIOE
#define LCD_D4_Pin GPIO_PIN_0
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_1
#define LCD_D5_GPIO_Port GPIOE

volatile uint32_t adc_value1;
volatile uint32_t adc_value2;
volatile uint32_t adc_value3;
//volatile uint32_t adc_value4;
uint8_t flag1 = 0;
uint8_t flag2 = 0;
uint8_t flag3 = 0;
//uint8_t flag4 = 0;
uint8_t null_flag = 0;
void water_lvl1();
void water_lvl2();
void water_lvl3();
//void water_lvl4();

PortPin_Map LCD_RS = {.GPIOx = LCD_RS_GPIO_Port, .GPIO_Pin_x = LCD_RS_Pin};
PortPin_Map LCD_RW = {.GPIOx = LCD_RW_GPIO_Port, .GPIO_Pin_x = LCD_RW_Pin};
PortPin_Map LCD_E = {.GPIOx = LCD_E_GPIO_Port, .GPIO_Pin_x = LCD_E_Pin};
PortPin_Map LCD_D4 = {.GPIOx = LCD_D4_GPIO_Port, .GPIO_Pin_x = LCD_D4_Pin};
PortPin_Map LCD_D5 = {.GPIOx = LCD_D5_GPIO_Port, .GPIO_Pin_x = LCD_D5_Pin};
PortPin_Map LCD_D6 = {.GPIOx = LCD_D6_GPIO_Port, .GPIO_Pin_x = LCD_D6_Pin};
PortPin_Map LCD_D7 = {.GPIOx = LCD_D7_GPIO_Port, .GPIO_Pin_x = LCD_D7_Pin};

static void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

	HAL_GPIO_WritePin(GPIOE, LCD_D6_Pin | LCD_D7_Pin | LCD_RS_Pin | LCD_RW_Pin | LCD_E_Pin | LCD_D4_Pin | LCD_D5_Pin, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = LCD_D6_Pin | LCD_D7_Pin | LCD_RS_Pin | LCD_RW_Pin | LCD_E_Pin | LCD_D4_Pin | LCD_D5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

int main(void)
{
	HAL_Init();

	// initalize push button on PA0
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	initValve(GPIO_PIN_6, GPIO_PIN_7); //VENTILI KONFIGURISANI NA GPIOC, tj radi na PC6 i PC7
	LCD_GPIO_Init();

	LCD_TypeDef *lcd = LCD_init(&LCD_RS, &LCD_RW, &LCD_E, &LCD_D4, &LCD_D5, &LCD_D6, &LCD_D7);
	LCD_begin(lcd);

	closeValve(SERVO1);
	closeValve(SERVO2);
	delay_ms(2000);

	// Prvi isis, dok se puni
	LCD_setCursor(lcd, 0, 0);
	LCD_clearScreen(lcd);
	LCD_putstr(lcd, (uint8_t *)"PRAZNO P1");

	while (1)
	{
		openValve(SERVO1);
		if (flag1 == 1 && null_flag == 0)
		{ //flag1 = prvi nivo vode
			closeValve(SERVO1);
			delay_ms(200);
			openValve(SERVO2);
			LCD_setCursor(lcd, 0, 0);
			LCD_clearScreen(lcd);
			LCD_putstr(lcd, (uint8_t *)"PRVI LVL");
		}
		if (flag2 == 1 && null_flag == 0)
		{ //flag2 = drugi nivo vode
			closeValve(SERVO2);
			LCD_setCursor(lcd, 0, 0);
			LCD_clearScreen(lcd);
			LCD_putstr(lcd, (uint8_t *)"SPREMNO ZA MIJESANJE");
			delay_ms(500);
		}
		if (flag1 == 1 && flag2 == 1)
		{

			int UserPressed = 0;
			LCD_clearScreen(lcd);
			LCD_setCursor(lcd, 0, 0);
			delay_ms(1000);
			LCD_putstr(lcd, (uint8_t *)"DRZI TIPKU");
			null_flag = 1;
			while (1)
			{

				//Check if user is pressed button, then flag that it's pressed
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0 == 1))
				{
					UserPressed = 1;
				}
				else
				{
					UserPressed = 0;
				}

				//Check if user has pressed button, if its pressed then run motor
				if (UserPressed)
				{
					run_DCmotor(100, GPIO_PIN_12);
				}
				else
				{
					run_DCmotor(0, GPIO_PIN_12);
				}

				delay_ms(200);
			}

			
		}
		//	  printUSART2("-> ADC: Value 1: [%d] \n",adc_value1);
		//	  printUSART2("-> ADC: Value 2: [%d] \n",adc_value2);
		//	  printUSART2("-> ADC: Value 3: [%d] \n",adc_value3);
		water_lvl1();
		water_lvl2();
		//	  delay_ms(500);
	}
}

void water_lvl1()
{
	initADC1_4();
	adc_value1 = getADC(GPIO_PIN_4);
	if (adc_value1 > 200)
	{
		flag1 = 1;
	}
	else
	{
		flag1 = 0;
	}
}

void water_lvl2()
{
	initADC1_5();
	adc_value2 = getADC(GPIO_PIN_5);
	if (adc_value2 > 200)
	{
		flag2 = 1;
	}
	else
	{
		flag2 = 0;
	}
}

void water_lvl3()
{
	initADC1_0();
	adc_value3 = getADC(GPIO_PIN_0);
	if (adc_value3 < 3800)
	{
		flag3 = 1;
	}
	else
	{
		flag3 = 0;
	}
}
