/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button_Pin GPIO_PIN_13
#define Button_GPIO_Port GPIOC
#define MOTOR_1_1_Pin GPIO_PIN_0
#define MOTOR_1_1_GPIO_Port GPIOC
#define MOTOR_1_2_Pin GPIO_PIN_1
#define MOTOR_1_2_GPIO_Port GPIOC
#define MOTOR_2_1_Pin GPIO_PIN_2
#define MOTOR_2_1_GPIO_Port GPIOC
#define MOTOR_2_2_Pin GPIO_PIN_3
#define MOTOR_2_2_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_6
#define Buzzer_GPIO_Port GPIOA
#define KEYPAD_R4_Pin GPIO_PIN_1
#define KEYPAD_R4_GPIO_Port GPIOB
#define KEYPAD_C1_Pin GPIO_PIN_2
#define KEYPAD_C1_GPIO_Port GPIOB
#define KEYPAD_C2_Pin GPIO_PIN_12
#define KEYPAD_C2_GPIO_Port GPIOB
#define KEYPAD_R1_Pin GPIO_PIN_13
#define KEYPAD_R1_GPIO_Port GPIOB
#define KEYPAD_R2_Pin GPIO_PIN_14
#define KEYPAD_R2_GPIO_Port GPIOB
#define KEYPAD_R3_Pin GPIO_PIN_15
#define KEYPAD_R3_GPIO_Port GPIOB
#define TRIG_Pin GPIO_PIN_8
#define TRIG_GPIO_Port GPIOA
#define ECHO_Pin GPIO_PIN_9
#define ECHO_GPIO_Port GPIOA
#define KEYPAD_C3_Pin GPIO_PIN_11
#define KEYPAD_C3_GPIO_Port GPIOA
#define KEYPAD_C4_Pin GPIO_PIN_12
#define KEYPAD_C4_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
