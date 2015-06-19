#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "core/game.h"

/*
 * Initializes the window
 * and SDL, creates a hardware
 * renderer if possible, and
 * seeds the random number
 * generator
 */
void game_init(struct game *g)
{
	int i,j;
	g->info.running = 1;
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error("SDL_Init failed: %s\n", SDL_GetError());
	g->screen.window = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	if (!g->screen.window)
		error("Could not create window: %s\n", SDL_GetError());
	g->screen.renderer = SDL_CreateRenderer(g->screen.window, -1, 0);
	if (!g->screen.renderer)
		error("Could not create renderer: %s\n", SDL_GetError());
	SDL_GetWindowSize(g->screen.window, &g->screen.width, &g->screen.height);
	g->info.last_time = SDL_GetTicks();
	g->grid.zoom = 100.0;
	for (i = 0; i < GRID_WIDTH; i++) {
		for (j = 0; j < GRID_HEIGHT; j++) {
			g->grid.data[i][j] = ((rand() % 0xFFFF) << 16) | (rand() % 0xFF << 8);
		}
	}
	g->grid.cx = GRID_WIDTH / 2;
	g->grid.cy = GRID_HEIGHT / 2;

	g->list.alloc = 100;
	g->list.data = malloc(sizeof(struct sc) * g->list.alloc);
	g->list.size = 0;

	g->event.map.quit = SDLK_ESCAPE;
	g->event.map.pause = SDLK_P;
	g->event.map.zoom_in = SDLK_PLUS;
	g->event.map.zoom_out = SDLK_MINUS;
	g->event.map.scroll_left = SDLK_LEFT;
	g->event.map.scroll_right = SDLK_RIGHT;
	g->event.map.scroll_up = SDLK_UP;
	g->event.map.scroll_down = SDLK_DOWN;
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
	g->info.update(g, current_time - g->info.last_time);

	SDL_SetRenderDrawColor(g->screen.renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(g->screen.renderer);
	g->screen.render(g);
	SDL_RenderPresent(g->screen.renderer);

	g->info.last_time = current_time;
	SDL_Delay(50);
}

/*
 * Destroys all allocated resources
 * by the game for a safe exit.
 */
void game_destroy(struct game *g)
{
	SDL_DestroyRenderer(g->screen.renderer);
	SDL_DestroyWindow(g->screen.window);
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
			g->info.running = 0;
			return;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_GetWindowSize(g->screen.window, &g->screen.width, &g->screen.height);
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		debug("mouse wheel: %d\n", event.wheel.y);
		g->grid.zoom += 4*event.wheel.y;
		break;
	case SDL_KEYDOWN:
		g->event.key_event(g, event.key.keysym.sym, event.key.state);
		break;
	case SDL_MOUSEMOTION:
		g->event.mouse_motion_event(g, event.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		g->event.mouse_button_event(g, event.button);
		break;
	case SDL_QUIT:
		g->info.running = 0;
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
	g->screen.render = r;
}
void game_set_update_func(struct game *g, update_func u)
{
	g->info.update = u;
}
void game_set_key_func(struct game *g, key_event_func k)
{
	g->event.key_event = k;
}
void game_set_mouse_moved_func(struct game *g, mouse_moved_func m)
{
	g->event.mouse_motion_event = m;
}
void game_set_mouse_clicked_func(struct game *g, mouse_clicked_func m)
{
	g->event.mouse_button_event = m;
}
