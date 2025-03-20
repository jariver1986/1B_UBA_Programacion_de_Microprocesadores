#include "delay.h"
#include "stm32f4xx_hal.h"

void delayInit(delay_t *delay, tick_t duration) {
    delay->duration = duration;
    delay->running = false;
}

bool delayRead(delay_t *delay) {
    if (!delay->running) {
        delay->startTime = HAL_GetTick();
        delay->running = true;
        return false;
    }

    if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
        delay->running = false;
        return true;
    }

    return false;
}

void delayWrite(delay_t *delay, tick_t duration) {
    delay->duration = duration;
}
