#include "game.h"

/*
 * Let's please use documentation
 * above the function rather than
 * inside it
 */

void render(struct game *g);
void update(struct game *g, Uint32 delta);
void key_event(struct game *g, SDL_Keycode key, Uint8 state);
void mouse_moved(struct game *g, SDL_MouseMotionEvent e);
void mouse_clicked(struct game *g, SDL_MouseButtonEvent e);

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

void render(struct game *g)
{
	int p = GRID_NORMAL_SIZE * g->zoom / 100.0;
	int num_tiles_w = g->width / p;
	int num_tiles_h = g->height / p;

	int i,j;
	for (i = 0; i < num_tiles_w; i++) {
		for (j = 0; j < num_tiles_h; j++) {
			SDL_Rect current = {i * p, j * p, p, p};
			Uint32 color = g->grid[i + g->cx][j + g->cy];
			SDL_SetRenderDrawColor(g->renderer, (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, 0xFF);
			SDL_RenderFillRect(g->renderer, &current);
			SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 0xFF);
			SDL_RenderDrawRect(g->renderer, &current);
		}
	}
}
void update(struct game *g, Uint32 delta)
{

}

/*
 * Callback for key presses
 * state is either SDL_PRESSED
 * or SDL_RELEASED
 */
void key_event(struct game *g, SDL_Keycode key, Uint8 state)
{
	if (state == SDL_RELEASED)
		return;
	switch(key) {
	case SDLK_ESCAPE:
		g->running = 0;
		break;
	case SDLK_LEFT:
		g->cx--;
		break;
	case SDLK_UP:
		g->cy--;
		break;
	case SDLK_RIGHT:
		g->cx++;
		break;
	case SDLK_DOWN:
		g->cy++;
		break;
	default:
		break;
	}
}

/*
 * Callback for mouse motion events
 */
void mouse_moved(struct game *g, SDL_MouseMotionEvent e)
{

}

/*
 * Callback for mouse button events
 */
void mouse_clicked(struct game *g, SDL_MouseButtonEvent e)
{

}

