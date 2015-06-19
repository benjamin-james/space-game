#include "math.h"

#include "SDL2/SDL.h"

#include "game.h"
#include "draw.h"

/*
 * Draws a rectangle
 * with color
 */
void draw_rect(SDL_Renderer *r, Uint32 color, int x, int y, int w, int h)
{
	SDL_Rect current = {x,y,w,h};
	SDL_SetRenderDrawColor(r, (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, 0xFF);
        SDL_RenderFillRect(r, &current);
/*	SDL_SetRenderDrawColor(r, 0, 0, 0, 0xFF);
	SDL_RenderDrawRect(r, &current);*/
}

/*
 * Draws the grid at zoom g->zoom and
 * centered at (g->cx, g->cy) on the grid
 * coordinate system.
 *
 * This function is in need of cleanup
 * especially for errors.
 * The 'for' loops seem duplicated,
 * except that sx += tile_size_x goes to sx -= tile_size_x,
 * same with the y axis. If there is a way to combine these,
 * the code would look so much better.
 */
void render(struct game *g)
{
	double tile_size_x = g->screen.width * g->grid.zoom / (GRID_NORMAL_SIZE * 100.0);
	double tile_size_y = g->screen.height * g->grid.zoom / (GRID_NORMAL_SIZE * 100.0);
	double num_tiles_w = GRID_NORMAL_SIZE * 100.0 / g->grid.zoom;
	double num_tiles_h = GRID_NORMAL_SIZE * 100.0 / g->grid.zoom;

	int i,j, sx, sy, w, h, cx, cy;
	w = round(tile_size_x) + 2;
	h = round(tile_size_y) + 2;
	cx = g->grid.cx;
	cy = g->grid.cy;
	for (i = 0, sx = (g->screen.width - tile_size_x) / 2; i < (num_tiles_w + 1)/ 2; i++, sx += tile_size_x) {
		for (j = 0, sy = (g->screen.height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy += tile_size_y)
			draw_rect(g->screen.renderer, g->grid.data[cx + i][cy + j], sx-1, sy-1, w, h);
		for (j = 0, sy = (g->screen.height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy -= tile_size_y)
			draw_rect(g->screen.renderer, g->grid.data[cx + i][cy - j], sx-1, sy-1, w, h);
	}
	for (i = 0, sx = (g->screen.width - tile_size_x) / 2; i < (num_tiles_w + 1)/ 2; i++, sx -= tile_size_x) {
		for (j = 0, sy = (g->screen.height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy += tile_size_y)
			draw_rect(g->screen.renderer, g->grid.data[cx - i][cy + j], sx-1, sy-1, w, h);
		for (j = 0, sy = (g->screen.height - tile_size_y) / 2; j < (num_tiles_h + 1) / 2; j++, sy -= tile_size_y)
			draw_rect(g->screen.renderer, g->grid.data[cx - i][cy - j], sx-1, sy-1, w, h);
	}
}
