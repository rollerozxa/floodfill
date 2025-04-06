#include "mainmenu.h"
#include "colours.h"
#include "consts.h"
#include "font.h"
#include "mouse.h"
#include "music.h"
#include "render.h"
#include "scene.h"
#include "sound.h"
#include "textures.h"

#include <math.h>
#include <stdio.h>

typedef struct {
	const char *label;
	void (*click)(void);
} Selector;

void play_click(void) {
	music_fade_out(2500);
	sound_play(SND_START);
	switch_scene("selectmode");
}

void about_click(void) {
	sound_play(SND_START);
	switch_scene("about");
}

void exit_click(void) {
	music_fade_out(500);
	switch_scene("exiting");
}

void dummy_function() {}

static Selector buttons[] = {
	{"Play Game", play_click},
	{"Statistics", dummy_function},
	{"Settings", dummy_function},
	{"About", about_click},
	{"Exit", exit_click}
};
static size_t button_count = sizeof(buttons) / sizeof(buttons[0]);
static size_t button_selected = 0;
static float select_cooldown = 0;

void mainmenu_init(void) {
	if (!music_is_playing())
		music_play(MUS_MAINMENU, -1);
}

void mainmenu_event(const SDL_Event *ev) {
	if (ev->type == SDL_EVENT_KEY_DOWN) {
		if (ev->key.scancode == SDL_SCANCODE_UP) {
			if (button_selected != 0) {
				button_selected--;
				sound_play(SND_SELECT);
			}
		}

		if (ev->key.scancode == SDL_SCANCODE_DOWN) {
			if (button_selected != button_count-1) {
				button_selected++;
				sound_play(SND_SELECT);
			}
		}
	}

	if (ev->type == SDL_EVENT_KEY_UP) {
		if (ev->key.scancode == SDL_SCANCODE_RETURN) {
			buttons[button_selected].click();
		}
	}

	for (size_t i = 0; i < button_count; i++) {
		int x = 250;
		int y = 100 + ((i+1) * 32);

		if (ev->type == SDL_EVENT_MOUSE_MOTION) {
			if (SDL_PointInRectFloat(&POINT(ev->motion.x, ev->motion.y), &RECT(x,y,96,24))) {

				if (button_selected != i) {
					button_selected = i;
					sound_play(SND_SELECT);
				}
			}
		}

		if (ev->type == SDL_EVENT_MOUSE_BUTTON_UP) {
			if (SDL_PointInRectFloat(&POINT(ev->motion.x, ev->motion.y), &RECT(x,y,96,24))) {
				buttons[button_selected].click();
			}
		}
	}
}

void mainmenu_update(void) {

}

static double bgpan = 0;

void mainmenu_draw(SDL_Renderer *renderer) {
	bgpan = fmod(bgpan + 0.25, 32);

	for (int x = -1; x < 20; x++) {
		for (int y = -1; y < 12; y++) {
			SDL_RenderTexture(renderer, textures_get(TEX_BG_STRIPES), NULL,
				&RECT(x*32+bgpan, y*32+bgpan, 32, 32));
		}
	}

	set_font_color((SDL_Color){0xFF, 0xFF, 0xFF});

	draw_text_shadow(renderer, "Flood Fill", 140+40, 20, 6);

	SDL_RenderTexture(renderer, textures_get(TEX_ICON), NULL, &RECT(80,12,96,96));

	for (size_t i = 0; i < button_count; i++) {
		int x = 250;
		int y = 100 + ((i+1) * 32);
		set_font_color((SDL_Color){200,200,200});
		if (button_selected == i) {
			SDL_FPoint mouse;
			int clicked = mouse_get_state_scaled(renderer, &mouse.x, &mouse.y);

			if (clicked == 1 && SDL_PointInRectFloat(&mouse, &RECT(x,y,96,24)))
				set_font_color((SDL_Color){130,130,130});
			else
				set_font_color((SDL_Color){255,255,255});

			draw_text_shadow(renderer, ">", x, y, 2);
		}

		draw_text_shadow(renderer, buttons[i].label, x+20, y, 2);
	}

	set_font_color((SDL_Color){255,255,255});
	char statusmsg[512];
	snprintf(statusmsg, 511, "Flood Fill ver. 1.0-dev (%s)", SDL_GetPlatform());
	draw_text_shadow(renderer, statusmsg, 0, NATIVE_HEIGHT-12, 1);
}

Scene mainmenu_scene = {
	"mainmenu",
	mainmenu_init,
	mainmenu_event,
	mainmenu_update,
	mainmenu_draw,
	0x1F3F8F
};
