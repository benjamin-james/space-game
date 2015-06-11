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
<<<<<<< HEAD
	game_init(&g, default_render, default_update, default_get_event);
	while (g->running)
		game_loop(&g);
	game_destroy(&g);
=======
	init(&g, &w, &r);
	while (g.running) {
		while (SDL_PollEvent(&e))
			get_event(&g, e);
		SDL_GetWindowSize(w, &g.width, &g.height);
		update(&g);
		render(&g, r);
	}
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();
>>>>>>> b0545d2e6cb1936c0cca2ff47491fcbea504a25f
	return 0;
}
