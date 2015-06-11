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
};

void init(struct game *g, SDL_Window **w, SDL_Renderer **r);
void get_event(struct game *g, SDL_Event e);
void render(struct game *g, SDL_Renderer *r);
void update(struct game *g);

/*
 * Error macros for errors, warnings, debug
 */
#define error(str, ...) { \
		fprintf(stderr, "<ERROR> in %s at line %i in %s: ", __FILE__, __func__, __LINE__); \
		fprintf(stderr, str, ##__VA_ARGS__); \
		exit(EXIT_FAILURE); }
#define warning(str, ...) { \
		fprintf(stderr, "<WARNING> in %s at line %i in %s: ", __FILE__, __func__, __LINE__); \
		fprintf(stderr, str, ##__VA_ARGS__); }
#define debug(str, ...) { \
		fprintf(stderr, "<DEBUG> in %s at line %i in %s: ", __FILE__, __func__, __LINE__); \
		fprintf(stderr, str, ##__VA_ARGS__); }
#define memchk(DATA) { \
		if ((DATA) == NULL) \
			error("Could not allocate memory\n"); }
#endif
