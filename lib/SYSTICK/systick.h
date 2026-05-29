#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

#ifndef SYSTICK_H
#define SYSTICK_H

extern uint32_t seed;

void sysTickInit(void);

#endif