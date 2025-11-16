#ifndef HCSR05_H
#define HCSR05_H

#include "stdint.h"
#include "stm32f1xx_hal.h"

#define TRIG_PIN GPIO_PIN_9
#define TRIG_PORT GPIOB
#define ECHO_PIN GPIO_PIN_8
#define ECHO_PORT GPIOB

void HCSR05_Init();
void HCSR05_Trigger();
float HCSR05_GetDistance();

#endif
