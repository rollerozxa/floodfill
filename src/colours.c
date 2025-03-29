#include "colours.h"

int num_to_colour(int num) {
	switch (num) {
		case 1: return 0xC80000;
		case 2: return 0x00C800;
		case 3: return 0x1E1EC8;
		case 4: return 0xC8C800;
	}

	return 0xFF00FF;
}

SDL_Color num_to_colour_2(int num) {
	switch (num) {
		case 1: return (SDL_Color){0xC8, 0x00, 0x00, 0xFF};
		case 2: return (SDL_Color){0x00, 0xC8, 0x00, 0xFF};
		case 3: return (SDL_Color){0x1E, 0x1E, 0xC8, 0xFF};
		case 4: return (SDL_Color){0xC8, 0xC8, 0x00, 0xFF};
	}

	return (SDL_Color){0xFF, 0x00, 0xFF};
}
