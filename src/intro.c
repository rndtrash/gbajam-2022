#include "intro.h"

#include <agbabi.h>
#include <tonc.h>
#include <gbfs.h>
#include <maxmod.h>
#include "common.h"
#include "gamestates.h"
#include "soundbank.h"

void intro_init()
{
	g_gameStates.intro.timer = INTRO_TIME;

	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x64;

#ifdef ASSETS_GBFS
	const GBFS_FILE * const assets_gbfs = find_first_gbfs_file(__rom_end);
#endif

	u32 disclaimerPalSize;
	const void * disclaimerPal = gbfs_get_obj(assets_gbfs, "disclaimer.pal.bin", &disclaimerPalSize);
	__aeabi_memcpy(pal_bg_mem, disclaimerPal, disclaimerPalSize);

	u32 disclaimerImgSize;
	const void * disclaimerImg = gbfs_get_obj(assets_gbfs, "disclaimer.img.bin", &disclaimerImgSize);
	__aeabi_memcpy(&tile_mem[0][0], disclaimerImg, disclaimerImgSize);

	u32 disclaimerMapSize;
	const void * disclaimerMap = gbfs_get_obj(assets_gbfs, "disclaimer.map.bin", &disclaimerMapSize);
	__aeabi_memcpy(&se_mem[30][0], disclaimerMap, disclaimerMapSize);

	mmStart(MOD_BUYSELLTRADE, MM_PLAY_ONCE);
}

void intro_draw()
{
	// TODO: draw the intro
//	static int x = 0;
//	static int y = 0;

//	REG_BG0HOFS = x++;
//	REG_BG0HOFS = y++;
}

void intro_update(int dt)
{
	if (g_gameStates.intro.timer < 0)
	{
		if (is_in_transition())
			return;

		transition(GAME_STATE_MENU);
	}
	g_gameStates.intro.timer -= dt;
}
