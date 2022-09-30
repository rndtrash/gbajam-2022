#ifndef GAME_STATES_H
#define GAME_STATES_H

#define MAX_MENU_DEPTH 2

struct MenuStackItem {
	struct Menu * menu;
	int item;
};

struct GSIntro {
	int timer;
};

struct GSMenu {
	struct MenuStackItem menuStack[MAX_MENU_DEPTH];
	int menuStackTop;

	struct Menu * current;
	int item;
};

union GSUnion {
	struct GSIntro intro;
	struct GSMenu menu;
//	struct GSGame game;
//	struct GSAbout about;
};

extern union GSUnion g_gameStates;

#endif
