#include "SDL2/SDL.h"

#include "game.h"
#include "draw.h"

/*
 * Draws a rectangle in my
 * preferred style, with an
 * outline.
 */
void draw_rect(SDL_Renderer *r, Uint32 color, int x, int y, int w, int h)
{
	SDL_Rect current = {x,y,w,h};
	SDL_SetRenderDrawColor(r, (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, 0xFF);
        SDL_RenderFillRect(r, &current);
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0xFF);
	SDL_RenderDrawRect(r, &current);
}

/*
 * This function is in need of cleanup
 * especially for errors.
 * The 'for' loops seem duplicated,
 * except that sx += tile_size_x goes to sx -= tile_size_x,
 * same with the y axis. If there is a way to combine these,
 * the code would look so much better.
 */
void render(struct game *g)
{
	double tile_size_x = g->width * g->zoom / (GRID_NORMAL_SIZE * 100.0);
	double tile_size_y = g->height * g->zoom / (GRID_NORMAL_SIZE * 100.0);
	double num_tiles_w = g->width / tile_size_x;
	double num_tiles_h = g->height / tile_size_y;

	int i,j, sx, sy;
	for (i = 0, sx = (g->width - tile_size_x) / 2; i < (num_tiles_w + 1)/ 2; i++, sx += tile_size_x) {
		for (j = 0, sy = (g->height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy += tile_size_y)
			draw_rect(g->renderer, g->grid[g->cx + i][g->cy + j], sx, sy, tile_size_x, tile_size_y);
		for (j = 0, sy = (g->height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy -= tile_size_y)
			draw_rect(g->renderer, g->grid[g->cx + i][g->cy + j], sx, sy, tile_size_x, tile_size_y);
	}
	for (i = 0, sx = (g->width - tile_size_x) / 2; i < (num_tiles_w + 1)/ 2; i++, sx -= tile_size_x) {
		for (j = 0, sy = (g->height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy += tile_size_y)
			draw_rect(g->renderer, g->grid[g->cx + i][g->cy + j], sx, sy, tile_size_x, tile_size_y);
		for (j = 0, sy = (g->height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy -= tile_size_y)
			draw_rect(g->renderer, g->grid[g->cx + i][g->cy + j], sx, sy, tile_size_x, tile_size_y);
	}
}
