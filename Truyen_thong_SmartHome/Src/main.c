/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DHT11.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define sizeofRx 3
#define sizeTx 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void servo_write(int);
void servo_sweep(void);
int map(int, int, int, int, int);
int i, len;
int delayTime = 10;
uint8_t flagRx = 0;
uint16_t lenght =0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t rxData[sizeofRx] ={0};
uint8_t SendBuffer[7];
char data[30];
DHT11_DATA_TypeDef DHT11_DATA;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if ( huart->Instance == huart2.Instance)
	{
		HAL_UART_Receive_DMA(&huart2,(uint8_t*)rxData,sizeofRx);
		flagRx = 1;
	}	
}

uint8_t Cong,CuaNha,DenKhach,CuaKhach,DenBep,CuaBep,DenNgu1,CuaNgu1;
uint8_t GianPhoi,QuatAn,DenNgu2,CuaNgu2,DenNgu3,CuaNgu3,DenVs1,DenVs2,DenTam;
void ReadData (void)
{
	Cong = rxData[0] & (1<<7);
	CuaNha = rxData[0] & (1<<6);
	DenKhach = rxData[0] & (1<<5);
	CuaKhach = rxData[0] & (1<<4);
	DenBep = rxData[0] & (1<<3);
	CuaBep = rxData[0] & (1<<2);
	DenNgu1 = rxData[0] & (1<<1);
	CuaNgu1 = rxData[0] & (1<<0);
	
	DenVs2 = rxData[1] & (1<<7);
	DenVs1 = rxData[1] & (1<<6);
	CuaNgu3 = rxData[1] & (1<<5);
	DenNgu3 = rxData[1] & (1<<4);
	CuaNgu2 = rxData[1] & (1<<3);
	DenNgu2 = rxData[1] & (1<<2);
	QuatAn = rxData[1] & (1<<1);
	GianPhoi = rxData[1] & (1<<0);
	
	DenTam = rxData[2] & (1<<0);	
}

void Control(void)
{
	if (Cong){
		// Chuong trình thuc hien open gate
		SendBuffer[0] = SendBuffer[0] | (1<<7);
	} else {
		// Chuong trinh thuc hien close gate
		SendBuffer[0] = SendBuffer[0] & ~(1<<7);
	}
	if (CuaNha){
		// Chuong trinh thuc hien mo cua nha
		SendBuffer[0] = SendBuffer[0] | (1<<6);
	} else {
		// Chuong trinh thuc hien dong cua nha
		SendBuffer[0] = SendBuffer[0] & ~(1<<6);
	}
	if (DenKhach){
		// Chuong trinh thuc hien bat den phong khach
		SendBuffer[0] = SendBuffer[0] | (1<<5);
	} else {
		// Chuong trinh thuc hien tat den phong khach
		SendBuffer[0] = SendBuffer[0] & ~(1<<5);
	}
	if (CuaKhach){
		// Chuong trinh thuc hien mo cua so phong khach
		SendBuffer[0] = SendBuffer[0] | (1<<4);
		servo_write(180);
	} else {
		// Chuong trinh thuc hien dong cua so phong khach
		SendBuffer[0] = SendBuffer[0] & ~(1<<4);
		servo_write(0);
	}
	if (DenBep){
		// Chuong trinh thuc hien bat den bep
		SendBuffer[0] = SendBuffer[0] | (1<<3);
	} else {
		// Chuong trinh thuc hien tat den bep
		SendBuffer[0] = SendBuffer[0] & ~(1<<3);
	}
	if (CuaBep){
		// Chuong trinh thuc hien mo cua bep
		SendBuffer[0] = SendBuffer[0] | (1<<2);
	} else {
		// Chuong trinh thuc hien dong cua bep
		SendBuffer[0] = SendBuffer[0] & ~(1<<2);
	}
	if (DenNgu1){
		// Chuong trinh thuc hien bat den ngu 1
		SendBuffer[0] = SendBuffer[0] | (1<<1);
	} else {
		// Chuong trinh thuc hien tat den ngu 1
		SendBuffer[0] = SendBuffer[0] & ~(1<<1);
	}
	if (CuaNgu1){
		// Chuong trinh thuc hien mo cua phong ngu 1
		SendBuffer[0] = SendBuffer[0] | (1<<0);
	} else {
		// Chuong trinh thuc hien dong cua phong ngu 1
		SendBuffer[0] = SendBuffer[0] & ~(1<<0);
	}
	if(DenVs2){
		// Chuong trinh thuc hien mo den ve sinh 2
		SendBuffer[1] = SendBuffer[1] | (1<<7);
	} else{
		// Chuong trinh tat den ve sinh 2
		SendBuffer[1] = SendBuffer[1] & ~(1<<7);
	}
	if(DenVs1){
		// Chuong trinh thuc hien mo den ve sinh 1
		SendBuffer[1] = SendBuffer[1] | (1<<6);
	} else{
		// Chuong trinh tat den ve sinh 1
		SendBuffer[1] = SendBuffer[1] & ~(1<<6);
	}
	if (DenNgu3){
		// Chuong trinh thuc hien bat den ngu 3
		SendBuffer[1] = SendBuffer[1] | (1<<4);
	} else {
		// Chuong trinh thuc hien tat den ngu 3
		SendBuffer[1] = SendBuffer[1] & ~(1<<4);
	}
	if (CuaNgu3){
		// Chuong trinh thuc hien mo cua phong ngu 3
		SendBuffer[1] = SendBuffer[1] | (1<<5);
	} else {
		// Chuong trinh thuc hien dong cua phong ngu 3
		SendBuffer[1] = SendBuffer[1] & ~(1<<5);
	}
	if (DenNgu2){
		// Chuong trinh thuc hien bat den ngu 2
		SendBuffer[1] = SendBuffer[1] | (1<<2);
	} else {
		// Chuong trinh thuc hien tat den ngu 2
		SendBuffer[1] = SendBuffer[1] & ~(1<<2);
	}
	if (CuaNgu2){
		// Chuong trinh thuc hien mo cua phong ngu 2
		SendBuffer[1] = SendBuffer[1] | (1<<3);
	} else {
		// Chuong trinh thuc hien dong cua phong ngu 2
		SendBuffer[1] = SendBuffer[1] & ~(1<<3);
	}
	if (QuatAn){
		// CHuong trinh thuc hien bat quat phong an
		SendBuffer[1] = SendBuffer[1] | (1<<1);
	} else{
		SendBuffer[1] = SendBuffer[1] & ~(1<<1);
	}
	if (GianPhoi){
		// chuong trinh thuc hien gian phoi
		SendBuffer[1] = SendBuffer[1] | (1<<0);
	} else {
		SendBuffer[1] = SendBuffer[1] & ~(1<<0);
	}
	 if (DenTam){
		 // Chuong trinh thuc hien den phong tam
		 SendBuffer[2] = SendBuffer[2] | (1<<0);
	 } else {
		 SendBuffer[2] = SendBuffer[2] & ~(1<<0);
	 }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim3.Instance)
	{
		if (Read_TempAndHumidity (&DHT11_DATA) == SUCCESS)
		{
		  SendBuffer[3] = DHT11_DATA.temp_int;
			SendBuffer[4] = DHT11_DATA.temp_deci;
			SendBuffer[5] = DHT11_DATA.humi_int;
			SendBuffer[6] = DHT11_DATA.humi_deci;
			
			len = sprintf((char*)data,"A,%i,%i,%i,%i,%i,%i,%i,",SendBuffer[0],SendBuffer[1],SendBuffer[2],SendBuffer[3],SendBuffer[4],SendBuffer[5],SendBuffer[6]);
			//sprintf((char*)data,"A,%i,%i,%i,%i,%i,%i,%i,",128,128,1,SendBuffer[3],SendBuffer[4],SendBuffer[5],SendBuffer[6]);
			HAL_UART_Transmit_DMA(&huart2,(uint8_t*)data,len);
	
		}
		
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	
  /* USER CODE BEGIN 1 */
	
	
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
	DHT11_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_UART_Receive_DMA(&huart2,(uint8_t*)rxData,sizeofRx);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if ( flagRx ){
			ReadData();
			Control();
			flagRx =0;
		}
    /* USER CODE END WHILE */
		
		
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 720-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7200-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 5000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void servo_write(int angle)
{
	htim2.Instance->CCR1 = map(0,180,50,250,angle);
}

void servo_sweep(void)
{
		for(int i = 0; i <= 180; i++)
		{
			servo_write(i);
			HAL_Delay(10);
		}
		for(int i = 180; i >= 0; i--)
		{
			servo_write(i);
			HAL_Delay(10);
		}
}
int map(int st1, int fn1, int st2, int fn2, int value)
{
    return (1.0*(value-st1))/((fn1-st1)*1.0) * (fn2-st2)+st2;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
