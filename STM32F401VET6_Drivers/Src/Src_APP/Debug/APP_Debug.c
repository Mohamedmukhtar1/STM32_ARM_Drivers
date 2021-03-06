/*
 * APP_Debug.c
 *
 *  Created on: May 19, 2022
 *      Author: Eng- Mohamed Mokhtar
 */

#include "APP_Debug.h"

void ADebug_vAll_GPIO_Ports (void)
{
	u8 i =0;
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOA);
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOB);
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOC);
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOD);
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOE);
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOH);

	MGPIO_vFastPortConfigMode(GPIOA_PORT, OUTPUT_PORT_MODE);
	MGPIO_vFastPortConfigMode(GPIOB_PORT, OUTPUT_PORT_MODE);
	MGPIO_vFastPortConfigMode(GPIOC_PORT, OUTPUT_PORT_MODE);
	MGPIO_vFastPortConfigMode(GPIOD_PORT, OUTPUT_PORT_MODE);
	MGPIO_vFastPortConfigMode(GPIOE_PORT, OUTPUT_PORT_MODE);
	MGPIO_vFastPortConfigMode(GPIOH_PORT, OUTPUT_PORT_MODE);

	for(i=0; i<16 ;i++)
	{
		MGPIO_vSetPinOutputType(GPIOA_PORT, (u8)i, OUTPUT_PUSH_PULL_TYPE);
		MGPIO_vSetPinOutputSpeed(GPIOA_PORT, (u8)i, OUTPUT_LOW_SPEED);

		MGPIO_vSetPinOutputType(GPIOB_PORT ,i ,OUTPUT_PUSH_PULL_TYPE);
		MGPIO_vSetPinOutputSpeed(GPIOB_PORT ,i ,OUTPUT_LOW_SPEED);

		MGPIO_vSetPinOutputType(GPIOC_PORT ,i ,OUTPUT_PUSH_PULL_TYPE);
		MGPIO_vSetPinOutputSpeed(GPIOC_PORT ,i ,OUTPUT_LOW_SPEED);

		MGPIO_vSetPinOutputType(GPIOD_PORT ,i ,OUTPUT_PUSH_PULL_TYPE);
		MGPIO_vSetPinOutputSpeed(GPIOD_PORT ,i ,OUTPUT_LOW_SPEED);

		MGPIO_vSetPinOutputType(GPIOE_PORT ,i ,OUTPUT_PUSH_PULL_TYPE);
		MGPIO_vSetPinOutputSpeed(GPIOE_PORT ,i ,OUTPUT_LOW_SPEED);

		MGPIO_vSetPinOutputType(GPIOH_PORT ,i ,OUTPUT_PUSH_PULL_TYPE);
		MGPIO_vSetPinOutputSpeed(GPIOH_PORT ,i ,OUTPUT_LOW_SPEED);/**/
	}

	for (i=0; i<16 ;i++)
	{
		MGPIO_vWritePinData(GPIOA_PORT, i, HIGH_STATE);
		MGPIO_vWritePinData(GPIOB_PORT, i, HIGH_STATE);
		MGPIO_vWritePinData(GPIOC_PORT, i, HIGH_STATE);
		MGPIO_vWritePinData(GPIOD_PORT, i, HIGH_STATE);
		MGPIO_vWritePinData(GPIOE_PORT, i, HIGH_STATE);
		MGPIO_vWritePinData(GPIOH_PORT, i, HIGH_STATE);
	}
}

void ADebug_vFlashingPins (void)
{
	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOA);
	MGPIO_vSetPinMode(GPIOA_PORT, GPIO_PIN_0, OUTPUT_MODE);
	MGPIO_vSetPinOutputType(GPIOA_PORT, GPIO_PIN_0, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinPullType(GPIOA_PORT, GPIO_PIN_0, PULL_UP_STATE);
	MGPIO_vSetPinOutputSpeed(GPIOA_PORT, GPIO_PIN_0, OUTPUT_LOW_SPEED);
	MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_0, HIGH_STATE);

	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOA);
	MGPIO_vSetPinMode(GPIOA_PORT, GPIO_PIN_2, OUTPUT_MODE);
	MGPIO_vSetPinOutputType(GPIOA_PORT, GPIO_PIN_2, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinPullType(GPIOA_PORT, GPIO_PIN_2, PULL_UP_STATE);
	MGPIO_vSetPinOutputSpeed(GPIOA_PORT, GPIO_PIN_2, OUTPUT_LOW_SPEED);

	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOA);
	MGPIO_vSetPinMode(GPIOA_PORT, GPIO_PIN_4, OUTPUT_MODE);
	MGPIO_vSetPinOutputType(GPIOA_PORT, GPIO_PIN_4, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinPullType(GPIOA_PORT, GPIO_PIN_4, PULL_UP_STATE);
	MGPIO_vSetPinOutputSpeed(GPIOA_PORT, GPIO_PIN_4, OUTPUT_LOW_SPEED);

	MRCC_vEnableBusClock(Bus_AHB1, PHB1_GPIOA);
	MGPIO_vSetPinMode(GPIOA_PORT, GPIO_PIN_6, OUTPUT_MODE);
	MGPIO_vSetPinOutputType(GPIOA_PORT, GPIO_PIN_6, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinPullType(GPIOA_PORT, GPIO_PIN_6, PULL_UP_STATE);
	MGPIO_vSetPinOutputSpeed(GPIOA_PORT, GPIO_PIN_6, OUTPUT_LOW_SPEED);

	while(1)
	{
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_0, HIGH_STATE);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_2, HIGH_STATE);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_4, LOW_STATE);
		Delay_vMilliSecond16MHzoscillator(500);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_0, LOW_STATE);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_2, HIGH_STATE);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_4, HIGH_STATE);
		Delay_vMilliSecond16MHzoscillator(500);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_0, HIGH_STATE);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_2, LOW_STATE);
		MGPIO_vWritePinData(GPIOA_PORT, GPIO_PIN_4, HIGH_STATE);
		Delay_vMilliSecond16MHzoscillator(500);

		MGPIO_vToggle_Pin(GPIOA_PORT, GPIO_PIN_6);
		Delay_vMilliSecond16MHzoscillator(500);
	}
}

void ADebug_vLED_Driver (void)
{
	HLED_vInitLED(LED_0_);
	HLED_vInitLED(LED_1_);
	HLED_vLEDStateControl(LED_0_, LED_ON);
	while(1)
	{
		HLED_vToggelLED(LED_1_);
		Delay_vMilliSecond16MHzoscillator(500);
	}
}

