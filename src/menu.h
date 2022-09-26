#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "gamestates.h"
#include "types.h"

enum {
	MENU_TYPE_INVALID = -1,
	MENU_TYPE_SUBMENU,
	MENU_TYPE_VOLUME,
	MENU_TYPE_GAME_STATE
};

struct MenuItem {
	const char * name;
	int type;
	union {
		struct { // MENU_TYPE_SUBMENU
			struct Menu * submenu;
		};
		struct { // MENU_TYPE_VOLUME
			int bottomBound;
			int topBound;
			int * variable;
		};
		struct { // MENU_TYPE_GAME_STATE
			int to;
		};
	};
};

struct Menu {
	int itemCount;
	struct MenuItem * items;
};

extern struct Menu MENU_ROOT;

void menu_stack_push();
void menu_stack_pop();

void menu_init();
void menu_draw();
void menu_update(int dt);

#endif
