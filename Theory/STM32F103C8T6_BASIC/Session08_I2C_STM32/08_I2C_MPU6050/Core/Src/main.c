/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define ADD_MPU6050 0xD0 // 0x68 << 1
#define RadianToDegre 57.2957 // doi radian sang do

int16_t ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0; // gia tri tho doc tu cam bien chua xu ly
float AX = 0, AY = 0, AZ = 0, GX = 0, GY = 0, GZ = 0; // gia tri tho da xu ly

//khoi tao 2 goc ban dau
float pitch = 0;
float roll = 0;

void MPU6050_Init() {
  uint8_t check;
  uint8_t mData;
  // dia chi cua MPU6050 la 0x68 nhung dia chi I2C chi truyen 7 bit nen se la 0xD0
  HAL_I2C_Mem_Read(&hi2c1, ADD_MPU6050, 0x75, 1, &check, 1, 1000);
  if(check == 0x68) {
    mData = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, ADD_MPU6050, 0x6B, 1, &mData, 1, 1000);
    mData = 0x07;
    HAL_I2C_Mem_Write(&hi2c1, ADD_MPU6050, 0x19, 1, &mData, 1, 1000);
    mData = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, ADD_MPU6050, 0x1B, 1, &mData, 1, 1000);
    mData = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, ADD_MPU6050, 0x1C, 1, &mData, 1, 1000);
  }
}

// doc gia tri con quay
void MPU6050ReadG(){
  uint8_t dataG[6]; // 6 byte = 6 thanh ghi
  HAL_I2C_Mem_Read(&hi2c1, ADD_MPU6050, 0x43, 1, dataG, 6, 1000); // doc duoc 6 byte data va luu vao mang dataG
  // ghep 2 thanh ghi lai voi nhau de tao thanh 1 gia tri data
  gx = (int16_t)(dataG[0] << 8 | dataG[1]); // dich 8 bit cua thanh ghi 0 len 8 bit cao + 8 bit cua thanh ghi 1 thanh 8 bit thap
  gy = (int16_t)(dataG[2] << 8 | dataG[3]); // dich 8 bit cua thanh ghi 2 len 8 bit cao + 8 bit cua thanh ghi 3 thanh 8 bit thap
  gz = (int16_t)(dataG[4] << 8 | dataG[5]); // dich 8 bit cua thanh ghi 4 len 8 bit cao + 8 bit cua thanh ghi 5 thanh 8 bit thap
  // xu ly du lieu tho
  GX = (float)gx/131.0;
  GY = (float)gy/131.0;
  GZ = (float)gz/131.0;
}

// doc gia tri gia toc
void MPU6050ReadA(){
  uint8_t dataA[6]; // 6 byte = 6 thanh ghi
  HAL_I2C_Mem_Read(&hi2c1, ADD_MPU6050, 0x3B, 1, dataA, 6, 1000); // doc duoc 6 byte data va luu vao mang dataA
  // ghep 2 thanh ghi lai voi nhau de tao thanh 1 gia tri data
  ax = (int16_t)(dataA[0] << 8 | dataA[1]); // dich 8 bit cua thanh ghi 0 len 8 bit cao + 8 bit cua thanh ghi 1 thanh 8 bit thap
  ay = (int16_t)(dataA[2] << 8 | dataA[3]); // dich 8 bit cua thanh ghi 2 len 8 bit cao + 8 bit cua thanh ghi 3 thanh 8 bit thap
  az = (int16_t)(dataA[4] << 8 | dataA[5]); // dich 8 bit cua thanh ghi 4 len 8 bit cao + 8 bit cua thanh ghi 5 thanh 8 bit thap
  // xu ly du lieu tho
  AX = (float)ax/16384.0;
  AY = (float)ay/16384.0;
  AZ = (float)az/16384.0;
}

// filter
void filter(float AX, float AY, float AZ, float GX, float GY, float GZ) {
  float pitchG = pitch + GX * (10000/1000000.0f);
  float rollG = pitch + GY * (10000/1000000.0f);

  float pitchA = atan2(AY, sqrt(AX*AX + AZ*AZ)) * RadianToDegre;
  float rollA = atan2(AX, sqrt(AY*AY + AZ*AZ)) * RadianToDegre;

  pitch = 0.98 * pitchG + 0.02 * pitchA;
  roll = 0.98 * rollG + 0.02 * rollA;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  MPU6050_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    MPU6050ReadG();
    MPU6050ReadA();
    filter(AX, AY, AZ, GX, GY, GZ);
    HAL_Delay(1); // thoi gian delay sau moi lan doc
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
