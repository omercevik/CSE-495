#include "main.h"
#include "Ultrasonic.h"
#include "Motors.h"

// Speed of sound in cm/us
const float speedOfSound = 0.0343/2;
float distance = 0;

void ultraSonicModule()
{
		uint32_t numTicks;
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
		usDelay(3);
		
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
		usDelay(10);
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
		
		while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET);
		
		numTicks = 0;
		while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET)
		{
			++numTicks;
			usDelay(2); //2.8usec
		};
		
		distance = (numTicks + 0.0f)*2.8f*speedOfSound;
		
		if(distance < 20)
		{
			// Stop Motors. Turn the motor. Start motors.
			turnMotors();
		}
}

void usDelay(uint32_t uSec)
{
	if(uSec < 2) uSec = 2;
	usTIM->ARR = uSec - 1; 	/*sets the value in the auto-reload register*/
	usTIM->EGR = 1; 			/*Re-initialises the timer*/
	usTIM->SR &= ~1; 		//Resets the flag
	usTIM->CR1 |= 1; 		//Enables the counter
	while((usTIM->SR&0x0001) != 1);
	usTIM->SR &= ~(0x0001);
}

