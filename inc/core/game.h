#ifndef GAME_H
#define GAME_H

#include <stdio.h> /* fprintf, stderr, */
#include <stdlib.h> /* size_t */

#include <SDL2/SDL.h> /* alot of stuff */

#include "core/entity.h"

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define GRID_NORMAL_SIZE 20 /* in pixels */

/*
 * We probably need some way
 * to store all game data. It is
 * generic until things work.
 */

/*
 * The first element in each module
 * is 'struct game', but it should
 * really only be used to gain access
 * to other needed modules.
 */
struct game_screen {
	struct game *g;
	SDL_Window *window;
	int width, height;
	SDL_Renderer *renderer;
	void (*render)(struct game *g);
};

/*
 * As of right now, this serves
 * as a buffer between the game objects
 * and the actual screen functions.
 */
struct game_grid {
	struct game *g;
	Uint32 data[GRID_WIDTH][GRID_HEIGHT];
	int cx, cy;
	double zoom;
};

struct game_list {
	struct sc *data;
	size_t alloc, size;
	int (*hash_func)(struct sc *s);
};

struct keymap {
	SDL_Keycode quit;
        SDL_Keycode pause;
	SDL_Keycode zoom_in;
	SDL_Keycode zoom_out;
	SDL_Keycode scroll_left;
        SDL_Keycode scroll_right;
	SDL_Keycode scroll_up;
	SDL_Keycode scroll_down;
};
/*
 * Once this modularization is sorted out,
 * the specific arguments can be figured out.
 */
struct game_event {
	struct game *g;
	void (*key_event)(struct game *g, SDL_Keycode key, Uint8 state);
	void (*mouse_motion_event)(struct game *g, SDL_MouseMotionEvent e);
	void (*mouse_button_event)(struct game *g, SDL_MouseButtonEvent e);

	struct keymap map;
};

/*
 * Vital game information,
 * in the future can contain
 * mutexes, etc
 */
struct game_info {
	struct game *g;
	Uint8 state;
	volatile int running;
	Uint32 last_time;
	void (*update)(struct game *g, Uint32 delta);
};

/*
 * Alas, this doesn't look quite as messy anymore!
 */
struct game {
	struct game_info info;
	struct game_list list;
	struct game_screen screen;
	struct game_grid grid;
	struct game_event event;
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
