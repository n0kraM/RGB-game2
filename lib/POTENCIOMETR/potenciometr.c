#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

#include "res_alloc.h"
#include "adc_bm.h"

/**
 * @brief Načte hodnotu potenciometru.
 *
 * Funkce přečte aktuální hodnotu potenciometru pomocí ADC
 * v 8bitovém režimu.
 *
 * @return Hodnota potenciometru v rozsahu 0–255.
 */

int potenciometr(){
    uint16_t potValue = adc_bm_read(ADC_BM_MODE_8BIT_SE, ADC_CHAN_POT1);
    return potValue;
}