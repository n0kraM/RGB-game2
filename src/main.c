/*
 * Name: main.c
 * Author: Klíš, Petrakovič
 *
 * This is a stub. Write your code here.
 *
 */

#include "wdog.h"
#include "littleHelper.h"
#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

#include "btn.h"
#include "ledbargraf.h"
#include "potenciometr.h"
#include "random.h"
#include "rgb.h"
#include "systick.h"
#include "zpozdeni.h"

#define SEKUNDA 166

/**
 * @brief Stub implementace funkce _sbrk.
 *
 * Funkce je vyžadována některými knihovnami jazyka C pro správu haldy.
 * V této implementaci není dynamická alokace podporována, proto vždy
 * vrací chybu.
 *
 * @param incr Požadovaná velikost rozšíření haldy.
 * @return Vždy vrací (void*) -1.
 */

void* _sbrk(int incr) {
    return (void*)-1;
}

void cil(int barvy[]);
void prubeh(int hracbarvy[]);
int vyhodnoceni(int barvy[], int hracbarvy[]);

int barvy[3];
int hracbarvy[3];
int body = 0;


uint32_t seed = 1;

__attribute__ ((weak)) int main(void)
{
	wdog_init(WDOG_CONF_DIS);

	rgbInit();
	btnInit();
	sysTickInit();
	ledBarInit();

	while(btn() != 8){}
	seed = SysTick->VAL;

	while (1) {
//rgb(0,0,0);
		if(btn() == 8){
			cil(barvy);
			prubeh(hracbarvy);
			int score = vyhodnoceni(barvy, hracbarvy);

			if(score == 0){
				body = 0;
			} else {
				body += score;
			}

			ledBar(body);

			rgb(0,0,0);
			zpozdeni(3000);
		}
	}

	return 0;
}

/**
 * @brief Vygeneruje cílovou RGB barvu a zobrazí ji hráči.
 *
 * Funkce náhodně vygeneruje hodnoty složek RGB v rozsahu 0–255,
 * zobrazí výslednou barvu po určitou dobu a následně ji několikrát
 * bliknutím připomene hráči.
 *
 * @param barvy Pole o velikosti 3 pro uložení RGB hodnot:
 *              [0] = červená,
 *              [1] = zelená,
 *              [2] = modrá.
 */

void cil(int barvy[]){
    for(int i = 0; i < 3; i++){
        barvy[i] = myRandom(0,255);
    }

    for(int i = 0; i < (SEKUNDA*7);i++){
		rgb(barvy[0], barvy[1], barvy[2]);
	}

    int cas = 0;

    while(cas < 3){
		rgb(0,0,0);
		zpozdeni(500);

        for(int i = 0; i < (SEKUNDA/2); i++){;
            rgb(barvy[0], barvy[1], barvy[2]);
        }
        cas++;
    }
}

/**
 * @brief Umožní hráči nastavit vlastní RGB barvu.
 *
 * Hráč pomocí tlačítek vybírá upravovanou barevnou složku
 * (červená, zelená nebo modrá) a potenciometrem nastavuje její hodnotu.
 * Nastavená barva je průběžně zobrazována na RGB LED.
 * Funkce končí po stisku potvrzovacího tlačítka.
 *
 * @param hracbarvy Pole o velikosti 3 pro uložení hráčových RGB hodnot:
 *                  [0] = červená,
 *                  [1] = zelená,
 *                  [2] = modrá.
 */

void prubeh(int hracbarvy[]){
    int red = 0, green = 0, blue = 0;
	int barva = 0, klik = 0;

    while(btn() != 8){

		klik = btn();
		if(klik > 0){
			barva = klik;
		}

		int hodnota = potenciometr();

		switch (barva)
		{
		case 1:
			red = hodnota;
			break;
		case 2:
			green = hodnota;
			break;
		case 4:
			blue = hodnota;
			break;
		default:
			break;
		}

        rgb(red,green,blue);       
    }

    hracbarvy[0] = red;
    hracbarvy[1] = green;
    hracbarvy[2] = blue;
}

/**
 * @brief Vyhodnotí podobnost cílové a hráčovy barvy.
 *
 * Funkce spočítá absolutní rozdíly jednotlivých RGB složek,
 * sečte je a podle výsledku vrátí bodové hodnocení.
 *
 * Bodování:
 * - rozdíl > 383  -> 0 bodů
 * - rozdíl 193–383 -> 1 bod
 * - rozdíl <= 192 -> 2 body
 *
 * @param barvy Pole obsahující cílovou RGB barvu.
 * @param hracbarvy Pole obsahující RGB barvu nastavenou hráčem.
 *
 * @return Počet získaných bodů:
 *         - 0 při velkém rozdílu,
 *         - 1 při středním rozdílu,
 *         - 2 při malém rozdílu.
 */

int vyhodnoceni(int barvy[], int hracbarvy[]){

    int rozdilR = barvy[0] - hracbarvy[0];
    int rozdilG = barvy[1] - hracbarvy[1];
    int rozdilB = barvy[2] - hracbarvy[2];


    rozdilR = abs(rozdilR);
    rozdilG = abs(rozdilG);
    rozdilB = abs(rozdilB);

    int celkovyrozdil = rozdilR + rozdilG + rozdilB;

        if(celkovyrozdil > 383){
            return 0;
        } else if (celkovyrozdil < 383 && celkovyrozdil > 192){
            return 1;
        } else {
            return 2;
        }
}