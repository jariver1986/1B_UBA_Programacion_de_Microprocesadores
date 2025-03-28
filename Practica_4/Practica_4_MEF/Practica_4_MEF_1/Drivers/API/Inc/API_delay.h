/**
 * @file API_delay.h
 * @brief Definiciones y prototipos para la implementación de retardos no bloqueantes.
 */

#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/**
 * @typedef tick_t
 * @brief Tipo de dato para representar el tiempo en milisegundos.
 */
typedef uint32_t tick_t;

/**
 * @typedef bool_t
 * @brief Tipo de dato booleano personalizado.
 */
typedef bool bool_t;

/**
 * @struct delay_t
 * @brief Estructura para gestionar un retardo no bloqueante.
 */
typedef struct {
    tick_t startTime; /**< Tiempo en el que inicia el retardo. */
    tick_t duration;  /**< Duración del retardo en milisegundos. */
    bool_t running;   /**< Indica si el retardo está corriendo. */
} delay_t;

/**
 * @brief Inicializa un retardo con una duración específica.
 *
 * @param delay Puntero a la estructura delay_t a inicializar.
 * @param duration Duración del retardo en milisegundos.
 */
void delayInit(delay_t *delay, tick_t duration);

/**
 * @brief Lee el estado del retardo.
 *
 * Inicia el retardo si aún no ha comenzado, o indica si el tiempo se ha cumplido.
 *
 * @param delay Puntero a la estructura delay_t.
 * @return true si el retardo ha finalizado, false en caso contrario.
 */
bool_t delayRead(delay_t *delay);

/**
 * @brief Actualiza la duración de un retardo.
 *
 * @param delay Puntero a la estructura delay_t.
 * @param duration Nueva duración en milisegundos.
 */
void delayWrite(delay_t *delay, tick_t duration);

/**
 * @brief Indica si un retardo está actualmente en ejecución.
 *
 * @param delay Puntero a la estructura delay_t.
 * @return true si el retardo está en ejecución, false si no.
 */
bool_t delayIsRunning(delay_t *delay);

/**
 * @brief Obtiene la cantidad de veces que se ha completado un retardo.
 * @return Número de retardos completados.
 */
uint32_t delayGetCompletedCount(void);

/**
 * @brief Reinicia a cero el contador de retardos completados.
 */
void delayResetCompletedCount(void);


#endif /* API_DELAY_H */
