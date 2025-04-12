#include "select_board_size.h"
#include "colours.h"
#include "consts.h"
#include "font.h"
#include "mouse.h"
#include "render.h"
#include <stdio.h>

typedef struct {
	int board_size;
	int w;
	int h;
	const char *name;
} BoardSize;

// TODO: revise dimensions
static BoardSize board_sizes[] = {
	{1, 10,5, "Small"},
	{2, 20,10, "Medium"},
	{3, 30,15, "Big"},
	{5, 40, 20, "Hyuge!"},
};
static size_t num_board_sizes = sizeof(board_sizes) / sizeof(board_sizes[0]);

void select_board_size_init(void) {

}

void select_board_size_event(const SDL_Event *ev) {
	// TODO
	switch (ev->type) {
		case SDL_EVENT_MOUSE_WHEEL:

			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:

			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			switch_scene("game");
			break;

		case SDL_EVENT_MOUSE_MOTION:

			break;
	}
}

void select_board_size_update(void) {

}

void select_board_size_draw(SDL_Renderer *renderer) {
	set_font_color(CLR_WHITE);

	draw_text_shadow(renderer, "Select board size", 10, 10, 3);

	for (size_t i = 0; i < num_board_sizes; i++) {
		set_font_color(CLR_WHITE);

		BoardSize boardsize = board_sizes[i];

		SDL_FRect rect = {
			-1, 70, 147, 210
		};
		rect.x = 11 + i * (rect.w + 10);

		int mod = 20;
		SDL_FPoint mouse;
		int pressed = mouse_get_state_scaled(renderer, &mouse.x, &mouse.y);
		if (SDL_PointInRectFloat(&mouse, &rect)) {
			if (pressed)
				mod = -10;
			else
				mod = 30;
		}

		SDL_Color color = {21+mod, 133+mod, 194+mod};
		set_draw_color(renderer, sdl_color_to_bitpack(color));

		SDL_RenderFillRect(renderer, &rect);

		float centerx = CENTER(rect.w, calculate_text_rect(boardsize.name, 3).w);
		draw_text_shadow(renderer, boardsize.name, rect.x + centerx, 205, 3);

		float cellsize = boardsize.board_size * 24;
		SDL_FPoint cell_pos = {
			rect.x + CENTER(rect.w, cellsize),
			rect.y + (125 - cellsize)};
		draw_cell(renderer, cell_pos, num_to_colour(2), cellsize, true);

		char dims[512];
		snprintf(dims, 511, "(%dx%d)", boardsize.w, boardsize.h);
		centerx = CENTER(rect.w, calculate_text_rect(dims, 2).w);
		draw_text_shadow(renderer, dims, rect.x + centerx, 250, 2);
	}
}

Scene select_board_size_scene = {
	"select_board_size",
	select_board_size_init,
	select_board_size_event,
	select_board_size_update,
	select_board_size_draw,
	0x0d7dba
};
