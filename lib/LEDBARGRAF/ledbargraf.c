#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Inicializuje LED lištu.
 *
 * Nastaví piny LED lišty jako GPIO výstupy a zhasne všechny LED.
 */

void ledBarInit(){
    PORTB -> PCR[8] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTB -> PCR[9] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTB -> PCR[10] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTB -> PCR[11] |= 1 << PORT_PCR_MUX_SHIFT;

    PORTC -> PCR[10] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTC -> PCR[11] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTC -> PCR[12] |= 1 << PORT_PCR_MUX_SHIFT;
    PORTC -> PCR[13] |= 1 << PORT_PCR_MUX_SHIFT;

    GPIOB->PDDR |= (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11);
    GPIOB->PDOR |= (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11);

    GPIOC->PDDR |= (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13);
    GPIOC->PDOR |= (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13);
}

/**
 * @brief Zobrazí počet bodů na LED liště.
 *
 * Funkce rozsvítí odpovídající LED podle aktuálního počtu bodů.
 * Nejprve zhasne všechny LED a následně rozsvítí jednu LED
 * odpovídající hodnotě parametru body.
 *
 * @param body Aktuální počet bodů v rozsahu 1–8.
 */

void ledBar(int body){
    for(int i = 8; i < 12; i++){
        GPIOB->PDOR |= (1 << i);
    }
    for(int i = 10; i < 14; i++){
        GPIOC->PDOR |= (1 << i);
    }

    switch(body){
        case 1:{
            GPIOB->PDOR &= ~(1 << 8);
            break;
        }
        case 2:{
            GPIOB->PDOR &= ~(1 << 9);
            break;
        }
        case 3:{
            GPIOB->PDOR &= ~(1 << 10);
            break;
        }
        case 4:{
            GPIOB->PDOR &= ~(1 << 11);
            break;
        }
        case 5:{
            GPIOC->PDOR &= ~(1 << 10);
            break;
        }
        case 6:{
            GPIOC->PDOR &= ~(1 << 11);
            break;
        }
        case 7:{
            GPIOC->PDOR &= ~(1 << 12);
            break;
        }
        case 8:{
            GPIOC->PDOR &= ~(1 << 13);
            break;
        }
        case 9 ... 100:{
            for(int i = 8; i < 12; i++){
                GPIOB->PDOR &= ~(1 << i);
            }
            for(int i = 10; i < 14; i++){
                GPIOC->PDOR &= ~(1 << i);
            }
        }
    }
}