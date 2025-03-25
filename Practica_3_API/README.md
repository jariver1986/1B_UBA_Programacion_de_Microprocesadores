# Práctica: Retardos no bloqueantes y control de LED con STM32

## Descripción

Esta práctica consiste en la implementación de un programa en C para microcontroladores STM32 utilizando STM32CubeIDE, cuyo objetivo principal es controlar el parpadeo de un LED conectado al pin **PA5** mediante retardos **no bloqueantes**. La frecuencia de encendido y apagado del LED está definida por una secuencia de tiempos almacenados en un arreglo `const`, evitando el uso de valores hardcodeados.

Se emplea una librería modular con temporizadores no bloqueantes 
(API_delay.c) y (API_delay.h)

estructurada y documentada con formato Doxygen para facilitar su reutilización.

---

## Objetivos

- Implementar retardos no bloqueantes utilizando `HAL_GetTick()`.
- Aplicar buenas prácticas de programación embebida (uso de `const`, tipos de `stdint.h`, código prolijo y comentado).
- Controlar la salida de un LED con diferentes tiempos de encendido/apagado definidos en un arreglo.
- Modularizar el código separando la lógica de retardos en una API reutilizable.
- Documentar funciones y estructuras utilizando comentarios tipo Doxygen.

---

## Componentes principales

- **delay_t**: Estructura de datos para manejar retardos.
- **delayInit()**: Inicializa el retardo con un valor específico.
- **delayRead()**: Verifica si ha transcurrido el retardo.
- **delayWrite()**: Cambia la duración del retardo en tiempo real.
- **delayGetCompletedCount()**: Obtiene la cantidad de veces que un retardo se completó.
- **delayResetCompletedCount()**: Reinicia dicho contador.

---

## Funcionamiento

1. El LED se enciende y apaga alternadamente usando `HAL_GPIO_WritePin()`.
2. Los tiempos de encendido y apagado se toman del arreglo `TIEMPOS[]`, que contiene 4 valores.
3. Cada parpadeo tiene una duración específica de encendido y apagado, con la misma duración en ambos casos.
4. Se alterna el estado del LED usando una variable booleana `estadoEncendido`.
5. Se evita el uso de `HAL_Delay()` para no bloquear el flujo del programa.

---

## Buenas prácticas aplicadas

- ✅ Uso de tipos estándar (`uint32_t`, `uint8_t`, `bool_t`) para portabilidad.
- ✅ Uso de constantes `const` y `#define` para evitar hardcodeo.
- ✅ Código limpio, con indentación coherente y comentarios claros.
- ✅ Documentación Doxygen para todas las funciones y estructuras.
- ✅ Separación del código de aplicación (`main.c`) y lógica de retardo (`API_delay.c`).

---

## Requisitos

- STM32CubeIDE v1.11.2
- Microcontrolador STM32F446RE (Nucleo-F446RE u otro compatible)
- LED conectado al pin PA5 (por defecto en placas Nucleo como LD2)

---

## Captura de Practica 3 API

![image](https://github.com/user-attachments/assets/a61b9d1a-5551-4c3d-ad08-c5d0778b1465)



---

## Créditos

Desarrollado como parte de una práctica de programación embebida.  
© 2025 [John Rivera] [Universidad de Buenos Aires] [Especializacion en Sistemas Embebidos]

