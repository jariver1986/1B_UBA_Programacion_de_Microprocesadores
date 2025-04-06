/**
 * @file API_Uart.c
 * @brief Implementación del módulo de comunicación UART para STM32 usando HAL.
 *
 * Este archivo contiene las funciones para inicializar, transmitir y recibir datos
 * utilizando el periférico UART con HAL. Incluye control de errores y validación
 * de parámetros para asegurar un funcionamiento robusto.
 */

#include "API_Uart.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>  // ✅ Este es el correcto para usar snprintf


#define UART_TIMEOUT 100  /**< Tiempo máximo de espera para las operaciones UART (en ms). */
#define MAX_SIZE     1024 /**< Tamaño máximo permitido para transmisiones/recepciones UART. */

/**
 * @brief Inicializa la UART especificada y envía un mensaje de confirmación.
 *
 * Utiliza la HAL para inicializar el periférico UART pasado como parámetro.
 * También transmite un mensaje con los parámetros configurados como confirmación.
 *
 * @param huartx Puntero al manejador de la UART a inicializar.
 * @retval true si la UART fue inicializada y se transmitió el mensaje correctamente.
 * @retval false si ocurrió un error en la inicialización o transmisión.
 */
bool uartInit(UART_HandleTypeDef *huartx) {
    if (HAL_UART_Init(huartx) != HAL_OK) {
        return false;
    }

    char msg[] = "UART Inicializada: 115200 8N1\r\n";
    if (HAL_UART_Transmit(huartx, (uint8_t *)msg, strlen(msg), UART_TIMEOUT) != HAL_OK) {
        return false;
    }

    return true;
}

/**
 * @brief Transmite una cadena terminada en NULL por UART.
 *
 * La función valida el puntero y la longitud máxima antes de enviar los datos
 * para evitar errores y desbordamientos.
 *
 * @param huartx Puntero al manejador de UART.
 * @param pstring Puntero a la cadena de texto terminada en NULL.
 */
void uartSendString(UART_HandleTypeDef *huartx, uint8_t * pstring) {
    if (pstring == NULL) return;
    uint16_t len = strlen((char *)pstring);
    if (len > MAX_SIZE) return;

    HAL_UART_Transmit(huartx, pstring, len, UART_TIMEOUT);
}

/**
 * @brief Transmite una cantidad específica de bytes por UART.
 *
 * La función valida el puntero, el tamaño, y evita transmisiones excesivas.
 *
 * @param huartx Puntero al manejador de UART.
 * @param pstring Puntero al arreglo de datos a transmitir.
 * @param size Número de bytes a transmitir.
 */
void uartSendStringSize(UART_HandleTypeDef *huartx, uint8_t * pstring, uint16_t size) {
    if (pstring == NULL || size == 0 || size > MAX_SIZE) return;

    HAL_UART_Transmit(huartx, pstring, size, UART_TIMEOUT);
}

/**
 * @brief Recibe una cantidad específica de bytes por UART.
 *
 * La función espera la recepción de un bloque de datos desde la UART
 * dentro del tiempo definido por UART_TIMEOUT.
 *
 * @param huartx Puntero al manejador de UART.
 * @param pstring Puntero al buffer donde se almacenarán los datos recibidos.
 * @param size Número de bytes a recibir.
 */
void uartReceiveStringSize(UART_HandleTypeDef *huartx, uint8_t * pstring, uint16_t size) {
    if (pstring == NULL || size == 0 || size > MAX_SIZE) return;

    HAL_UART_Receive(huartx, pstring, size, UART_TIMEOUT);
}



/**
 * @brief Lee la configuracion de Uart Baudrate y la concatena en
 * msg
 *
 */
char* uartGetConfigString(UART_HandleTypeDef *huartx) {
    static char msg[64];

    if (huartx == NULL) {
        snprintf(msg, sizeof(msg), "UART inválida\r\n");
        return msg;
    }

    snprintf(msg, sizeof(msg),
             "Configuracion: Baudrate=%lu, 8N1\r\n",
             huartx->Init.BaudRate);

    return msg;
}
