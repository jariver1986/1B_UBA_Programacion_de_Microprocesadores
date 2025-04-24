/*
 * spi.c
 *
 *  Created on: Mar 25, 2025
 *      Author: HP VICTUS
 */

/**
 * @file spi.c
 * @brief Implementación de funciones para configuración y uso del periférico SPI1 en STM32F4.
 */

//====================== INTERCONEXIÓN ADXL345 - STM32F446RE ======================//
// ADXL345        ->  STM32F446RE                // DESCRIPCIÓN
// ----------------------------------------------------------------------------- //
/* VCC           ->  3.3V                        // Alimentación del sensor     */
/* GND           ->  GND                         // Tierra común                */
/* CS            ->  PA9                         // Chip Select (CS) manual     */
/* SCL (CLK)     ->  PA5                         // SPI1_SCK - reloj SPI        */
/* SDA (MOSI)    ->  PA7                         // SPI1_MOSI - datos al sensor */
/* SDO (MISO)    ->  PA6                         // SPI1_MISO - datos al STM32  */
//================================================================================//


#include "spi.h"

/* Definiciones para habilitar periféricos y banderas de estado */
#define SPI1EN  (1U<<12)  /**< Habilita el reloj del módulo SPI1 */
#define GPIOAEN (1U<<0)   /**< Habilita el reloj para el puerto GPIOA */

#define SR_TXE  (1U<<1)   /**< Transmit buffer empty flag */
#define SR_RXNE (1U<<0)   /**< Receive buffer not empty flag */
#define SR_BSY  (1U<<7)   /**< SPI busy flag */

/**
 * @brief Inicializa los pines GPIOA para usar con el periférico SPI1.
 *
 * Configura PA5 (SCK), PA6 (MISO), PA7 (MOSI) en modo alternativo
 * y PA9 como salida para la selección de esclavo (CS).
 */
void spi_gpio_init(void)
{
	RCC->AHB1ENR	|= GPIOAEN;

	/* PA5 */
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |=  (1U << 11);

	/* PA6 */
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |=  (1U << 13);

	/* PA7 */
	GPIOA->MODER &= ~(1U << 14);
	GPIOA->MODER |=  (1U << 15);

	/* Set PA9 as output pin */
	GPIOA->MODER |=  (1U << 18);
	GPIOA->MODER &= ~(1U << 19);

	/* Configura funciones alternativas para SPI en PA5, PA6, PA7 */
	/* PA5 */
	GPIOA->AFR[0] |=  (1U << 20);
	GPIOA->AFR[0] &= ~(1U << 21);
	GPIOA->AFR[0] |=  (1U << 22);
	GPIOA->AFR[0] &= ~(1U << 23);

	/* PA6 */
	GPIOA->AFR[0] |=  (1U << 24);
	GPIOA->AFR[0] &= ~(1U << 25);
	GPIOA->AFR[0] |=  (1U << 26);
	GPIOA->AFR[0] &= ~(1U << 27);

	/* PA7 */
	GPIOA->AFR[0] |=  (1U << 28);
	GPIOA->AFR[0] &= ~(1U << 29);
	GPIOA->AFR[0] |=  (1U << 30);
	GPIOA->AFR[0] &= ~(1U << 31);
}

/**
 * @brief Configura el módulo SPI1 para transmisión y recepción.
 *
 * Configura SPI1 como maestro, en modo full-duplex, con reloj dividido por 4,
 * CPOL y CPHA en alto, MSB primero, y con manejo por software del esclavo.
 */
void spi1_config(void)
{
    RCC->APB2ENR |= SPI1EN;

    /* Clock = fPCLK/4 */
    SPI1->CR1 |=  (1U << 3);
    SPI1->CR1 &= ~(1U << 4);
    SPI1->CR1 &= ~(1U << 5);

    /* CPOL = 1, CPHA = 1 */
    SPI1->CR1 |= (1U << 0);
    SPI1->CR1 |= (1U << 1);

    /* Full duplex */
    SPI1->CR1 &= ~(1U << 10);

    /* MSB first */
    SPI1->CR1 &= ~(1U << 7);

    /* Master mode */
    SPI1->CR1 |= (1U << 2);

    /* 8-bit data frame */
    SPI1->CR1 &= ~(1U << 11);

    /* Software slave management (SSM=1, SSI=1) */
    SPI1->CR1 |= (1U << 8);
    SPI1->CR1 |= (1U << 9);

    /* SPI enable */
    SPI1->CR1 |= (1U << 6);
}

/**
 * @brief Transmite un bloque de datos vía SPI1.
 *
 * @param data Puntero al arreglo de datos a transmitir.
 * @param size Cantidad de bytes a enviar.
 */
void spi1_transmit(uint8_t *data, uint32_t size)
{
    uint32_t i = 0;
    uint8_t temp;

    while (i < size)
    {
        while (!(SPI1->SR & SR_TXE)) {}  /**< Espera a que el buffer esté vacío */
        SPI1->DR = data[i];              /**< Envía un byte */
        i++;
    }

    while (!(SPI1->SR & SR_TXE)) {}     /**< Espera a que se termine la transmisión */
    while ((SPI1->SR & SR_BSY)) {}      /**< Espera a que el bus esté libre */

    /* Limpia el flag de overrun (lectura obligatoria de DR y SR) */
    temp = SPI1->DR;
    temp = SPI1->SR;
    (void)temp;  // Evita warning por variable no usada
}

/**
 * @brief Recibe un bloque de datos vía SPI1.
 *
 * @param data Puntero al buffer donde se almacenarán los datos recibidos.
 * @param size Cantidad de bytes a recibir.
 */
void spi1_receive(uint8_t *data, uint32_t size)
{
    while (size)
    {
        SPI1->DR = 0;  /**< Envía dato dummy para generar reloj */

        while (!(SPI1->SR & SR_RXNE)) {} /**< Espera hasta recibir datos */

        *data++ = SPI1->DR;  /**< Almacena byte recibido */
        size--;
    }
}

/**
 * @brief Habilita la línea de selección de esclavo (CS) poniéndola en bajo.
 */
void cs_enable(void)
{
    GPIOA->ODR &= ~(1U << 9);
}

/**
 * @brief Deshabilita la línea de selección de esclavo (CS) poniéndola en alto.
 */
void cs_disable(void)
{
    GPIOA->ODR |= (1U << 9);
}
