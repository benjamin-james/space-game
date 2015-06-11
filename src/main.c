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
	game_set_key_event_func(&g, key_event);
	game_set_mouse_moved_func(&g, mouse_moved);
	game_set_mouse_clicked_func(&g, mouse_clicked);
	while (g.running)
		game_loop(&g);
	game_destroy(&g);
	return 0;
}

void render(struct game *g)
{

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

