#include "HCSR05.h"

extern TIM_HandleTypeDef htim2;

void HCSR05_Init() {
  // bat timer2
  HAL_TIM_Base_Start(&htim2);
}

void HCSR05_Trigger() {
  HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, 1);
  HAL_Delay(1);
  HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, 0);
}

float HCSR05_GetDistance() {
  uint16_t time;
  uint16_t distance;
  HCSR05_Trigger();

  // doi cho den khi chan ECHO len cao => bat dau do khoang cach
  while(HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) == 0);
  __HAL_TIM_SET_COUNTER(&htim2, 0); // thanh ghi CNT dem den ARR thi reset ve 0
  // sau khi len cao, doi cho den khi chan ECHo xuong thap
  while(HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) == 1);
  // time o day tinh bang us : 1 cnt = 1us trong timer2 da cau hinh truoc do
  time = __HAL_TIM_GET_COUNTER(&htim2); // tinh thoi gian tu luc phat o chan TRIG den khi thu ve o chan ECHO
  distance = (time * 1.0) * 0.034 / 2; // tinh khoang cach dua vao van toc am thanh
  // gioi han pham vi
  if(distance > 10) {
    distance = 10;
  }
  if(distance < 0) {
    distance = 0;
  } 

  return distance;
}
