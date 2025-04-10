#include "success.h"
#include "board.h"
#include "consts.h"
#include "font.h"
#include "gui/button.h"
#include "overlay.h"
#include "render.h"
#include "scene.h"
#include <stdio.h>

static Button continue_button;

void success_init(void) {
	BUTTON(continue_button, RECT(0, 0, 150, 40), "Continue");
}

void success_event(const SDL_Event *ev) {
	if (button_event(ev, &continue_button)) {
		hide_overlay();
		switch_scene("selectmode");
	}
}

void success_draw(SDL_Renderer *renderer) {
	draw_translucent_overlay(renderer);

	SDL_FRect pausebg_rect = draw_centered_fill_rect(renderer, POINT(20 * 10, 20 * 12));

	SDL_FRect text_rect = {pausebg_rect.x, pausebg_rect.y, pausebg_rect.w, 20*2};
	draw_text_shadow_centered(renderer, "You win!", &text_rect, 2);

	set_draw_color(renderer, 0x0C2E0B);
	SDL_RenderFillRect(renderer, &RECT(
		pausebg_rect.x, pausebg_rect.y + 35,
		pausebg_rect.w, 2));

	SDL_FPoint text_pos = { pausebg_rect.x + 25, pausebg_rect.y + 70 };

	char msg[256];

	snprintf(msg, 255, "Cells: %d", board.claimed_cells);
	draw_text_shadow(renderer, msg, text_pos.x, text_pos.y, 1.5);

	text_pos.y += 30;

	snprintf(msg, 255, "Moves: %d", board.moves);
	draw_text_shadow(renderer, msg, text_pos.x, text_pos.y, 1.5);

	continue_button.rect.x = pausebg_rect.x + CENTER(pausebg_rect.w, continue_button.rect.w);
	continue_button.rect.y = pausebg_rect.y + 20*9;

	button(renderer, &continue_button);
}

Overlay success_overlay = {
	"success",
	success_init,
	success_event,
	NULL,
	success_draw
};
