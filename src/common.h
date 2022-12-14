#ifndef COMMON_H
#define COMMON_H

#include "types.h"

#include "intro.h"
#include "menu.h"
//#include "game.h"
//#include "about.h"

#define TRANSITION_TIME (1 << SHIFT_AMOUNT)

#ifndef ASSETS_GBFS
extern const GBFS_FILE assets_gbfs[];
#else
extern const char __rom_end[];
#endif

extern GSInit const GAME_INITS[];
extern GSDraw const GAME_DRAWS[];
extern GSUpdate const GAME_UPDATES[];

struct Transition {
	int to;
	int state;
	int timer;
};

struct Game {
	int gameState;
	struct Transition transition;

	GSDraw draw;
	GSUpdate update;

	int soundVolume;
	int musicVolume;
};

extern struct Game g_game;

void game_init();
void game_loop();

inline int is_in_transition() { return g_game.transition.timer > 0; }
void transition(int to);
void transition_draw();
void transition_update(int dt);
void change_game_state(int to);

#endif
