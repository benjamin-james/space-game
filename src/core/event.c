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
	case SDLK_ESCAPE:
		g->info.running = 0;
		break;
	case SDLK_LEFT:
		g->grid.cx--;
		break;
	case SDLK_UP:
		g->grid.cy--;
		break;
	case SDLK_RIGHT:
		g->grid.cx++;
		break;
	case SDLK_DOWN:
		g->grid.cy++;
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
