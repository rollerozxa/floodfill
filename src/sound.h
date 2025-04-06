#pragma once

#include <SDL3/SDL.h>

enum {
	SND_CLICK,
	SND_SELECT,
	SND_SPREAD,
	SND_START
};

void sound_init(void);
void sound_play(int sound_id);
