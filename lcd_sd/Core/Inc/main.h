/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define user_sw_1_Pin GPIO_PIN_6
#define user_sw_1_GPIO_Port GPIOF
#define user_sw_2_Pin GPIO_PIN_7
#define user_sw_2_GPIO_Port GPIOF
#define user_sw_3_Pin GPIO_PIN_8
#define user_sw_3_GPIO_Port GPIOF
#define user_sw_4_Pin GPIO_PIN_9
#define user_sw_4_GPIO_Port GPIOF
#define lcd_D4_Pin GPIO_PIN_4
#define lcd_D4_GPIO_Port GPIOA
#define lcd_D5_Pin GPIO_PIN_5
#define lcd_D5_GPIO_Port GPIOA
#define lcd_D6_Pin GPIO_PIN_6
#define lcd_D6_GPIO_Port GPIOA
#define lcd_D7_Pin GPIO_PIN_7
#define lcd_D7_GPIO_Port GPIOA
#define lcd_RS_Pin GPIO_PIN_4
#define lcd_RS_GPIO_Port GPIOC
#define lcd_EN_Pin GPIO_PIN_5
#define lcd_EN_GPIO_Port GPIOC
#define ext_sw_1_Pin GPIO_PIN_7
#define ext_sw_1_GPIO_Port GPIOE
#define ext_sw_2_Pin GPIO_PIN_8
#define ext_sw_2_GPIO_Port GPIOE
#define ext_sw_3_Pin GPIO_PIN_9
#define ext_sw_3_GPIO_Port GPIOE
#define ext_sw_4_Pin GPIO_PIN_10
#define ext_sw_4_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
