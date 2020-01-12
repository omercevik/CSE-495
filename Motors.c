#include "main.h"
#include "Motors.h"

void startForwardMotors(void)
{
	HAL_GPIO_WritePin(MOTOR_1_1_GPIO_Port,MOTOR_1_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_1_2_GPIO_Port,MOTOR_1_2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_2_1_GPIO_Port,MOTOR_2_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_2_2_GPIO_Port,MOTOR_2_2_Pin,GPIO_PIN_RESET);
}

void stopMotors(void)
{
	HAL_GPIO_WritePin(MOTOR_1_1_GPIO_Port,MOTOR_1_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_1_2_GPIO_Port,MOTOR_1_2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_2_1_GPIO_Port,MOTOR_2_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_2_2_GPIO_Port,MOTOR_2_2_Pin,GPIO_PIN_RESET);
}

void turnMotors(void)
{
	stopMotors();
	HAL_Delay(600);
	
	HAL_GPIO_WritePin(MOTOR_1_1_GPIO_Port,MOTOR_1_1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_1_2_GPIO_Port,MOTOR_1_2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_2_1_GPIO_Port,MOTOR_2_1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_2_2_GPIO_Port,MOTOR_2_2_Pin,GPIO_PIN_SET);
	
	HAL_Delay(600);
	startForwardMotors();
}
