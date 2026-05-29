#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Generuje softwarové zpoždění v milisekundách pomocí periferie SysTick.
 *
 * Funkce využívá systémový časovač (SysTick) ke smyčkovému čekání. Pro každou milisekundu
 * konfiguruje časovač na odpočet 48 000 cyklů.
 * Blokuje běh programu, dokud zadaný čas neuplyne.
 *
 * @param[in] timeMs Doba zpoždění v milisekundách.
 */

void zpozdeni(int timeMs){
    for(int i = 0; i < timeMs; i++){
        SysTick -> LOAD = 47999;
        SysTick -> VAL = 0;
        SysTick -> CTRL = 5;

        while((SysTick -> CTRL & (1<<16)) == 0){
        }
        SysTick -> CTRL = 0;
    }
}