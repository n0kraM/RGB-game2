#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

extern uint32_t seed;

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