#include "stdlib.h"
#include "time.h" /* for time() */

#include "SDL2/SDL.h"

/*
 * Global variables
 * Let's keep these to a minimum.
 */

volatile int running = 1;

/*
 * Let's please use documentation
 * above the function rather than
 * inside it
 */
void init(SDL_Window **w, SDL_Renderer **r);
void get_event(SDL_Event e);
void render(SDL_Renderer *r);
void update(Uint32 delta);

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
		current_time = SDL_GetTicks();
		update(current_time - last_time);
		last_time = current_time;
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(r);
		render(r);
		SDL_RenderPresent(r);
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
	SDL_Init(SDL_INIT_EVERYTHING);
	*w = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	*r = SDL_CreateRenderer(*w, -1, 0);
}

/*
 * Function called every time an event happens,
 * so this should take care of each one.
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
