/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

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
#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

#define DRV_BYTE_ORDER  DRV_LITTLE_ENDIAN
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void SystemClock_Config(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WK_UP_Interrupt_Pin GPIO_PIN_4
#define WK_UP_Interrupt_GPIO_Port GPIOE
#define ACC_SCK_Pin GPIO_PIN_1
#define ACC_SCK_GPIO_Port GPIOA
#define BLINKY_Pin GPIO_PIN_3
#define BLINKY_GPIO_Port GPIOA
#define ACC_CS_Pin GPIO_PIN_4
#define ACC_CS_GPIO_Port GPIOA
#define ACC_MISO_Pin GPIO_PIN_6
#define ACC_MISO_GPIO_Port GPIOA
#define ACC_MOSI_Pin GPIO_PIN_7
#define ACC_MOSI_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
