#include "common.h"

GSInit const GAME_INITS[] = {
	[GAME_STATE_MENU] = menu_init,
//	GAME_STATE_GAME] = game_init,
//	GAME_STATE_ABOUT] = about_init
};

GSDraw const GAME_DRAWS[] = {
	[GAME_STATE_MENU] = menu_draw,
//	[GAME_STATE_GAME] = game_draw,
//	[GAME_STATE_ABOUT] = about_draw
};

GSUpdate const GAME_UPDATES[] = {
	[GAME_STATE_MENU] = menu_update,
//	[GAME_STATE_GAME] = game_update,
//	[GAME_STATE_ABOUT] = about_update
};

struct Game g_game;

void game_init()
{
	g_game = (struct Game){
		.gameState = GAME_STATE_INVALID,

		.transition = (struct Transition) { .to = GAME_STATE_INVALID, .state = TRANSITION_OUT, .timer = TRANSITION_TIME },

		.draw = GAME_DRAWS[GAME_STATE_MENU],
		.update = GAME_UPDATES[GAME_STATE_MENU],

		.soundVolume = 5,
		.musicVolume = 5
	};
	transition(GAME_STATE_MENU);
}

void game_loop()
{
	int dt = (60 << SHIFT_AMOUNT) / 1000; // TODO: use millis() or smth like that

	g_game.draw();
	transition_draw();

	// dt = millis() - dt;

	g_game.update(dt);
	transition_update(dt);
}

void transition(int to)
{
	if (is_in_transition())
		return;

	g_game.transition.to = to;
	g_game.transition.state = (g_game.gameState == GAME_STATE_INVALID) ? TRANSITION_IN : TRANSITION_OUT;
	g_game.transition.timer = TRANSITION_TIME;
}

void transition_draw()
{
	//
}

void transition_update(int dt)
{
	(void) dt;
}
