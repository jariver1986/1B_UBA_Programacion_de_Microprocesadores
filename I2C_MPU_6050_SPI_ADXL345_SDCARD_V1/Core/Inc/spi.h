/*
 * spi.h
 *
 *  Created on: Mar 25, 2025
 *      Author: HP VICTUS
 */

/**
 * @file spi.h
 * @brief Declaraciones para la configuración y uso del módulo SPI en STM32F4.
 *
 * Este archivo contiene las funciones necesarias para inicializar los pines GPIO
 * y el periférico SPI1, así como funciones para transmitir y recibir datos mediante SPI,
 * y controlar el pin de selección de chip (CS).
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>

/**
 * @brief Inicializa los pines GPIO requeridos para la comunicación SPI.
 */
void spi_gpio_init(void);

/**
 * @brief Configura el periférico SPI1 con los parámetros adecuados.
 */
void spi1_config(void);

/**
 * @brief Transmite datos mediante SPI1.
 * @param data Puntero al buffer que contiene los datos a enviar.
 * @param size Número de bytes a transmitir.
 */
void spi1_transmit(uint8_t *data, uint32_t size);

/**
 * @brief Recibe datos mediante SPI1.
 * @param data Puntero al buffer donde se almacenarán los datos recibidos.
 * @param size Número de bytes a recibir.
 */
void spi1_receive(uint8_t *data, uint32_t size);

/**
 * @brief Activa la línea de selección de chip (CS).
 */
void cs_enable(void);

/**
 * @brief Desactiva la línea de selección de chip (CS).
 */
void cs_disable(void);

#endif /* SPI_H_ */
