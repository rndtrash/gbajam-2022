#include "common.h"

#include <maxmod.h>
#include <tonc.h>

//#define NIBBLE2ASCIIHEX(n) ((char) (((n) < 10) ? (n) + 0x30 : (n) + 0x37))

GSInit const GAME_INITS[] = {
	[GAME_STATE_INTRO] = intro_init,
	[GAME_STATE_MENU] = menu_init,
//	[GAME_STATE_GAME] = game_init,
//	[GAME_STATE_ABOUT] = about_init
};

GSDraw const GAME_DRAWS[] = {
	[GAME_STATE_INTRO] = intro_draw,
	[GAME_STATE_MENU] = menu_draw,
//	[GAME_STATE_GAME] = game_draw,
//	[GAME_STATE_ABOUT] = about_draw
};

GSUpdate const GAME_UPDATES[] = {
	[GAME_STATE_INTRO] = intro_update,
	[GAME_STATE_MENU] = menu_update,
//	[GAME_STATE_GAME] = game_update,
//	[GAME_STATE_ABOUT] = about_update
};

struct Game g_game;

void game_init()
{
	g_game = (struct Game){
		.gameState = GAME_STATE_INVALID,

		.transition = (struct Transition) { .to = GAME_STATE_INVALID, .state = TRANSITION_IN, .timer = 0 },

		.draw = NULL,
		.update = NULL,

		.soundVolume = 4,
		.musicVolume = 3
	};
	transition(GAME_STATE_INTRO);
}

void game_loop()
{
	int dt = (1 << SHIFT_AMOUNT) / 60; // TODO: use millis() or smth like that

	g_game.draw();
	transition_draw();

	// dt = millis() - dt;

	g_game.update(dt);
	transition_update(dt);

	unsigned int newVolume = g_game.musicVolume * 256; // from 0 to 4 * 256 == 1024
	if (g_game.transition.timer > 0) {
		int transitionVolume = (g_game.transition.timer * newVolume) >> SHIFT_AMOUNT; // Since the timer is [0; 1], we can use it as a percentage
		if (g_game.transition.state == TRANSITION_IN)
			transitionVolume = newVolume - transitionVolume;
		newVolume = transitionVolume;
	}
	mmSetModuleVolume(newVolume);

	// DEBUG:
/*	unsigned int n = newVolume;
	char text[9] = {NIBBLE2ASCIIHEX(n >> 28), NIBBLE2ASCIIHEX((n >> 24) & 0xF), \
	NIBBLE2ASCIIHEX((n >> 20) & 0xF), NIBBLE2ASCIIHEX((n >> 16) & 0xF), \
	NIBBLE2ASCIIHEX((n >> 12) & 0xF), NIBBLE2ASCIIHEX((n >> 8) & 0xF), \
	NIBBLE2ASCIIHEX((n >> 4) & 0xF), NIBBLE2ASCIIHEX(n & 0xF), \
	0};
	tte_erase_screen();
	tte_write(text);*/
}

void transition(int to)
{
	if (is_in_transition())
		return;

	g_game.transition.to = to;
	g_game.transition.state = (g_game.gameState == GAME_STATE_INVALID) ? TRANSITION_IN : TRANSITION_OUT;
	g_game.transition.timer = TRANSITION_TIME;

	if (g_game.transition.state == TRANSITION_IN)
		change_game_state(to);
}

void transition_draw()
{
	//
}

void transition_update(int dt)
{
	if (g_game.transition.timer > 0) {
		g_game.transition.timer -= dt;
		if (g_game.transition.timer < 0) {
			if (g_game.transition.state == TRANSITION_OUT) {
				g_game.transition.state = TRANSITION_IN;
				g_game.transition.timer = TRANSITION_TIME;
				change_game_state(g_game.transition.to);
			} else
				g_game.transition.timer = 0;
		}
	}
}

void change_game_state(int to)
{
	g_game.draw = GAME_DRAWS[to];
	g_game.update = GAME_UPDATES[to];
	g_game.gameState = to;

	GAME_INITS[to]();
}
