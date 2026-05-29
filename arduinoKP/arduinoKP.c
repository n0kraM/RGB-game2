#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>
#include "adc_bm.h"
#include "soc_def.h"
#include "res_alloc.h"

extern uint32_t seed;

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

/**
 * @brief Generuje pseudonáhodné číslo v zadaném rozsahu.
 *
 * Funkce využívá lineární kongruentní generátor (LCG)
 * a globální proměnnou seed jako zdroj pseudonáhodnosti.
 *
 * @param min Dolní mez generovaného čísla.
 * @param max Horní mez generovaného čísla.
 *
 * @return Náhodné číslo v rozsahu <min, max>.
 */

int myRandom(int min, int max){
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    unsigned int n  = (unsigned int)(seed / 65536);
    return (n % (max - min + 1)) + min;
}


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
    }
}

/**
 * @brief Generuje softwarové zpoždění v milisekundách pomocí periferie SysTick.
 *
 * Funkce využívá systémový časovač (SysTick) ke smyčkovému čekání. Pro každou milisekundu
 * konfiguruje časovač na odpočet 48 000 cyklů.
 * Blokuje běh programu, dokud zadaný čas neuplyne.
 *
 * @param[in] timeMs Doba zpoždění v milisekundách.
 */

void spozdeni(int timeMs){
    for(int i = 0; i < timeMs; i++){
        SysTick -> LOAD = 47999;
        SysTick -> VAL = 0;
        SysTick -> CTRL = 5;

        while((SysTick -> CTRL & (1<<16)) == 0){
        }
        SysTick -> CTRL = 0;
    }
}