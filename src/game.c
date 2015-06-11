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
void game_init(struct game *g, render_func renderer, update_func updater, event_func event_getter)
{
	g->running = 1;
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error("SDL_Init failed: %s\n", SDL_GetError());
	g->window = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	if (!g->w)
		error("Could not create window: %s\n", SDL_GetError());
	g->renderer = SDL_CreateRenderer(g->window, -1, 0);
	if (!g->r)
		error("Could not create renderer: %s\n", SDL_GetError());
	SDL_GetWindowSize(g->w, &g->width, &g->height);
	g->last_time = SDL_GetTicks();
	g->render = renderer;
	g->update = updater;
	g->get_event = event_getter;
}

/*
 * The function called on
 * every loop.
 */
void game_loop(struct game *g)
{
	SDL_Event e;
	Uint32 current_time = SDL_GetTicks();
	while (SDL_PollEvent(&e))
		g->get_event(&g, e);
	g->update(g, current_time - g->last_time);

	SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(r);
	g->render(g, r);
	SDL_RenderPresent(r);

	g->last_time = current_time;
	SDL_Delay(50);
}

/*
 * Destroys all allocated resources
 * by the game for a safe exit.
 */
void game_destroy(struct game *g)
{
	SDL_DestroyRenderer(g->renderer);
	SDL_DestroyWindow(g->window);
	SDL_Quit();
}

/*
 * Function called every time an event happens,
 * so this should take care of each one, or call
 * another function to take care of a specific
 * event.
 */
void default_get_event(struct game *g, SDL_Event event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		switch (event.window.type) {
		case SDL_WINDOWEVENT_CLOSE:
			g->running = 0;
			return;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_GetWindowSize(g->window, &g->width, &g->height);
			break;
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
 * screen. This shouldn't be the
 * main render function but implemented
 * in another file.
 */
void default_render(struct game *g, SDL_Renderer *r)
{
	/* DRAW STUFF */
}

/*
 * Game logic such as physics, ai,
 * input checking, etc should be
 * processed here.
 */
void default_update(struct game *g, Uint32 delta)
{

}
