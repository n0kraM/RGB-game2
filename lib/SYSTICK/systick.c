#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

extern uint32_t seed;

/**
 * @brief Inicializuje časovač SysTick.
 *
 * Nastaví SysTick na maximální hodnotu přetečení a zapne
 * časovač s procesorovým hodinovým signálem.
 */

void sysTickInit(void){
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0b101;
}