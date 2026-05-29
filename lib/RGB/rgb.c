#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Inicializuje RGB LED.
 *
 * Nastaví piny RGB LED jako GPIO výstupy a vypne všechny
 * barevné kanály LED.
 */

void rgbInit()
{
    PORTB->PCR[18] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTB->PCR[19] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTD->PCR[1] |= 1 << PORT_PCR_MUX_SHIFT;

    GPIOB->PDDR |= (1 << 18) | (1 << 19);
    GPIOD->PDDR |= 1 << 1;

    GPIOB->PDOR |= 1 << 18;
    GPIOB->PDOR |= 1 << 19;
    GPIOD->PDOR |= 1 << 1;
}

/**
 * @brief Zobrazí RGB barvu pomocí softwarového PWM.
 *
 * Funkce generuje PWM signál pro jednotlivé barevné složky
 * RGB LED pomocí softwarové implementace PWM.
 *
 * Hodnoty barev jsou v rozsahu 0–255.
 *
 * @param r Intenzita červené složky.
 * @param g Intenzita zelené složky.
 * @param b Intenzita modré složky.
 */

void rgb(int r, int g, int b){
    for (int i = 0; i < 255; i++) {
        if (i < r) {
            GPIOB->PDOR &= ~(1 << 18);
        } else {
            GPIOB->PDOR |= 1 << 18;
        }

        if (i < g) {
            GPIOB->PDOR &= ~(1 << 19);
        } else {
            GPIOB->PDOR |= 1 << 19;
        }

        if (i < b) {
            GPIOD->PDOR &= ~(1 << 1);
        } else {
            GPIOD->PDOR |= 1 << 1;
        }

        for (volatile int j = 0; j < 100; j++);
    }
}