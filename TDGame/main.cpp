#define SDL_MAIN_HANDLED
#include "Manager_game.h"

int main(int argc, char** argv) {
	Manager_game* game = Manager_game::instance();
	return game->run(argc, argv);
}