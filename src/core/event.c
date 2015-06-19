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
	switch(key) {
	case g->event.map.scroll_left:
		g->grid.cx--;
		break;
	case g->event.map.scroll_up:
		g->grid.cy--;
		break;
	case g->event.map.scroll_right:
		g->grid.cx++;
		break;
	case g->event.map.scroll_down:
		g->grid.cy++;
		break;
	case g->event.map.quit:
		g->info.running = 0;
		break;
	case g->event.map.zoom_in:
		g->zoom += 5;
		break;
	case g->event.map.zoom_out:
		g->zoom -= 5;
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
