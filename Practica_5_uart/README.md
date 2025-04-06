# Práctica 4: Detección de flancos con UART y anti-rebote

## Objetivo

Implementar un programa embebido en STM32 que utilice:
- Una **máquina de estados finita (MEF)** para el manejo del anti-rebote de un pulsador.
- Un **módulo UART personalizado** para comunicar eventos por puerto serie.
  
El sistema debe informar por UART cuando se detectan **flancos ascendentes** y **descendentes** del pulsador, utilizando una implementación desacoplada y modular.

---

## Funcionalidad implementada

- Se creó una MEF que detecta eventos de flanco:
  - **Flanco descendente** (botón presionado)
  - **Flanco ascendente** (botón liberado)
- En cada flanco detectado se envía un mensaje UART:
  - `"Flanco descendente detectado\r\n"`
  - `"Flanco ascendente detectado\r\n"`
- Se implementó una función que permite recibir por UART un carácter `'c'`.
  - Al recibirlo, se responde con la configuración actual de la UART:  
    `"Configuracion: Baudrate=115200, 8N1\r\n"`

---

## Módulos utilizados

### `API_debounce.c`
- Contiene la lógica de anti-rebote mediante una MEF de 4 estados.
- Detecta flancos y los expone mediante funciones `detectRise()` y `detectFall()`.

### `API_Uart.c`
- Implementa la inicialización, transmisión y recepción por UART.
- Todas las funciones incluyen validación de parámetros.
- Usa comentarios estilo Doxygen.
- Incluye `uartGetConfigString()` para generar un mensaje con la configuración activa.

### `API_delay.c`
- Implementa retardos no bloqueantes usando HAL y `HAL_GetTick()`.

---

## Comunicación UART

- Terminal UART configurada a `115200 baudios, 8N1, sin paridad`.
- Mensajes se transmiten en líneas nuevas para legibilidad.
- Permite ver en tiempo real las acciones del usuario sobre el botón.

---

## Buenas prácticas implementadas

- Código desacoplado y modular.
- Comentarios técnicos en formato Doxygen.
- Uso de `stdint.h` y tipos estándar (`uint32_t`, `bool_t`, etc.).
- Uso de `const` y `#define` para evitar valores hardcodeados.
- Manejo defensivo de errores y validación de parámetros.

---

## Resultado esperado

En una terminal UART conectada al STM32 se observará:

```
Flanco descendente detectado
Flanco ascendente detectado
Flanco descendente detectado
...
```

Al escribir `'c'` en la terminal:

```
Configuracion: Baudrate=115200, 8N1
```

---

## Autor

> *Práctica desarrollada por [Tu Nombre] como parte del curso de Sistemas Embebidos con STM32.*
