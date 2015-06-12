#include "game.h"
#include "draw.h"
#include "event.h"
#include "math.h"

/*
 * Let's please use documentation
 * above the function rather than
 * inside it
 */

void update(struct game *g, Uint32 delta);

/*
 * The entry point
 */
int main(int argc, char **argv)
{
	struct game g;
	game_init(&g);
	game_set_render_func(&g, render);
	game_set_update_func(&g, update);
	game_set_key_func(&g, key_event);
	game_set_mouse_moved_func(&g, mouse_moved);
	game_set_mouse_clicked_func(&g, mouse_clicked);
	while (g.running)
		game_loop(&g);
	game_destroy(&g);
	return 0;
}


void update(struct game *g, Uint32 delta)
{
	SDL_GetWindowSize(g->window, &g->width, &g->height);
}

