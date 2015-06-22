#include <SDL2/SDL.h>

#include "core/game.h"
#include "core/event.h"


/*
 * Callback for key presses
 * state is either SDL_PRESSED
 * or SDL_RELEASED
 */
void key_event(struct game *g, SDL_Keycode key, Uint8 state)
{
	if (state == SDL_RELEASED)
		return;
	if (key == g->event.map.scroll_left)
		g->grid.cx--;
	else if (key == g->event.map.scroll_up)
		g->grid.cy--;
	else if (key == g->event.map.scroll_right)
		g->grid.cx++;
	else if (key == g->event.map.scroll_down)
		g->grid.cy++;
	else if (key == g->event.map.quit)
		g->info.running = 0;
	else if (key == g->event.map.zoom_in)
		g->grid.zoom += 5;
	else if (key == g->event.map.zoom_out)
		g->grid.zoom -= 5;
}

/*
 * Callback for mouse motion events
 */
void mouse_moved(struct game *g, SDL_MouseMotionEvent e)
{
	debug("game: %p mouse moved %d by %d\n", g, e.x, e.y);
}

/*
 * Callback for mouse button events
 */
void mouse_clicked(struct game *g, SDL_MouseButtonEvent e)
{
	debug("game: %p mouse clicked: %d\n", g, e.type == SDL_MOUSEBUTTONDOWN);
}
