#include <string.h>
#include "core/tiles.h"

/*
 * Makes an empty tile at given coordinates.
 */
void init_tile(struct tile *tile, int x, int y) {
	 memset(tile, 0, sizeof(*tile));
	 tile->pt.x = x;
	 tile->pt.y = y;
}
