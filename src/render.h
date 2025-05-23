#pragma once

#include <SDL3/SDL.h>

unsigned int sdl_color_to_bitpack(SDL_Color color);

void set_draw_color(SDL_Renderer *renderer, unsigned int color);
void set_draw_color_alpha(SDL_Renderer *renderer, unsigned int color);

void draw_box(SDL_Renderer *renderer, SDL_FRect *rect);
void draw_box_hover(SDL_Renderer *renderer, SDL_FRect *rect);
void draw_box_active(SDL_Renderer *renderer, SDL_FRect *rect);

void draw_cell(SDL_Renderer *renderer, SDL_FPoint pos, unsigned int colour, float cellsize, bool claimed);

void draw_translucent_overlay(SDL_Renderer *renderer);
SDL_FRect draw_centered_fill_rect(SDL_Renderer *renderer, SDL_FPoint dimensions);
