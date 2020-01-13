#include "main.h"
#include "Buzzer.h"
#include "Ultrasonic.h"

int melody = 100;
bool ButtonPressed = false;
extern char uartBuf[100];
extern UART_HandleTypeDef huart2;
int melodyCounter = 0;
extern int melodyChanger;

const float ToneFreq[] = {
    1046.50, // C6
    1174.66, // D6
    1318.51, // E6
    1396.91, // F6
    1567.98, // G6
    1760.00, // A6
    1975.53, // B6
    2093.00, // C7
    -1 // End of array (if -1, then restart array index)
};

void RingingAlarm(void)
{
  /* Turn LED2 on: Alarm generation */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Button_Pin, GPIO_PIN_RESET);


  /*Configure GPIO pins : Button_Pin LCD_RS_Pin LCD_E_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	
	TIM2_Init();
	TIM3_Init();
	EXTI0_Init();

	// Buzzer plays.
	buzzerModule();
}

void buzzerModule(void)
{
  int index = 0;
  float freq = 0;
	
	while(freq != -1)
	{
		freq = ToneFreq[index++];
		startTone(freq);
		ultraSonicModule();
		HAL_Delay(melody);
		stopTone();
		HAL_Delay(melody);
	}
	if(++melodyCounter % 10 == 0 && melodyCounter < 30)
	{
			melody /= 2;
			melodyChanger *= 2;
	}
	index = 0;
	freq = 0;
}

void startTone(float freq) {
    TIM2_StartFrequency(freq / 2);
    TIM3_StartTiming();
    HAL_GPIO_WritePin(Button_GPIO_Port, Button_Pin, GPIO_PIN_RESET);
}

void stopTone() {
    // Stop Tone Gen
    TIM2->CR1 &= ~TIM_CR1_CEN;
    // Stop one-second timer
    TIM3->CR1 &= ~TIM_CR1_CEN;
    // Turn off buzzer
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Button_GPIO_Port, Button_Pin, GPIO_PIN_SET);
}
static void TIM2_Init() {
    __HAL_RCC_TIM2_CLK_ENABLE();

    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_StartFrequency(float freq) {
    // 1 cycle == 2 toggles
		TIM2->SR &= ~TIM_SR_UIF; // Clear flag
    TIM2->CNT = 0; // Clear count

    float usec = 1000000 / freq;
    TIM2->PSC = round(__PSC(usec));
    TIM2->ARR = round(__ARR(usec));

    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
        TIM2->SR &= ~TIM_SR_UIF;
    }
}


static void TIM3_Init() {
    __HAL_RCC_TIM3_CLK_ENABLE();

    TIM3->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM3_IRQn);

    long one_sec = 1 * 1000 * 1000;
    TIM3->PSC = __PSC(one_sec);
    TIM3->ARR = __ARR(one_sec);
}

void TIM3_StartTiming() {
    TIM3->SR &= ~TIM_SR_UIF; // Clear flag
    TIM3->CNT = 0; // Clear count
    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {
        TIM3->SR &= ~TIM_SR_UIF;
        stopTone();
    }
}

void EXTI0_Init() {
    EXTI->IMR |= EXTI_IMR_MR0; // Mask for EXTI0
    EXTI->FTSR |= EXTI_FTSR_TR0;// Enable Falling Edge Trigger
    EXTI->RTSR &= ~EXTI_RTSR_TR0; // Disable Rising Edge Trigger
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0_Msk;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; // Multiplex PA0 to EXTI0

    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) {
			  ButtonPressed = true;
        EXTI->PR = EXTI_PR_PR0;
    }
}
