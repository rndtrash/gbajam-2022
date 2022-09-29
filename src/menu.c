#include "menu.h"

struct Menu MENU_SETTINGS;
struct Menu MENU_ROOT;

void menu_init()
{
	MENU_SETTINGS = (struct Menu) {
		.itemCount = 2,
		.items = (struct MenuItem[]) {
			(struct MenuItem) {
				.name = "Sound",
				.type = MENU_TYPE_VOLUME,
				.bottomBound = 0,
				.topBound = 4,
				.variable = &(g_game.soundVolume)
			},
			(struct MenuItem) {
				.name = "Music",
				.type = MENU_TYPE_VOLUME,
				.bottomBound = 0,
				.topBound = 4,
				.variable = &(g_game.musicVolume)
			},
		}
	};

	MENU_ROOT = (struct Menu){
		.itemCount = 3,
		.items = (struct MenuItem[]){
			(struct MenuItem) { .name = "START!", .type = MENU_TYPE_GAME_STATE, .to = GAME_STATE_GAME },
			(struct MenuItem) { .name = "Settings", .type = MENU_TYPE_SUBMENU, .submenu = &MENU_SETTINGS },
			(struct MenuItem) { .name = "About...", .type = MENU_TYPE_GAME_STATE, .to = GAME_STATE_ABOUT }
		}
	};

	g_gameStates.menu.menuStackTop = 0;
	g_gameStates.menu.current = &MENU_ROOT;
	g_gameStates.menu.item = 0;
}

void menu_draw()
{
	//
}

void menu_update(int dt)
{
	(void) dt;
}
