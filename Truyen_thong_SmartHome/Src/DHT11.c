#include "DHT11.h"

static void GPIO_DHT11_OUT(void);
static void GPIO_DHT11_IN(void);
static uint8_t  READ_DATA_8BIT(void) ;

/******************* DHT11 khoi tao ************************/
void DHT11_Init(void)
{
	GPIO_DHT11_OUT();		// thiet lap che do dau ra 
	DHT11_DOUT_1;				// Khoi tao pin DHT11
	HAL_Delay(1000);		// delay 1s
}


/********************* Config GPIO output ********************/
static void GPIO_DHT11_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_DHT11_CLK;
	GPIO_InitStruct.Pin = GPIO_DHT11_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIO_DHT11_PORT, &GPIO_InitStruct);
}


/*************** Config GPIO Input *****************************/
static void GPIO_DHT11_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_DHT11_CLK;
	GPIO_InitStruct.Pin = GPIO_DHT11_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIO_DHT11_PORT, &GPIO_InitStruct);
}

/**************** Doc 8 bit dau vao DHT11 **********************/
/*
*		Chuan bi gui du lieu logic '0'. 50 uS
*		Doi logic '1' và so sanh thoi gian . neu qua 30uS mà logic = '1' du lieu nhan duoc là bit 1.
*		Neu qua 30 uS mà logic = '0' du lieu là bit 0.
*/
static uint8_t READ_DATA_8BIT(void)
{
	uint8_t i, data = 0;								// data: 1 byte du lieu 8 bit
	
	for ( i = 0; i<8 ; i++)
	{
		while (DHT11_DATA_IN == 0);     // Ðoi cho du lieu nhan vao la 1.
		delay_us(30);											// delay micros 30uS
		if ( DHT11_DATA_IN == 1)				
		{
			while (DHT11_DATA_IN == 1);   
			data |= (uint8_t)( 0x01 << (7-i)); // set bit nhan duoc len 1
		}
		else
			data &= (uint8_t)~(0x01 << (7-i)); // clear bit nhan duoc xuong 0
	}
	
	return data ;
}

/****************************** Doc DHTT11 ************************/
uint8_t	Read_TempAndHumidity (DHT11_DATA_TypeDef *DHT11_DATA)
{
	GPIO_DHT11_OUT();		// Thiet lap che do OUTPUT
	DHT11_DOUT_0;			// Xuat muc logic 0
	HAL_Delay(20);		// Delay 20mS
	DHT11_DOUT_1;			// Xuat muc logic 1. 
	delay_us(30);			// Doi DHT11 response  30uS
	GPIO_DHT11_IN();	// Thiet lap che do Input
	
	if (DHT11_DATA_IN == 0)		// Ktra  pin DHT = 0 ( DHT11 co nhan duoc tin hieu khong), neu khong nhan duoc bao Error
	{
		while (DHT11_DATA_IN == 0); // cho ket thuc tin hieu muc 0
		while (DHT11_DATA_IN == 1); // cho ket thuc tin hieu muc 1
		
		
		DHT11_DATA->humi_int = READ_DATA_8BIT();	// doc data byte 1
		DHT11_DATA->humi_deci = READ_DATA_8BIT(); // doc data byte 2
		DHT11_DATA->temp_int = READ_DATA_8BIT();	// doc data byte 3
		DHT11_DATA->temp_deci = READ_DATA_8BIT();	// doc data byte 4		
		DHT11_DATA->check_sum = READ_DATA_8BIT(); // doc data byte 5
		
		GPIO_DHT11_OUT();			// Ket thuc qua trinh nhan du lieu. thay doi che do dau ra
		DHT11_DOUT_1;				// Dua pin len 1 de tiep tuc chu ky tiep theo
		
		/* Kiem tra check sum dung tra lai SUCCESS, neu sai tra lai ERROR */
		if (DHT11_DATA->check_sum == DHT11_DATA->humi_int + DHT11_DATA->humi_deci 
																+ DHT11_DATA->temp_int + DHT11_DATA->temp_deci)
			return SUCCESS;
		else
			return ERROR;
	}
	else
		return ERROR;
}

/********************* HAM Delay Micro ******************/
/*
*		_nop() delay 1 chu ky may. O day, ta dung clock la 72MHZ. _nop() = 1/ 72MHz (s)
*		72 lan __nop() se tuong ung voi 1 uS.
*/
void delay_us(uint8_t time)
{
	while (time --)
	{
				__nop();
				__nop();		//2
				
					
				
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//10
		
		
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//20
				
				
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//30
				
				
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//40
				
				
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//50
				
				
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//60
				
				
				__nop();		
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();
				__nop();		//70
				
				
	}
}
