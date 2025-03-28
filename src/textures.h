#pragma once

#include <SDL3/SDL.h>

enum {
	TEX_BG_STRIPES,
	TEX_CHECK,
	TEX_CUTE,
	TEX_ICON
};

void textures_init(SDL_Renderer *renderer);

SDL_Texture *textures_get(int texture_id);
