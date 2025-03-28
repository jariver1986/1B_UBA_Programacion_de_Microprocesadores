#include "API_debounce.h"
#include "stm32f4xx_hal.h"

/* Variables globales --------------------------------------------------------*/
#define DEBOUNCE_TIME_MS 40  ///< constantes no  hardcodeadas

// Definición de los estados posibles de MEF
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;

// Prototipos de funciones internas
static void buttonPressed(void);     // Enciende el LED
static void buttonReleased(void);    // Apaga el LED

// Variables privadas del módulo
static debounceState_t estadoActual;     // Estado actual de la MEF encapsulado static
static delay_t delayDebounce;           // Retardo no bloqueante para anti-rebote
static bool_t teclaPresionada = false;  // Bandera para flanco descendente detectado

void debounceFSM_init(void)
{
    estadoActual = BUTTON_UP;                  // Estado inicial
    delayInit(&delayDebounce, DEBOUNCE_TIME_MS);             // Configura retardo de 40 ms
}

void debounceFSM_update(void)
{
    switch (estadoActual) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) { // Botón presionado
                estadoActual = BUTTON_FALLING;
                delayInit(&delayDebounce, DEBOUNCE_TIME_MS);
            }
            break;
        case BUTTON_FALLING:
            if (delayRead(&delayDebounce)) {	//Retardo no bloqueante
                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                    estadoActual = BUTTON_DOWN;
                    teclaPresionada = true;     // Marca flanco descendente
                    buttonPressed();            // Enciende el LED
                } else {
                    estadoActual = BUTTON_UP;   // Rebote descartado
                }
            }
            break;
        case BUTTON_DOWN:
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) { // Botón soltado
                estadoActual = BUTTON_RAISING;
                delayInit(&delayDebounce, DEBOUNCE_TIME_MS);
            }
            break;
        case BUTTON_RAISING:
            if (delayRead(&delayDebounce)) {		//Retardo no bloqueante
                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
                    estadoActual = BUTTON_UP;
                    buttonReleased();           // Apaga el LED
                } else {
                    estadoActual = BUTTON_DOWN; // Rebote descartado
                }
            }
            break;
        default:
            debounceFSM_init();                 // Reinicia en caso de error
            break;
    }
}

bool_t readKey(void)
{
    if (teclaPresionada) {
        teclaPresionada = false;   // Limpia la bandera
        return true;
    }
    return false;
}

static void buttonPressed(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Enciende LED (LD2)
}

static void buttonReleased(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Apaga LED (LD2)
}
