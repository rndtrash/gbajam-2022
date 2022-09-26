#ifndef TYPES_H
#define TYPES_H

#define SHIFT_AMOUNT 16
#define SHIFT_MASK ((1 << SHIFT_AMOUNT) - 1)

typedef void (*GSInit)();
typedef void (*GSDraw)();
typedef void (*GSUpdate)(int dt);

enum {
	TRANSITION_NONE = -1,
	TRANSITION_OUT,
	TRANSITION_IN
};

enum {
	GAME_STATE_INVALID = -1,
	GAME_STATE_MENU,
	GAME_STATE_GAME,
	GAME_STATE_ABOUT
};

#endif
