#ifndef INTRO_H
#define INTRO_H

#include "types.h"

#define INTRO_TIME (4 << SHIFT_AMOUNT)

void intro_init();
void intro_draw();
void intro_update(int dt);

#endif
