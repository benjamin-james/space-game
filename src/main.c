#include "SDL2/SDL.h"

/*
 * Let's please use documentation
 * above the function rather than
 * inside it
 */
int main(int argc, char **argv)
{
	SDL_Window *w;
	SDL_Init(SDL_INIT_VIDEO);
	w = SDL_CreateWindow(*argv, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_Delay(5000);
	SDL_DestroyWindow(w);
	SDL_Quit();
	return 0;
}
