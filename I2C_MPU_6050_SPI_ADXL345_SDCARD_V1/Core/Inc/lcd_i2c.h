/*
 * lcd_i2c.h
 *
 *  Created on: 20 abr. 2025
 *      Author: HP VICTUS
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

// Dirección del LCD (PCF8574)
// ⚠️ Si tu módulo tiene dirección 0x3F en vez de 0x27, cámbialo aquí
#define LCD_I2C_ADDR (0x27 << 1)  // Dirección de 7 bits << 1 para HAL

// Inicializa el LCD (modo 4 bits)
void LCD_Init(I2C_HandleTypeDef *hi2c);

// Envía un comando (como limpiar pantalla, mover cursor, etc.)
void LCD_SendCommand(I2C_HandleTypeDef *hi2c, uint8_t cmd);

// Envía un carácter (letra, número, etc.)
void LCD_SendData(I2C_HandleTypeDef *hi2c, uint8_t data);

// Envía una cadena completa (texto)
void LCD_SendString(I2C_HandleTypeDef *hi2c, const char *str);

#endif /* INC_LCD_I2C_H_ */
