/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header para main.c. Contiene definiciones comunes de la aplicación.
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "API_delay.h"
#include "API_debounce.h"

/* Función para manejo de errores -------------------------------------------*/
void Error_Handler(void);

/* Definiciones de pines -----------------------------------------------------*/
#define B1_Pin GPIO_PIN_13           /**< Botón de usuario */
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2      /**< Transmisión USART */
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3      /**< Recepción USART */
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5           /**< LED de usuario */
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13          /**< Pin TMS para depuración */
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14          /**< Pin TCK para depuración */
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3           /**< Pin SWO para trazas */
#define SWO_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
