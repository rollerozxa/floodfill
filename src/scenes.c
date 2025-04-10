#include "scenes.h"
#include "overlays/pause.h"
#include "overlays/success.h"
#include "scene.h"
#include "scenes/about.h"
#include "scenes/exiting.h"
#include "scenes/game.h"
#include "scenes/mainmenu.h"
#include "scenes/selectmode.h"
#include "scenes/settings.h"

void register_scenes(void) {
	// First scene needs to be first
	add_scene(mainmenu_scene);
	add_scene(about_scene);
	add_scene(game_scene);
	add_scene(selectmode_scene);
	add_scene(settings_scene);
	add_scene(exiting_scene);

	add_overlay(pause_overlay);
	add_overlay(success_overlay);
}
