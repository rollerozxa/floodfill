#include "about.h"
#include "colours.h"
#include "consts.h"
#include "font.h"
#include "render.h"

const char *lines[] = {
	"==================================================",
	"Flood Fill is a puzzle game where your goal is to",
	"fill the game board with a single colour by",
	"changing the colour of the board."
};
const size_t line_len = sizeof(lines) / sizeof(lines[0]);

void about_draw(SDL_Renderer *renderer) {
	draw_text_shadow(renderer, "About Flood Fill", 20, 15, 4);

	for (size_t i = 0; i < line_len; i++) {
		draw_text_shadow(renderer, lines[i], 20, 65+i*25, 2);
	}

	for (size_t x = 0; x < SDL_ceilf((float)NATIVE_WIDTH/32); x++) {
		for (size_t y = 0; y < 2; y++) {
			draw_cell(renderer, POINT(x*32, NATIVE_HEIGHT-(32*(y+1))), num_to_colour(2), 32, true);
		}
	}
}

Scene about_scene = {
	"about",
	NULL,
	NULL,
	NULL,
	about_draw,
	0x1F3F8F
};
