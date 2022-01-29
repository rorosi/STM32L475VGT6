/*
 * example.c
 *
 *  Created on: Jan 20, 2022
 *      Author: TAE
 */


#include <stdio.h>
#include <string.h>

#include "main.h"
#include "example.h"
#include "stm32l475e_iot01.h"
#include "stm32l475e_iot01_tsensor.h"
#include "stm32l475e_iot01_hsensor.h"
#include "wifi.h"
#include "es_wifi_io.h"

extern UART_HandleTypeDef huart1;

uint8_t MAC_Addr[6];
uint8_t IP_Addr[4];

ES_WIFIObject_t EsWifiObj;

void User_LED(uint32_t interval)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
	HAL_Delay(interval);
}

int __io_putchar(int ch)
{
	while (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 30000))
	{

	}
	return ch;
}

int __io_getchar(void)
{
	uint8_t ch = 0;
	while (HAL_OK != HAL_UART_Receive(&huart1, (uint8_t *) &ch, 1, 30000))
	{

	}
	return ch;
}

float Temperature_Test(void)
{
	float temp_value = 0;

	BSP_TSENSOR_Init();
	temp_value = BSP_TSENSOR_ReadTemp();

	return temp_value;
}

float Humidity_Test(void)
{
	float humidity_value = 0;

	BSP_HSENSOR_Init();
	humidity_value = BSP_HSENSOR_ReadHumidity();

	return humidity_value;
}
