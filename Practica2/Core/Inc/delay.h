#ifndef DELAY_H
#define DELAY_H

#include "stdint.h"
#include "stdbool.h"

typedef uint32_t tick_t;
typedef struct {
    tick_t duration;
    tick_t startTime;
    bool running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

#endif /* DELAY_H */
