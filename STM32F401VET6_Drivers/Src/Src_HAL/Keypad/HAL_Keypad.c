/*
 * HAL_Keypad.c
 *
 *  Created on: May 30, 2022
 *      Author: Eng- Mohamed Mokhtar
 */

#include "HAL_Keypad_Interface.h"

void HKEYPAD_vInitiate(void)
{
	MRCC_vEnableBusClock(Bus_AHB1, KEYPAD_ROW_BUS);
	MRCC_vEnableBusClock(Bus_AHB1, KEYPAD_COL_BUS);
	/************************************************************************************/
	MGPIO_vSetPinMode(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, OUTPUT_MODE);
	MGPIO_vSetPinMode(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, OUTPUT_MODE);
	MGPIO_vSetPinMode(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, OUTPUT_MODE);
	MGPIO_vSetPinMode(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, OUTPUT_MODE);

	MGPIO_vSetPinOutputType(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinOutputType(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinOutputType(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, OUTPUT_PUSH_PULL_TYPE);
	MGPIO_vSetPinOutputType(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, OUTPUT_PUSH_PULL_TYPE);

	MGPIO_vSetPinOutputSpeed(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, OUTPUT_LOW_SPEED);
	MGPIO_vSetPinOutputSpeed(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, OUTPUT_LOW_SPEED);
	MGPIO_vSetPinOutputSpeed(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, OUTPUT_LOW_SPEED);
	MGPIO_vSetPinOutputSpeed(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, OUTPUT_LOW_SPEED);

	MGPIO_vWritePinData(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, HIGH_STATE);
	MGPIO_vWritePinData(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, HIGH_STATE);
	MGPIO_vWritePinData(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, HIGH_STATE);
	MGPIO_vWritePinData(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, HIGH_STATE);
	/************************************************************************************/
	MGPIO_vSetPinMode(KEYPAD_COL_PORT, KEYPAD_C0_PIN, INPUT_MODE);
	MGPIO_vSetPinMode(KEYPAD_COL_PORT, KEYPAD_C1_PIN, INPUT_MODE);
	MGPIO_vSetPinMode(KEYPAD_COL_PORT, KEYPAD_C2_PIN, INPUT_MODE);
	MGPIO_vSetPinMode(KEYPAD_COL_PORT, KEYPAD_C3_PIN, INPUT_MODE);

	MGPIO_vSetPinPullType(KEYPAD_COL_PORT, KEYPAD_C0_PIN, PULL_UP_STATE);
	MGPIO_vSetPinPullType(KEYPAD_COL_PORT, KEYPAD_C1_PIN, PULL_UP_STATE);
	MGPIO_vSetPinPullType(KEYPAD_COL_PORT, KEYPAD_C2_PIN, PULL_UP_STATE);
	MGPIO_vSetPinPullType(KEYPAD_COL_PORT, KEYPAD_C3_PIN, PULL_UP_STATE);
}

u8 HKEYPAD_u8READ(void)
{
	u8 KeyPad_ARRAY [4][4]= KEYPAD_KEYS_VALUES;
	u8 loc_u8_Row =KEYPAD_R1_PIN;
	u8 loc_u8_Col =KEYPAD_C1_PIN;
	u8 loc_u8_RWCL_DATA_READING = 0;
	u8 loc_u8_Pad_Reading = PAD_RELEASE;

	for (loc_u8_Row = KEYPAD_R0_PIN; loc_u8_Row <= KEYPAD_R3_PIN; loc_u8_Row++)
	{
		MGPIO_vWritePinData(KEYPAD_ROW_PORT, loc_u8_Row, LOW_STATE);
		for (loc_u8_Col = KEYPAD_C0_PIN; loc_u8_Col <= KEYPAD_C3_PIN; loc_u8_Col++)
		{
			loc_u8_Pad_Reading = MGPIO_u8ReadPinData(KEYPAD_COL_PORT, loc_u8_Col);
			if (PAD_PRESSE == loc_u8_Pad_Reading)
			{
				Delay_vMilliSecond16MHzoscillator(50);
				loc_u8_Pad_Reading = MGPIO_u8ReadPinData(KEYPAD_COL_PORT, loc_u8_Col);
				if (PAD_PRESSE == loc_u8_Pad_Reading)
				{
					while (PAD_PRESSE == MGPIO_u8ReadPinData(KEYPAD_COL_PORT, loc_u8_Col));
					loc_u8_RWCL_DATA_READING =  KeyPad_ARRAY[loc_u8_Row -KEYPAD_R0_PIN][loc_u8_Col -KEYPAD_C0_PIN];
					//loc_u8_Pad_Reading = PAD_RELEASE;
					//MGPIO_vWritePinData(PHB1_GPIOA, GPIO_PIN_2, HIGH_STATE);
				}
				else {/*NOTHING*/}
			}
			else {/*NOTHING*/}
		}
		MGPIO_vWritePinData(KEYPAD_ROW_PORT, loc_u8_Row, HIGH_STATE);
		//Delay_vMilliSecond16MHzoscillator(100);
		//MGPIO_vWritePinData(PHB1_GPIOA, GPIO_PIN_2, LOW_STATE);
	}
	return loc_u8_RWCL_DATA_READING;
}
