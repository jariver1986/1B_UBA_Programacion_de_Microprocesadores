/* lcd_hal.c */
#include "lcd_i2c.h"
#include "stm32f4xx_hal.h"
#include <string.h>

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define CMD_MODE      0x00
#define DATA_MODE     0x01

static void LCD_SendInternal(I2C_HandleTypeDef *hi2c, uint8_t data);
static void LCD_SendNibble(I2C_HandleTypeDef *hi2c, uint8_t nibble, uint8_t mode);
static void LCD_Delay(void) {
    HAL_Delay(1);
}

void LCD_Init(I2C_HandleTypeDef *hi2c) {
    HAL_Delay(50);
    LCD_SendNibble(hi2c, 0x30, CMD_MODE);
    HAL_Delay(5);
    LCD_SendNibble(hi2c, 0x30, CMD_MODE);
    HAL_Delay(1);
    LCD_SendNibble(hi2c, 0x30, CMD_MODE);
    HAL_Delay(10);
    LCD_SendNibble(hi2c, 0x20, CMD_MODE); // Modo 4 bits

    LCD_SendCommand(hi2c, 0x28);  // 2 líneas, matriz 5x8
    LCD_SendCommand(hi2c, 0x0C);  // Display ON, cursor OFF
    LCD_SendCommand(hi2c, 0x06);  // Modo entrada
    LCD_SendCommand(hi2c, 0x01);  // Limpiar pantalla
    HAL_Delay(5);
}

void LCD_SendCommand(I2C_HandleTypeDef *hi2c, uint8_t cmd) {
    LCD_SendNibble(hi2c, cmd & 0xF0, CMD_MODE);
    LCD_SendNibble(hi2c, (cmd << 4) & 0xF0, CMD_MODE);
}

void LCD_SendData(I2C_HandleTypeDef *hi2c, uint8_t data) {
    LCD_SendNibble(hi2c, data & 0xF0, DATA_MODE);
    LCD_SendNibble(hi2c, (data << 4) & 0xF0, DATA_MODE);
}

void LCD_SendString(I2C_HandleTypeDef *hi2c, const char *str) {
    while (*str) {
        LCD_SendData(hi2c, (uint8_t)(*str++));
    }
}

static void LCD_SendNibble(I2C_HandleTypeDef *hi2c, uint8_t nibble, uint8_t mode) {
    uint8_t data = nibble | LCD_BACKLIGHT | mode;
    LCD_SendInternal(hi2c, data | LCD_ENABLE);
    LCD_Delay();
    LCD_SendInternal(hi2c, data & ~LCD_ENABLE);
    LCD_Delay();
}

static void LCD_SendInternal(I2C_HandleTypeDef *hi2c, uint8_t data) {
    HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR, &data, 1, HAL_MAX_DELAY);
}
