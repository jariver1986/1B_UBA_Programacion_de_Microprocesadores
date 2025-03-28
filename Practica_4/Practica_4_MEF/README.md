# 🧪 Práctica 4 - Anti-rebote con Máquina de Estados Finita (MEF)

## 🎯 Objetivo

Implementar una MEF (Máquina de Estados Finita) en lenguaje C sobre la placa **STM32F446RE** para gestionar el **anti-rebote por software** de un pulsador, encendiendo o apagando un LED en función de su estado.

---

## ⚙️ Descripción del funcionamiento

- Se implementaron los estados:
  - `BUTTON_UP`  
  - `BUTTON_FALLING`  
  - `BUTTON_DOWN`  
  - `BUTTON_RAISING`

- Se utilizó un **retardo no bloqueante** de `40 ms` implementado a través del módulo `API_delay` (reutilizado de la práctica anterior).
  
- El LED (pin `GPIOA_PIN_5`) se enciende al detectar un **flanco descendente** (presión del botón) y se apaga con el **flanco ascendente** (liberación del botón).

---

## 📂 Estructura del proyecto

- El manejo de la MEF se integró directamente en `main.c` para simplificar la arquitectura.
- Se mantuvo modularizada la lógica de retardos en:
  - `Drivers/API/Src/API_delay.c`
  - `Drivers/API/Inc/API_delay.h`

---

## 🔍 Variables claves para depuración

- `estadoActual` → indica el estado de la MEF.
- `teclaPresionada` → se activa con flanco descendente.
- `delayDebounce.running` → muestra si el retardo está activo.

---

## 📌 Consideraciones

- No se usó interrupción para el botón; se lee mediante sondeo periódico.
- La UART fue inicializada pero no utilizada en esta práctica.
- El diseño favorece legibilidad y buenas prácticas como:
  - Tipos estándar (`uint32_t`, `bool`)
  - Valores no hardcodeados (`const`, `#define`)
  - Programación defensiva (`default:` en la MEF)

---

## ✅ Estado del proyecto

🟢 Funcionamiento verificado:  
Presionar el botón enciende el LED. Soltarlo lo apaga. No se presentan falsos positivos por rebote mecánico.