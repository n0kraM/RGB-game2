#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Inicializuje tlačítka.
 *
 * Nastaví příslušné piny portu A do režimu GPIO vstupu
 * pro čtení stavů tlačítek.
 */

void btnInit()
{
    PORTA->PCR[4] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTA->PCR[5] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTA->PCR[12] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTA->PCR[13] |= 1 << PORT_PCR_MUX_SHIFT;
}

/**
 * @brief Načte stav tlačítek.
 *
 * Funkce kontroluje stavy čtyř tlačítek a vrací jejich
 * kombinaci jako bitovou masku.
 *
 * Mapování bitů:
 * - bit 0 -> tlačítko PTA4
 * - bit 1 -> tlačítko PTA5
 * - bit 2 -> tlačítko PTA12
 * - bit 3 -> tlačítko PTA13
 *
 * @return Bitová maska stisknutých tlačítek.
 */

int btn(){
    int result = 0;
    if ((GPIOA->PDIR & (1 << 4)) == 0) {
        result |= 1 << 0;
    }
    if ((GPIOA->PDIR & (1 << 5)) == 0) {
        result |= 1 << 1;
    }
    if ((GPIOA->PDIR & (1 << 12)) == 0) {
        result |= 1 << 2;
    }
    if ((GPIOA->PDIR & (1 << 13)) == 0) {
        result |= 1 << 3;
    }
    return result;
}