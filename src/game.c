#include "game.h"
#include "board.h"
#include "consts.h"
#include "colours.h"
#include "font.h"
#include "gui/button.h"
#include "mouse.h"
#include "overlay.h"
#include "render.h"
#include "settings.h"
#include "scene.h"
#include "sound.h"
#include "textures.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static bool helddown = false;
static SDL_Point first_held_pos = {-1,-1};
static SDL_Point current_held_pos = {-1,-1};
static int held_sum = -1;

static int score = 0;

static SDL_FRect pause_button_rect = {NATIVE_WIDTH-24, 0, 24, 24};

void game_init(void) {
	helddown = false;

	first_held_pos = (SDL_Point){-1,-1};
	current_held_pos = (SDL_Point){-1,-1};

	board_change_size(board.w, board.h, 2);
	board_reset();
}

void game_event(const SDL_Event *ev) {
	if (has_overlay()) return;

	if (ev->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		SDL_FPoint mpos = {ev->motion.x, ev->motion.y};

		for (int x = 0; x < board.w; x++) {
			for (int y = 0; y < board.h; y++) {
				SDL_Point point = board_to_screen_coord(x, y);

				SDL_FRect rect = {point.x, point.y, board.cell_size, board.cell_size};

				if (SDL_PointInRectFloat(&POINT(ev->motion.x, ev->motion.y), &rect)) {
					if (board.p[x][y].colour != board.current_colour) {
						board_spread_colour(board.p[x][y].colour);
						sound_play(SND_SPREAD);
						board.moves++;
					}
				}
			}
		}

		if (SDL_PointInRectFloat(&mpos, &pause_button_rect)) {
			sound_play(SND_CLICK);
			switch_overlay("pause");
		}
	}
}

void game_update(void) {
	if (has_overlay() || scene_is_transitioning()) return;

	if (board.claimed_cells == board.w * board.h) {
		switch_overlay("success");
	}
}

void game_draw(SDL_Renderer *renderer) {

	for (int x = -1; x < 20; x++) {
		for (int y = -1; y < 12; y++) {
			SDL_RenderTexture(renderer, textures_get(TEX_BG_STRIPES), NULL,
				&RECT(x*32, y*32, 32, 32));
		}
	}

	set_draw_color(renderer, 0xFF00FF);
	SDL_RenderFillRect(renderer, &board.rect);

	set_draw_color(renderer, 0x123E11);
	SDL_FRect rect = {0,0,NATIVE_WIDTH,24};
	SDL_RenderFillRect(renderer, &rect);
	rect.y = NATIVE_HEIGHT - 24;
	SDL_RenderFillRect(renderer, &rect);

	for (int x = 0; x < board.w; x++) {
		for (int y = 0; y < board.h; y++) {
			SDL_FRect cellrect = {
				board.rect.x + x*board.cell_size,
				board.rect.y + y*board.cell_size,
				board.cell_size,
				board.cell_size};

			SDL_FPoint mouse;
			int pressed = mouse_get_state_scaled(renderer, &mouse.x, &mouse.y);
			float cmult = 1;
			if (SDL_PointInRectFloat(&mouse, &cellrect)) {
				cmult = pressed ? 0.8 : 1.2;
			}

			SDL_Color cell_colour = num_to_colour_2(board.p[x][y].colour);

			cell_colour.r *= cmult;
			cell_colour.g *= cmult;
			cell_colour.b *= cmult;

			SDL_Point point = board_to_screen_coord(x, y);
			draw_cell(renderer, POINT(point.x, point.y), sdl_color_to_bitpack(cell_colour), board.cell_size, board.p[x][y].claimed);
		}
	}

	char statusmsg[512];
	snprintf(statusmsg, 511, "Cells claimed: %d/%d", board.claimed_cells, board.w*board.h);
	draw_text_shadow(renderer, statusmsg, 24, 2, 2);

	SDL_FPoint mouse;
	int pressed = mouse_get_state_scaled(renderer, &mouse.x, &mouse.y);

	if (SDL_PointInRectFloat(&mouse, &pause_button_rect)) {
		if (pressed)
			SDL_SetTextureColorMod(textures_get(TEX_PAUSE), 0x88, 0x88, 0x88);
		else
		SDL_SetTextureColorMod(textures_get(TEX_PAUSE), 0xBB, 0xBB, 0xBB);
	} else
		SDL_SetTextureColorMod(textures_get(TEX_PAUSE), 0xFF, 0xFF, 0xFF);

	SDL_RenderTexture(renderer, textures_get(TEX_PAUSE), NULL, &pause_button_rect);
}

Scene game_scene = {
	"game",
	game_init,
	game_event,
	game_update,
	game_draw,
	0x1F3F8F
};
