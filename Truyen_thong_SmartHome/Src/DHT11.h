#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f1xx_hal.h"

/****************** KHAI BAO BIEN ******************/
typedef struct
{
	uint8_t temp_int;  // phan nguyen nhiet do
	uint8_t temp_deci; // phan thap phan nhiet do
	uint8_t humi_int;  // phan nguyen do am
	uint8_t humi_deci; // phan thap phan nhiet do
	uint8_t check_sum; //sum tong
} DHT11_DATA_TypeDef;

/******************* DHT11 define port connect ***********/
#define				GPIO_DHT11_CLK			__HAL_RCC_GPIOA_CLK_ENABLE()
#define				GPIO_DHT11_PORT			GPIOA
#define				GPIO_DHT11_PIN			GPIO_PIN_4

/******************* DHT11 define huong ra vao ****************/
#define				DHT11_DOUT_0		HAL_GPIO_WritePin(GPIO_DHT11_PORT, GPIO_DHT11_PIN, 0)
#define				DHT11_DOUT_1		HAL_GPIO_WritePin(GPIO_DHT11_PORT, GPIO_DHT11_PIN, 1)
#define				DHT11_DATA_IN	HAL_GPIO_ReadPin(GPIO_DHT11_PORT, GPIO_DHT11_PIN)

/*************************** KHAI BAO HAM CON ******************/
void DHT11_Init(void);
void delay_us(uint8_t time);
uint8_t Read_TempAndHumidity (DHT11_DATA_TypeDef *DHT11_DATA);
#endif
