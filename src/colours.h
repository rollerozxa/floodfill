#pragma once

#include <SDL3/SDL.h>

#define CLR_WHITE (SDL_Color){0xFF, 0xFF, 0xFF}
#define CLR_BLACK (SDL_Color){0x00, 0x00, 0x00}

int num_to_colour(int num);
SDL_Color num_to_colour_2(int num);
