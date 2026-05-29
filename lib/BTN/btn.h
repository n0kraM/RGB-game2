#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>

#ifndef BTN_H
#define BTN_H

#define BTN1 4
#define BTN2 5
#define BTN3 12
#define BTN4 13

void btnInit();

int btn();

#endif