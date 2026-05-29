#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

#ifndef ARDUINO_KP_H
#define ARDUINO_KP_H

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

#define BTN1 4
#define BTN2 5
#define BTN3 12
#define BTN4 13

extern uint32_t seed;

int btn();
void rgbInit();
void btnInit();
void rgb(int r, int g, int b);

void sysTickInit(void);
int myRandom(int min, int max);
 
int potenciometr();
void ledBarInit();
void ledBar(int body);
void spozdeni(int timeMs);

#endif