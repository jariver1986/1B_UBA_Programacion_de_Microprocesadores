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
#include "stm32f4xx_hal.h"
//#include <stdbool.h>  // Necesario para bool_t
//#include <stdint.h>   // Necesario para uint32_t
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/*typedef uint32_t tick_t; // Marca de tiempo
typedef bool bool_t;     // Tipo de dato booleano
typedef struct{
   tick_t startTime;
   tick_t duration;
   volatile bool_t running;
} delay_t;
*/
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/


///////////////
//Ver delay.h//
///////////////

/* USER CODE BEGIN EM */
/**
 * @brief  Inicializa una estructura de retardo con una duración específica.
 * @param  delay: Puntero a la estructura de retardo que se inicializará.
 * @param  duration: Duración del retardo en milisegundos.
 * @retval Ninguno.
 */
//void delayInit( delay_t * delay, tick_t duration );

/**
 * @brief  Verifica si ha transcurrido el tiempo especificado en la estructura de retardo.
 * @param  delay: Puntero a la estructura de retardo.
 * @retval true si el tiempo de retardo ha finalizado, false en caso contrario.
 */
//bool_t delayRead( delay_t * delay );

/**
 * @brief  Modifica la duración del retardo.
 * @param  delay: Puntero a la estructura de retardo.
 * @param  duration: Nueva duración del retardo en milisegundos.
 * @retval Ninguno.
 */
//void delayWrite( delay_t * delay, tick_t duration );
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
