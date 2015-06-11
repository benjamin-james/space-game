#include "stdlib.h"
#include "time.h"

#include "SDL2/SDL.h"

#include "game.h"

/*
 * Initializes the window
 * and SDL, creates a hardware
 * renderer if possible, and
 * seeds the random number
 * generator
 */
void init(struct game *g, SDL_Window **w, SDL_Renderer **r)
{
	g->running = 1;
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error("SDL_Init failed: %s\n", SDL_GetError());
	*w = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	if (!*w)
		error("Could not create window: %s\n", SDL_GetError());
	*r = SDL_CreateRenderer(*w, -1, 0);
	if (!*r)
		error("Could not create renderer: %s\n", SDL_GetError());
	SDL_GetWindowSize(*w, &g->width, &g->height);
	g->last_time = SDL_GetTicks();
}

/*
 * Function called every time an event happens,
 * so this should take care of each one, or call
 * another function to take care of a specific
 * event.
 */
void get_event(struct game *g, SDL_Event event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		switch (event.window.type) {
		case SDL_WINDOWEVENT_CLOSE:
			g->running = 0;
			return;
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			g->running = 0;
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		/* event.mouse.x, event.mouse.y */
		break;
	case SDL_QUIT:
		g->running = 0;
		break;
	default:
		break;
	}
}

/*
 * Draws all objects on the
 * screen.
 */
void render(struct game *g, SDL_Renderer *r)
{
	SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(r);

	/* DRAW STUFF */

	SDL_RenderPresent(r);
}

/*
 * Game logic such as physics, ai,
 * input checking, etc should be
 * processed here.
 */
void update(struct game *g)
{
	Uint32 current_time = SDL_GetTicks();
	Uint32 delta = current_time - g->last_time;
	g->last_time = current_time;

	debug("Delta: %u\n", delta);
	SDL_Delay(50);
}
