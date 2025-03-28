/**
 * @file API_debounce.h
 * @brief Declaraciones públicas para la implementación de la MEF anti-rebote.
 */

#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#include <stdbool.h>
#include <stdint.h>
#include "API_delay.h"

/**
 * @brief Inicializa la máquina de estados finita (MEF) para el maejo de rebotes del pulsador.
 *
 * Debe llamarse una vez al inicio para establecer el estado inicial y configurar el retardo.
 */
void debounceFSM_init(void);






/**
 * @brief Actualiza el estado de la MEF anti-rebote.
 *
 * Se recomienda llamarla de forma periódica dentro del bucle principal para procesar eventos.
 */
void debounceFSM_update(void);






/**
 * @brief Lee si se detectó una pulsación válida del botón (descendente).
 *
 * @return true si se detectó una pulsación desde la última lectura; false en caso contrario.
 *
 */
bool_t readKey(void);





#endif /* API_DEBOUNCE_H */
