/**
 * @file API_delay.h
 * @brief Implementación de una API para manejo de retardos no bloqueantes.
 */

#include "API_delay.h"

// Variable privada: solo visible dentro de este archivo .c
static uint32_t retardoCompletadoContador = 0;

// Función privada: solo se usa internamente
static void incrementarContador(void) {
    retardoCompletadoContador++;
}
/**
 * @brief Inicializa una estructura de retardo no bloqueante.
 *
 * Esta función configura la estructura de tipo @c delay_t con una duración inicial
 * y establece el estado del retardo como no activo. No inicia el conteo de tiempo.
 *
 * @param delay Puntero a la estructura @c delay_t que se desea inicializar.
 * @param duration Duración del retardo en milisegundos.
 *
 * @return Ninguno.
 */
void delayInit(delay_t *delay, tick_t duration)
{
    delay->duration = duration;  /**< Asigna la duración del retardo. */
    delay->running = false;      /**< Inicializa el estado del retardo como inactivo. */
    if (delay == NULL)			/**< control de los parámetros. */
    	return;
    if (duration == 0)			/**< control de los parámetros. */
    	return;
}

/**
 * @brief Verifica si ha transcurrido el tiempo de un retardo no bloqueante.
 *
 * Esta función se debe llamar periódicamente dentro del bucle principal.
 * Si el retardo aún no ha iniciado, lo inicia y retorna @c false.
 * Si el retardo ya está corriendo y el tiempo se ha cumplido, retorna @c true y detiene el retardo.
 *
 * @param delay Puntero a la estructura @c delay_t que representa el retardo.
 *
 * @return @c true si el retardo ha terminado, @c false en caso contrario.
 */
bool_t delayRead(delay_t *delay)
{
    if (!delay->running) {
        delay->startTime = HAL_GetTick(); /**< Captura el tiempo de inicio. */
        delay->running = true;           /**< Marca el retardo como activo. */
        return false;
    }

    if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
        delay->running = false; /**< Finaliza el retardo. */
        incrementarContador();  // 🔄 Se llama la función privada
        return true;
    }


    return false; /**< El retardo aún no ha finalizado. */
}

/**
 * @brief Modifica la duración de un retardo no bloqueante.
 *
 * Esta función permite cambiar el tiempo de duración del retardo sin reiniciar su estado actual.
 * El nuevo valor será utilizado la próxima vez que se inicie el retardo.
 *
 * @param delay Puntero a la estructura @c delay_t a la que se desea cambiar la duración.
 * @param duration Nueva duración del retardo en milisegundos.
 *
 * @return Ninguno.
 */
void delayWrite(delay_t *delay, tick_t duration)
{
    delay->duration = duration; /**< Actualiza la duración del retardo. */
    if (delay == NULL)			/**< control de los parámetros. */
        	return;
    if (duration == 0)			/**< control de los parámetros. */
        	return;
}

/**
 * @brief Verifica si el retardo está en ejecución.
 *
 * @param delay Puntero a la estructura de retardo.
 * @return true si el retardo está corriendo, false en caso contrario.
 */
bool_t delayIsRunning(delay_t *delay) {
    return delay->running; /**< Retorna el estado del retardo. */
}
/**
 * @brief Obtiene la cantidad de veces que se ha completado un retardo.
 *
 * Esta función retorna el número de veces que se ha completado un retardo
 * desde que el sistema se inició o desde la última vez que se llamó a
 * delayResetCompletedCount().
 *
 * @return Número de retardos completados (contador interno).
 */
uint32_t delayGetCompletedCount(void) {
    return retardoCompletadoContador;
}

/**
 * @brief Reinicia el contador de retardos completados.
 *
 * Esta función reinicia a cero el contador interno que lleva el registro
 * de cuántas veces se ha completado un retardo. Es útil para reiniciar
 * la medición en determinados eventos.
 */
void delayResetCompletedCount(void) {
    retardoCompletadoContador = 0;
}

