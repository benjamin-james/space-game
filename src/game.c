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
void game_init(struct game *g)
{
	g->running = 1;
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error("SDL_Init failed: %s\n", SDL_GetError());
	g->window = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	if (!g->window)
		error("Could not create window: %s\n", SDL_GetError());
	g->renderer = SDL_CreateRenderer(g->window, -1, 0);
	if (!g->renderer)
		error("Could not create renderer: %s\n", SDL_GetError());
	SDL_GetWindowSize(g->window, &g->width, &g->height);
	g->last_time = SDL_GetTicks();
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
		default_get_event(g, e);
	g->update(g, current_time - g->last_time);

	SDL_SetRenderDrawColor(g->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g->renderer);
	g->render(g);
	SDL_RenderPresent(g->renderer);

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
		g->key_event(g, event.key.keysym.sym, event.key.state);
		break;
	case SDL_MOUSEMOTION:
		g->mouse_motion_event(g, event.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		g->mouse_button_event(g, event.button);
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
void default_render(struct game *g)
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

/*
 * Simple set functions
 */
void game_set_render_func(struct game *g, render_func r)
{
	g->render = r;
}
void game_set_update_func(struct game *g, update_func u)
{
	g->update = u;
}
void game_set_key_func(struct game *g, key_event_func k)
{
	g->key_event = k;
}
void game_set_mouse_moved_func(struct game *g, mouse_moved_func m)
{
	g->mouse_motion_event = m;
}
void game_set_mouse_clicked_func(struct game *g, mouse_clicked_func m)
{
	g->mouse_button_event = m;
}
