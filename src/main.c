#include <agbabi.h>
#include <tonc.h>
#include <gbfs.h>
#include <maxmod.h>

#include "soundbank.h"

#include "common.h"

int main() __attribute__((noreturn));

int main()
{
#ifdef ASSETS_GBFS
	const GBFS_FILE * const assets_gbfs = find_first_gbfs_file(__rom_end);
#endif
	u32 soundbank_size;
	const void * soundbank_bin = gbfs_get_obj(assets_gbfs, "soundbank.bin", &soundbank_size);

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ;

	irq_init(NULL);

	// Maxmod requires the vblank interrupt to reset sound DMA.
	// Link the VBlank interrupt to mmVBlank, and enable it.
	irq_add(II_VBLANK, mmVBlank);
	irq_enable(II_VBLANK);

	// initialise maxmod with soundbank and 8 channels
	mmInitDefault((mm_addr) soundbank_bin, 8);

	mm_sound_effect ambulance = {
		{ SFX_HAMPTER }, // id
		(int) (1<<10), // rate
		0, // handle
		255, // volume
		0, // panning
	};

	mm_sound_effect boom = {
		{ SFX_HAMPTER }, // id
		(int) (1<<10), // rate
		0, // handle
		255, // volume
		255, // panning
	};

	// sound effect handle (for cancelling it later)
	mm_sfxhand amb = 0;

	game_init();

	while (1) {
		VBlankIntrWait();
		mmFrame();

		key_poll();

		game_loop();

		// Play looping ambulance sound effect out of left speaker if A button is hit
		if (key_hit(KEY_A)) {
			amb = mmEffectEx(&ambulance);
		}
		// stop ambulance sound when A button is released
		if (amb && key_released(KEY_A)) {
			mmEffectCancel(amb);
			amb = 0;
		}

		// Play explosion sound effect out of right speaker if B button is hit
		if (key_hit(KEY_B)) {
			mmEffectEx(&boom);
		}
	}
}
