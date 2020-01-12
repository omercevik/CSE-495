#ifndef	_ULTRASONIC_H
#define	_ULTRASONIC_H

#include <stdint.h>

#define usTIM	TIM4

void usDelay(uint32_t uSec);
void ultraSonicModule(void);

#endif
