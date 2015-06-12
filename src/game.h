#ifndef GAME_H
#define GAME_H

#include "stdio.h"
#include "stdlib.h"

#include "SDL2/SDL.h"


#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define GRID_NORMAL_SIZE 20 /* in pixels */
/*
 * We probably need some way
 * to store all game data. It is
 * generic until things work.
 */

struct game {
	Uint8 state;
	void *data;
	int width, height;
	volatile int running;
	Uint32 last_time;

	Uint32 grid[GRID_WIDTH][GRID_HEIGHT];
	int cx, cy; /* current x and y of grid */
	double zoom;
	/* These should rarely be modified */
	SDL_Window *window;
	SDL_Renderer *renderer;

	void (*render)(struct game *g);
	void (*update)(struct game *g, Uint32 delta);
	void (*key_event)(struct game *g, SDL_Keycode key, Uint8 state);
	void (*mouse_motion_event)(struct game *g, SDL_MouseMotionEvent e);
	void (*mouse_button_event)(struct game *g, SDL_MouseButtonEvent e);
};

typedef void (*render_func)(struct game *g);
typedef void (*update_func)(struct game *g, Uint32 delta);
typedef void (*key_event_func)(struct game *g, SDL_Keycode key, Uint8 state);
typedef void (*mouse_moved_func)(struct game *g, SDL_MouseMotionEvent e);
typedef void (*mouse_clicked_func)(struct game *g, SDL_MouseButtonEvent e);

void game_init(struct game *g);
void game_set_render_func(struct game *g, render_func r);
void game_set_update_func(struct game *g, update_func u);
void game_set_key_func(struct game *g, key_event_func k);
void game_set_mouse_moved_func(struct game *g, mouse_moved_func m);
void game_set_mouse_clicked_func(struct game *g, mouse_clicked_func m);

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
