#ifndef EVENT_H
#define EVENT_H

#include "core/game.h"
#include <SDL2/SDL.h>

void key_event(struct game *g, SDL_Keycode key, Uint8 state);
void mouse_moved(struct game *g, SDL_MouseMotionEvent e);
void mouse_clicked(struct game *g, SDL_MouseButtonEvent e);

#endif
