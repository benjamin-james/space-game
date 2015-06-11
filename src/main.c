#include "SDL2/SDL.h"

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
	SDL_Window *w;
	SDL_Renderer *r;
	SDL_Event e;
	struct game g;
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
	return 0;
}
