/*
 * adxl345.h
 *
 *  Created on: Mar 25, 2025
 *      Author: HP VICTUS
 */

/**
 * @file adxl345.h
 * @brief Definiciones y prototipos de funciones para el manejo del acelerómetro ADXL345 vía SPI.
 *
 * Este archivo contiene las macros y declaraciones necesarias para inicializar y leer
 * datos del acelerómetro ADXL345 usando comunicación SPI.
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "spi.h"
#include <stdint.h>

/** @defgroup ADXL345_RegMap Mapa de registros del ADXL345
 *  @{
 */
#define DEVID_R            (0x00)  /**< Dirección del registro de identificación del dispositivo */
#define DEVICE_ADDR        (0x53)  /**< Dirección del dispositivo ADXL345 (no se usa directamente en SPI) */
#define DATA_FORMAT_R      (0x31)  /**< Dirección del registro de formato de datos */
#define POWER_CTL_R        (0x2D)  /**< Dirección del registro de control de energía */
#define DATA_START_ADDR    (0x32)  /**< Dirección inicial para lectura de datos de los ejes */
/** @} */

/** @defgroup ADXL345_Config Configuraciones del ADXL345
 *  @{
 */
#define FOUR_G             (0x01)  /**< Configura el rango a ±4g */
#define RESET              (0x00)  /**< Valor de reinicio para ciertos registros */
#define SET_MEASURE_B      (0x08)  /**< Activa el bit de medición en POWER_CTL */
/** @} */

/**
 * @brief Inicializa el acelerómetro ADXL345.
 *
 * Configura el sensor para empezar a tomar mediciones con rango de ±4g
 * y activa el modo de medición.
 */
void adxl_init(void);

/**
 * @brief Lee datos desde un registro del ADXL345 vía SPI.
 *
 * @param address Dirección del registro desde donde se desea leer.
 * @param rxdata Puntero al buffer donde se almacenarán los datos leídos.
 */
void adxl_read(uint8_t address, uint8_t *rxdata);

#endif /* ADXL345_H_ */

