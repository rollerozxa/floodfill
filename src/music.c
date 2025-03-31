#include "music.h"

#include <data/music_mainmenu.h>

#include <SDL3_mixer/SDL_mixer.h>

static Mix_Music *music_bank[100];
static bool music_loaded = false;

#define LOAD_MUSIC(id, var) \
	music_bank[id] = Mix_LoadMUS_IO(SDL_IOFromMem(var, var##_len), true)

void music_init(void) {
	LOAD_MUSIC(MUS_MAINMENU, music_mainmenu_ogg);
	//LOAD_SOUND(SND_, _ogg);

	music_loaded = true;
}

void music_play(int music_id, int loops) {
	if (!music_loaded)
		music_init();

	Mix_PlayMusic(music_bank[music_id], loops);
}

void music_fade_out(int ms) {
	Mix_FadeOutMusic(2500);
}
