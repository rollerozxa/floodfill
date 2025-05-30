#include "textures.h"

#include <data/background_stripes.h>
#include <data/check.h>
#include <data/cute.h>
#include <data/icon.h>
#include <data/pause.h>

#include <SDL_QOI/SDL_QOI.h>

static SDL_Texture *texture_bank[100];
static bool textures_loaded = false;

#define LOAD_TEX(id, data, len) \
	texture_bank[id] = SDL_CreateTextureFromSurface(renderer, SDL_LoadQOI_IO(SDL_IOFromMem(data, len))); \
	SDL_SetTextureScaleMode(texture_bank[id], SDL_SCALEMODE_NEAREST)

#define LOAD_TEX_LINEAR(id, data, len) \
	texture_bank[id] = SDL_CreateTextureFromSurface(renderer, SDL_LoadQOI_IO(SDL_IOFromMem(data, len))); \
	SDL_SetTextureScaleMode(texture_bank[id], SDL_SCALEMODE_LINEAR)

void textures_init(SDL_Renderer *renderer) {
	LOAD_TEX(TEX_BG_STRIPES, background_stripes_qoi, background_stripes_qoi_len);
	LOAD_TEX(TEX_CHECK, check_qoi, check_qoi_len);
	LOAD_TEX(TEX_CUTE, cute_qoi, cute_qoi_len);
	LOAD_TEX_LINEAR(TEX_ICON, icon_qoi, icon_qoi_len);
	LOAD_TEX(TEX_PAUSE, pause_qoi, pause_qoi_len);

	textures_loaded = true;
}

SDL_Texture *textures_get(int texture_id) {
	return texture_bank[texture_id];
}
