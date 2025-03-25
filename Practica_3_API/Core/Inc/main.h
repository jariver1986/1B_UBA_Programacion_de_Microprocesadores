/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header para main.c. Contiene definiciones comunes de la aplicación.
  *
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * Todos los derechos reservados.
  *
  * Este software está licenciado bajo los términos que se encuentran en el archivo LICENSE
  * en el directorio raíz de este componente de software.
  * Si no se incluye un archivo LICENSE, se proporciona TAL CUAL (AS-IS).
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @typedef tick_t
 * @brief Representa una marca de tiempo en milisegundos.
 */
typedef uint32_t tick_t;

/**
 * @typedef bool_t
 * @brief Tipo booleano personalizado.
 */
typedef bool bool_t;

/**
 * @struct delay_t
 * @brief Estructura que modela un retardo no bloqueante.
 */
typedef struct {
    tick_t startTime; /**< Tiempo de inicio del retardo. */
    tick_t duration;  /**< Duración total del retardo. */
    bool_t running;   /**< Estado del retardo: corriendo o detenido. */
} delay_t;

/**
 * @brief Inicializa un retardo con duración específica.
 * @param delay Puntero a la estructura de retardo.
 * @param duration Duración en milisegundos.
 */
void delayInit(delay_t *delay, tick_t duration);

/**
 * @brief Verifica si ha transcurrido el tiempo del retardo.
 * @param delay Puntero a la estructura de retardo.
 * @return true si finalizó, false si aún está corriendo.
 */
bool_t delayRead(delay_t *delay);

/**
 * @brief Modifica la duración de un retardo.
 * @param delay Puntero a la estructura de retardo.
 * @param duration Nueva duración en milisegundos.
 */
void delayWrite(delay_t *delay, tick_t duration);

/**
 * @brief Función manejadora de errores.
 */
void Error_Handler(void);

/* Definiciones de pines -----------------------------------------------------*/
#define B1_Pin GPIO_PIN_13           /**< Botón de usuario. */
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2      /**< Transmisión USART. */
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3      /**< Recepción USART. */
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5           /**< LED de usuario. */
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13          /**< Pin TMS para depuración. */
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14          /**< Pin TCK para depuración. */
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3           /**< Pin SWO para trazas. */
#define SWO_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
