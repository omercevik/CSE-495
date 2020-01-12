#include "KeyPad.h"
#include "Ultrasonic.h"
#include "Buzzer.h"

#define						_KEYPAD_DEBOUNCE_TIME_MS				20
#define						_KEYPAD_USE_FREERTOS						1

const GPIO_TypeDef* _KEYPAD_ROW_GPIO_PORT[] =
{
															KEYPAD_C1_GPIO_Port,
															KEYPAD_C2_GPIO_Port,
															KEYPAD_C3_GPIO_Port,
															KEYPAD_C4_GPIO_Port
};
  
const uint16_t _KEYPAD_ROW_GPIO_PIN[] =
{
															KEYPAD_C1_Pin,
															KEYPAD_C2_Pin,
															KEYPAD_C3_Pin,
															KEYPAD_C4_Pin
};

const GPIO_TypeDef* _KEYPAD_COLUMN_GPIO_PORT[] =
{
															KEYPAD_R1_GPIO_Port,
															KEYPAD_R2_GPIO_Port,
															KEYPAD_R3_GPIO_Port,
															KEYPAD_R4_GPIO_Port
};
  
const uint16_t _KEYPAD_COLUMN_GPIO_PIN[] =
{
															KEYPAD_R1_Pin,
															KEYPAD_R2_Pin,
															KEYPAD_R3_Pin,
															KEYPAD_R4_Pin
};

#if (_KEYPAD_USE_FREERTOS==1)
#define	_KEYPAD_DELAY(x)			osDelay(x)
#else
#define	_KEYPAD_DELAY(x)			HAL_Delay(x)
#endif

KeyPad_t	KeyPad;

//#############################################################################################
void	KeyPad_Init(void)
{
	GPIO_InitTypeDef	gpio;
	KeyPad.ColumnSize = sizeof(_KEYPAD_COLUMN_GPIO_PIN)/2;
	KeyPad.RowSize = sizeof(_KEYPAD_ROW_GPIO_PIN)/2;
	for(uint8_t	i=0 ; i<KeyPad.ColumnSize ; i++)
	{
		gpio.Mode = GPIO_MODE_OUTPUT_PP;
		gpio.Pull = GPIO_NOPULL;
		gpio.Speed = GPIO_SPEED_FREQ_LOW;
		gpio.Pin = _KEYPAD_COLUMN_GPIO_PIN[i];
		HAL_GPIO_Init((GPIO_TypeDef*)_KEYPAD_COLUMN_GPIO_PORT[i],&gpio);
		HAL_GPIO_WritePin((GPIO_TypeDef*)_KEYPAD_COLUMN_GPIO_PORT[i],_KEYPAD_COLUMN_GPIO_PIN[i],GPIO_PIN_SET);
	}
	for(uint8_t	i=0 ; i<KeyPad.RowSize ; i++)
	{
		gpio.Mode = GPIO_MODE_INPUT;
		gpio.Pull = GPIO_PULLUP;
		gpio.Speed = GPIO_SPEED_FREQ_LOW;
		gpio.Pin = _KEYPAD_ROW_GPIO_PIN[i];
		HAL_GPIO_Init((GPIO_TypeDef*)_KEYPAD_ROW_GPIO_PORT[i],&gpio);		
	}
}
//#############################################################################################
uint16_t	KeyPad_Scan(void)
{
	uint16_t key=0;
	for(uint8_t c=0 ; c<KeyPad.ColumnSize ; c++)
	{
		for(uint8_t	i=0 ; i<KeyPad.ColumnSize ; i++)
			HAL_GPIO_WritePin((GPIO_TypeDef*)_KEYPAD_COLUMN_GPIO_PORT[i],_KEYPAD_COLUMN_GPIO_PIN[i],GPIO_PIN_SET);
		HAL_GPIO_WritePin((GPIO_TypeDef*)_KEYPAD_COLUMN_GPIO_PORT[c],_KEYPAD_COLUMN_GPIO_PIN[c],GPIO_PIN_RESET);
		HAL_Delay(5);
		for(uint8_t r=0 ; r<KeyPad.RowSize ; r++)
		{
			if(HAL_GPIO_ReadPin((GPIO_TypeDef*)_KEYPAD_ROW_GPIO_PORT[r],_KEYPAD_ROW_GPIO_PIN[r])==GPIO_PIN_RESET)
			{
				HAL_Delay(_KEYPAD_DEBOUNCE_TIME_MS);
				if(HAL_GPIO_ReadPin((GPIO_TypeDef*)_KEYPAD_ROW_GPIO_PORT[r],_KEYPAD_ROW_GPIO_PIN[r])==GPIO_PIN_RESET)
				{
					key |= 1<<c;					
					key |= 1<<(r+8);
					while(HAL_GPIO_ReadPin((GPIO_TypeDef*)_KEYPAD_ROW_GPIO_PORT[r],_KEYPAD_ROW_GPIO_PIN[r])==GPIO_PIN_RESET)
						HAL_Delay(5);
					return key;
				}
			}			
		}		
	}
	return key;
}
//#############################################################################################
uint16_t	KeyPad_WaitForKey(uint32_t	Timeout_ms)
{	
	uint16_t 	keyRead;
	while(Timeout_ms==0)
	{
		keyRead = KeyPad_Scan();
		ultraSonicModule();
			buzzerModule();
		if(keyRead!=0)
		{
			KeyPad.LastKey = keyRead;
			return keyRead;	
		}
		HAL_Delay(_KEYPAD_DEBOUNCE_TIME_MS);	
	}
	uint32_t	StartTime = HAL_GetTick();
	while(HAL_GetTick()-StartTime < Timeout_ms)
	{
		keyRead = KeyPad_Scan();
		ultraSonicModule();
			buzzerModule();
		if(keyRead!=0)
		{
			KeyPad.LastKey = keyRead;
			return keyRead;	
		}
		HAL_Delay(_KEYPAD_DEBOUNCE_TIME_MS);	
	}
	KeyPad.LastKey=0;
	return 0;
}
//#############################################################################################
char	KeyPad_WaitForKeyGetChar(uint32_t	Timeout_ms)
{
	ultraSonicModule();
	buzzerModule();
	switch(KeyPad_WaitForKey(Timeout_ms))
	{
		case 0x0000:
			return 0;
		case 0x0101:
			return '1';
		case 0x0201:
			return '2';
		case 0x0401:
			return '3';
		case 0x0102:
			return '4';
		case 0x0202:
			return '5';
		case 0x0402:
			return '6';
		case 0x0104:
			return '7';
		case 0x0204:
			return '8';		
		case 0x0404:
			return '9';		
		case 0x0208:
			return '0';
		
		default:
			return 0;		
	}
}
