#ifndef	_BUZZER_H
#define	_BUZZER_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define __TIM_USEC_TICK(PERIOD) ((SystemCoreClock / 1000000UL) * PERIOD)
#define __PSC(PERIOD)           (((__TIM_USEC_TICK(PERIOD) + 49999UL) / 50000UL) - 1)
#define __ARR(PERIOD)           ((__TIM_USEC_TICK(PERIOD) / (__PSC(PERIOD) + 1)) - 1)

void buzzerModule(void);
void RingingAlarm(void);

void TIM2_Init(void);
void TIM2_StartFrequency(float);
void TIM2_IRQHandler(void);

void TIM3_Init(void);
void TIM3_StartTiming(void);
void TIM3_IRQHandler(void);

void EXTI0_Init(void);
void EXTI0_IRQHandler(void);

void startTone(float);
void stopTone(void);

#endif
