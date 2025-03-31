#pragma once

#include <SDL3/SDL.h>

enum {
	MUS_MAINMENU
};

void music_init(void);
void music_play(int music_id, int loops);
void music_fade_out(int ms);
