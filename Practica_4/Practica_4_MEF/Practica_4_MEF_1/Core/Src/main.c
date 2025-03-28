/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Cuerpo principal del programa.
  *                   Implementa una máquina de estados finita (MEF) para anti-rebote.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * Todos los derechos reservados.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "API_delay.h"     ///< Módulo de retardos no bloqueantes.
#include <stdbool.h>       ///< Para uso de tipo booleano estándar.

/* Variables globales --------------------------------------------------------*/
#define DEBOUNCE_TIME_MS 40  ///< constantes no  hardcodeadas

/**
 * @brief Manejador de la UART2 (no utilizado en esta práctica).
 */
UART_HandleTypeDef huart2;

/**
 * @brief Prototipo para configuración del reloj del sistema.
 */
void SystemClock_Config(void);

/**
 * @brief Inicialización de pines GPIO.
 */
static void MX_GPIO_Init(void);

/**
 * @brief Inicialización de UART2 (no utilizada en esta práctica).
 */
static void MX_USART2_UART_Init(void);

/* MEF Anti-rebote -----------------------------------------------------------*/

/**
 * @brief Estados posibles de la MEF de anti-rebote.
 */
typedef enum {
    BUTTON_UP,         ///< Botón no presionado
    BUTTON_FALLING,    ///< Posible flanco descendente (esperando confirmación)
    BUTTON_DOWN,       ///< Botón presionado
    BUTTON_RAISING     ///< Posible flanco ascendente (esperando confirmación)
} debounceState_t;

static debounceState_t estadoActual;     ///< Estado actual de la MEF
static delay_t delayDebounce;            ///< Retardo para detección de flancos
static bool teclaPresionada = false;     ///< Bandera para detectar flanco descendente

/**
 * @brief Enciende el LED de usuario (LD2).
 */
static void buttonPressed(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

/**
 * @brief Apaga el LED de usuario (LD2).
 */
static void buttonReleased(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

/**
 * @brief Inicializa la máquina de estados anti-rebote.
 */
void debounceFSM_init(void) {
    estadoActual = BUTTON_UP;
    delayInit(&delayDebounce, DEBOUNCE_TIME_MS);  ///< Configura retardo de 40 ms
}

/**
 * @brief Actualiza la MEF para el manejo del botón con anti-rebote.
 *
 * Esta función debe ser llamada periódicamente desde el bucle principal.
 * Detecta flancos del botón y ejecuta acciones en consecuencia.
 */
void debounceFSM_update(void) {
    switch (estadoActual) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                estadoActual = BUTTON_FALLING;
                delayInit(&delayDebounce, DEBOUNCE_TIME_MS);
            }
            break;

        case BUTTON_FALLING:
            if (delayRead(&delayDebounce)) {	///< Retardo no bloqueante
                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                    estadoActual = BUTTON_DOWN;
                    teclaPresionada = true;
                    buttonPressed(); ///< Acción: encender LED
                } else {
                    estadoActual = BUTTON_UP;
                }
            }
            break;

        case BUTTON_DOWN:
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
                estadoActual = BUTTON_RAISING;
                delayInit(&delayDebounce, DEBOUNCE_TIME_MS);
            }
            break;

        case BUTTON_RAISING:
            if (delayRead(&delayDebounce)) {	///< Retardo no bloqueante
                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
                    estadoActual = BUTTON_UP;
                    buttonReleased(); ///< Acción: apagar LED
                } else {
                    estadoActual = BUTTON_DOWN;
                }
            }
            break;

        default:
            debounceFSM_init(); ///< Programación defensiva: reiniciar MEF
            break;
    }
}

/* Función principal ---------------------------------------------------------*/

/**
 * @brief Punto de entrada de la aplicación.
 * @retval int Código de retorno del programa.
 */
int main(void)
{
    HAL_Init();                   ///< Inicialización de HAL y Systick
    SystemClock_Config();         ///< Configura el reloj del sistema
    MX_GPIO_Init();               ///< Inicializa entradas/salidas
    MX_USART2_UART_Init();        ///< UART (no usada en esta práctica)

    debounceFSM_init();           ///< Inicia la MEF de anti-rebote

    while (1)
    {
        debounceFSM_update();     ///< Llama periódicamente a la MEF
    }
}

/* Configuración del sistema -------------------------------------------------*/

/**
 * @brief Configuración del reloj del sistema basada en HSI y PLL.
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        Error_Handler();

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        Error_Handler();
}

/**
 * @brief Inicialización de la UART2.
 * @note No se utiliza en esta práctica.
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
        Error_Handler();
}

/**
 * @brief Inicialización de los pines GPIO.
 * @details Configura el pin del botón como entrada y el LED como salida.
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief Función de manejo de errores.
 * @details Entra en bucle infinito y desactiva interrupciones.
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1) {
        // Bucle infinito para detener la ejecución en caso de error
    }
}
