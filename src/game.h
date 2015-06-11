#ifndef GAME_H
#define GAME_H

#include "stdio.h"
#include "stdlib.h"

#include "SDL2/SDL.h"

/*
 * We probably need some way
 * to store all game data. It is
 * generic until things work.
 */

struct game {
	void *data;
	int width, height;
	volatile int running;
	Uint32 last_time;

	SDL_Window *window;
	SDL_Renderer *renderer;

	void (*render)(struct game *g);
	void (*update)(struct game *g, Uint32 delta);
	void (*get_event)(struct game *g, SDL_Event event);
};

typedef void (*render_func)(struct game *g);
typedef void (*update_func)(struct game *g, Uint32 delta);
typedef void (*event_func)(struct game *g, SDL_Event e);

void game_init(struct game *g, render_func renderer, update_func updater, event_func event_getter);
void game_loop(struct game *g);
void game_destroy(struct game *g);

void default_get_event(struct game *g, SDL_Event event);
void default_render(struct game *g);
void default_update(struct game *g, Uint32 delta);

/*
 * Error macros for errors, warnings, debug
 */
#define error(str, ...) { \
		fprintf(stderr, "<ERROR> in %s at line %i in %s: ", __FILE__, __LINE__, __func__); \
		fprintf(stderr, str, ##__VA_ARGS__); \
		exit(EXIT_FAILURE); }
#define warning(str, ...) { \
		fprintf(stderr, "<WARNING> in %s at line %i in %s: ", __FILE__, __LINE__, __func__); \
		fprintf(stderr, str, ##__VA_ARGS__); }
#define debug(str, ...) { \
		fprintf(stderr, "<DEBUG> in %s at line %i in %s: ", __FILE__, __LINE__, __func__); \
		fprintf(stderr, str, ##__VA_ARGS__); }
#define memchk(DATA) { \
		if ((DATA) == NULL) \
			error("Could not allocate memory\n"); }
#endif
