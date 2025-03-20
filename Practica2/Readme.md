Retardos No Bloqueantes
Este proyecto implementa retardos no bloqueantes para STM32 utilizando la HAL. A diferencia de HAL_Delay(), 
que bloquea la ejecución del programa, los retardos no bloqueantes permiten realizar otras tareas mientras 
se espera que el tiempo expire.

📌 Funcionamiento
El retardo se gestiona con la función HAL_GetTick(), que cuenta los milisegundos desde el inicio del sistema. 
Se utiliza una estructura delay_t para almacenar la duración y el estado del retardo.

Funciones disponibles
delayInit(delay_t *delay, tick_t duration): Inicializa un retardo con la duración deseada.
bool delayRead(delay_t *delay): Retorna true cuando el retardo ha expirado, sin bloquear la ejecución.
void delayWrite(delay_t *delay, tick_t duration): Modifica la duración del retardo en tiempo de ejecución.
Ventajas
-No bloquea la ejecución del código.
-Permite ejecutar otras tareas en paralelo.
-Útil para gestionar LED parpadeantes, adquisición de datos, comunicación UART, etc.

Codigo:

delay_t myDelay;
delayInit(&myDelay, 100); // Configurar un retardo de 100 ms

while (1)
{
    if (delayRead(&myDelay))
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Alternar LED
    }
}
Este método optimiza la eficiencia del microcontrolador al permitir multitarea sin necesidad de interrupciones.
