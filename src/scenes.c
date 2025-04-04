#include "scenes.h"
#include "about.h"
#include "exiting.h"
#include "game.h"
#include "mainmenu.h"
#include "overlay.h"
#include "pause.h"
#include "scene.h"
#include "settings.h"

void register_scenes(void) {
	// First scene needs to be first
	add_scene(mainmenu_scene);
	add_scene(about_scene);
	add_scene(game_scene);
	add_scene(settings_scene);
	add_scene(exiting_scene);

	add_overlay(pause_overlay);
}
