/**
 * @file API_Uart.h
 * @brief Módulo de interfaz UART para STM32 utilizando HAL.
 *
 * Este archivo contiene las declaraciones de funciones para inicialización,
 * transmisión y recepción de datos por UART.
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/**
 * @brief Inicializa la UART especificada.
 *
 * Esta función se encarga de inicializar el periférico UART utilizando la configuración
 * definida en la estructura `UART_HandleTypeDef`. Además, envía un mensaje inicial
 * por el puerto serie confirmando la configuración.
 *
 * @param huartx Puntero a la estructura UART_HandleTypeDef que representa la UART a inicializar.
 * @return true si la inicialización fue exitosa, false si ocurrió un error.
 */
bool uartInit(UART_HandleTypeDef *huartx);

/**
 * @brief Envía una cadena de caracteres por UART.
 *
 * Esta función transmite una cadena de texto terminada en NULL a través del periférico UART.
 * Se valida el puntero y el tamaño máximo permitido para evitar errores.
 *
 * @param huartx Puntero al manejador de UART.
 * @param pstring Puntero a la cadena a transmitir.
 */
void uartSendString(UART_HandleTypeDef *huartx, uint8_t * pstring);

/**
 * @brief Envía una cadena de un tamaño específico por UART.
 *
 * Esta función transmite un bloque de datos de tamaño fijo a través del periférico UART.
 * Se valida el puntero y el tamaño antes de la transmisión.
 *
 * @param huartx Puntero al manejador de UART.
 * @param pstring Puntero al arreglo de datos a transmitir.
 * @param size Tamaño en bytes de los datos a enviar.
 */
void uartSendStringSize(UART_HandleTypeDef *huartx, uint8_t * pstring, uint16_t size);

/**
 * @brief Recibe una cadena de un tamaño específico por UART.
 *
 * Esta función intenta recibir una cantidad fija de bytes desde la UART,
 * con un tiempo de espera determinado por la macro `UART_TIMEOUT`.
 *
 * @param huartx Puntero al manejador de UART.
 * @param pstring Puntero al buffer donde se almacenarán los datos recibidos.
 * @param size Cantidad de bytes a recibir.
 */
void uartReceiveStringSize(UART_HandleTypeDef *huartx, uint8_t * pstring, uint16_t size);

/**
 * @brief Genera un mensaje con la configuración actual de la UART.
 *
 * @param huartx Puntero al manejador de UART.
 * @return Puntero a una cadena estática con el mensaje de configuración.
 */
char* uartGetConfigString(UART_HandleTypeDef *huartx);


#endif /* API_INC_API_UART_H_ */


