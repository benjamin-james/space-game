#include "game.h"

/*
 * Let's please use documentation
 * above the function rather than
 * inside it
 */

/*
 * The entry point
 */
int main(int argc, char **argv)
{
	struct game g;
	game_init(&g, default_render, default_update, default_get_event);
	while (g.running)
		game_loop(&g);
	game_destroy(&g);
	return 0;
}
