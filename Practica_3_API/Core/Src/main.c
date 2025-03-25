/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Cuerpo principal del programa
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * Todos los derechos reservados.
  *
  * Este software está licenciado bajo los términos que se encuentran en el archivo LICENSE
  * en el directorio raíz de este software componente.
  * Si no se incluye un archivo LICENSE, se proporciona TAL CUAL (AS-IS).
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/** @brief Manejador de la UART2. */
UART_HandleTypeDef huart2;

/** @brief Prototipo de configuración del reloj del sistema. */
void SystemClock_Config(void);
/** @brief Inicialización de pines GPIO. */
static void MX_GPIO_Init(void);
/** @brief Inicialización del periférico UART2. */
static void MX_USART2_UART_Init(void);

/**
  * @brief  Punto de entrada de la aplicación.
  * @retval int Código de retorno del programa.
  */
int main(void)
{
    HAL_Init(); /**< Inicializa los periféricos y la interfaz de memoria Flash. */
    SystemClock_Config(); /**< Configura el reloj del sistema. */
    MX_GPIO_Init(); /**< Inicializa los pines GPIO. */
    MX_USART2_UART_Init(); /**< Inicializa la UART2. */

    /**
     * @brief Variable de retardo.
     */
    delay_t myDelay;
    delayInit(&myDelay, 500); /**< Configura un retardo inicial de 500 ms. */

    /**
     * @brief Arreglo de tiempos de retardo alternantes,
     * Las constantes que se utilizan en el código no están hardcodeadas
     */
	#define CANTIDAD_TIEMPOS 4
    const uint32_t TIEMPOS[CANTIDAD_TIEMPOS] = {100, 100, 100, 100};

    uint8_t index = 0; /**< Índice de la secuencia de tiempos. */
    bool estadoEncendido = true;

    while (1)
    {
    	if (delayRead(&myDelay))
    	    {
    	        if (estadoEncendido)
    	        {
    	            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // LED ON
    	        }
    	        else
    	        {
    	            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // LED OFF
    	            index = (index + 1) % 4; // Solo avanza el índice al terminar apagado
    	        }

    	        estadoEncendido = !estadoEncendido; // Alterna entre encendido y apagado
    	        delayWrite(&myDelay, TIEMPOS[index]); // Mismo tiempo para ON y OFF
    	    }
    }
}

/**
  * @brief Configuración del reloj del sistema.
  * @retval None
  */
void SystemClock_Config(void)
{
    // Configuración del reloj del sistema basada en HSI y PLL.
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
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief Inicialización de la UART2.
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
    {
        Error_Handler();
    }
}

/**
  * @brief Inicialización de los pines GPIO.
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
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief Manejo de errores del sistema.
  * @retval None
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
