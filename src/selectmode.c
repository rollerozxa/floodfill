#include "selectmode.h"
#include "colours.h"
#include "font.h"
#include "mouse.h"
#include "render.h"
#include "sound.h"

typedef struct {
	const char *title;
	const char *description[4];
	char board[4][7];
	char board_claimed[4][7];
	bool disabled;
	void (*click)(void);
} Mode;

void classic_click(void) {
	switch_scene("game");
}
static void dummy_function() {}

Mode modes[] = {
	{
		"Classic",
		{
			"The classic flood",
			"fill game. Random",
			"board, limited",
			"game moves."
		},
		{
			{2,2,3,1,3,1,2},
			{1,2,2,2,2,4,1},
			{1,4,2,4,1,3,1},
			{2,3,2,3,4,3,1},
		},
		{
			{1,1,0,0,0,0,0},
			{0,1,1,1,1,0,0},
			{0,0,1,0,0,0,0},
			{0,0,1,0,0,0,0},
		},
		false,
		classic_click
	},
	{
		"Time attack",
		{
			"Previously flooded",
			"cells will switch",
			"colour. Hurry!"
		},
		{
			{2,2,3,1,3,1,2},
			{1,2,2,2,2,4,1},
			{1,4,2,4,1,3,1},
			{2,3,2,3,4,3,1},
		},
		{
			{1,1,0,0,0,0,0},
			{0,1,1,1,1,0,0},
			{0,0,1,0,0,0,0},
			{0,0,1,0,0,0,0},
		},
		true,
		dummy_function
	},
	{
		"Puzzle",
		{
			"Predefined boards,",
			"strategic moves",
			"to complete each",
			"level."
		},
		{
			{2,2,2,2,2,2,2},
			{2,2,2,2,2,2,2},
			{2,2,1,1,1,1,1},
			{2,2,1,1,1,1,1},
		},
		{
			{1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1},
			{1,1,0,0,0,0,0},
			{1,1,0,0,0,0,0},
		},
		true,
		dummy_function
	},
};
size_t mode_count = sizeof(modes) / sizeof(modes[0]);

int selected_mode = -1;

float xoff, xvel = 0;

float lerp(float a, float b, float t) {
	return a * (1-t) + b * t;
}

void selectmode_init(void) {

}

bool holdingdown = false;
float motion = 0;

void selectmode_event(const SDL_Event *ev) {
	switch (ev->type) {
		case SDL_EVENT_MOUSE_WHEEL:
			xvel -= ev->wheel.y * 45;
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			holdingdown = true;
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (xvel < 0.05 && selected_mode != -1) {
				sound_play(SND_START);
				modes[selected_mode].click();
			}
			motion = 0;
			holdingdown = false;
			break;

		case SDL_EVENT_MOUSE_MOTION:
			if (holdingdown) {
				xvel -= ev->motion.xrel;
				motion += SDL_fabs(ev->motion.xrel);
			}
			break;
	}
}

void selectmode_update(void) {
	xoff += lerp(xvel, 0, 0.75);
	xvel -= lerp(xvel, 0, 0.75);

	if (xoff < 0) {
		xoff = lerp(xoff, 0, 0.5);
	}
}

void selectmode_draw(SDL_Renderer *renderer) {
	set_font_color(CLR_WHITE);

	draw_text_shadow(renderer, "Select mode", 10, 10, 3);

	for (size_t i = 0; i < mode_count; i++) {
		set_font_color(CLR_WHITE);

		Mode mode = modes[i];

		SDL_FRect rect = {
			10 + i * 240 - xoff, 54, 230, 280
		};

		int mod = 20;
		SDL_FPoint mouse;
		int pressed = mouse_get_state_scaled(renderer, &mouse.x, &mouse.y);
		if (SDL_PointInRectFloat(&mouse, &rect) && !mode.disabled) {
			if (motion < 4) {
				if (pressed) {
					selected_mode = i;
					mod = -10;
				} else
					mod = 30;
			} else
				selected_mode = -1;
		}

		SDL_Color color = {21+mod, 133+mod, 194+mod};
		set_draw_color(renderer, sdl_color_to_bitpack(color));

		SDL_RenderFillRect(renderer, &rect);

		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 4; y++) {
				SDL_FPoint point = {
					x * 36 + rect.x + 6,
					y * 36 + rect.y + 6};

				draw_cell(renderer, point, num_to_colour(mode.board[y][x]), 36, mode.board_claimed[y][x]);
			}
		}

		float centerx = (rect.w - calculate_text_rect(mode.title, 3).w) / 2;
		draw_text_shadow(renderer, mode.title, rect.x + centerx, 205, 3);

		for (int j = 0; j < 4; j++) {
			if (mode.description[j])
				draw_text_shadow(renderer, mode.description[j], rect.x + 6, 240 + j * 20, 2);
		}

		if (mode.disabled) {
			set_draw_color_alpha(renderer, 0x000000A0);
			SDL_RenderFillRect(renderer, &rect);
			const char *coming_soon = "Coming soon!";
			set_font_color((SDL_Color){0xFF, 0x00, 0x00, 0xFF});
			for (size_t i = 0; coming_soon[i] != '\0'; i++) {
				draw_char_shadow(renderer, coming_soon[i], rect.x + i * GLYPH_WIDTH * 3 + 5, rect.y + i * 10 + 5, 3);
			}
		}
	}
}

Scene selectmode_scene = {
	"selectmode",
	selectmode_init,
	selectmode_event,
	selectmode_update,
	selectmode_draw,
	0x0d7dba
};
