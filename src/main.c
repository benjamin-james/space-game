#include "stdio.h"
#include "stdlib.h"
#include "time.h" /* for time() */

#include "SDL2/SDL.h"

/*
 * Global variables
 * Let's keep these to a minimum.
 */

volatile int running = 1;
int width, height;

/*
 * Let's please use documentation
 * above the function rather than
 * inside it
 */
void init(SDL_Window **w, SDL_Renderer **r);
void get_event(SDL_Event e);
void render(SDL_Renderer *r);
void update(Uint32 delta);

/*
 * The entry point
 */
int main(int argc, char **argv)
{
	SDL_Window *w;
	SDL_Renderer *r;
	SDL_Event e;
	Uint32 last_time, current_time;
	init(&w, &r);
	last_time = SDL_GetTicks();
	while (running) {
		while (SDL_PollEvent(&e))
			get_event(e);
		SDL_GetWindowSize(w, &width, &height);

		current_time = SDL_GetTicks();
		update(current_time - last_time);
		last_time = current_time;

		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(r);
		render(r);
		SDL_RenderPresent(r);

		SDL_Delay(50);
	}
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();
	return 0;
}

/*
 * Initializes the window
 * and SDL, creates a hardware
 * renderer if possible, and
 * seeds the random number
 * generator
 */
void init(SDL_Window **w, SDL_Renderer **r)
{
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	*w = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	if (!*w) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	*r = SDL_CreateRenderer(*w, -1, 0);
	if (!*r) {
		fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

/*
 * Function called every time an event happens,
 * so this should take care of each one, or call
 * another function to take care of a specific
 * event.
 */
void get_event(SDL_Event event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		switch (event.window.type) {
		case SDL_WINDOWEVENT_CLOSE:
			running = 0;
			return;
		}
		break;
	case SDL_QUIT:
		running = 0;
		break;
	default:
		break;
	}
}

/*
 * Draws all objects on the
 * screen.
 */
void render(SDL_Renderer *r)
{

}

/*
 * Game logic such as physics, ai,
 * input checking, etc should be
 * processed here.
 */
void update(Uint32 delta)
{

}
