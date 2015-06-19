#include "core/coordinate.h"

/*
 * Return the distance in tiles between two ships.
 * This will mostly be used in hit chance calculations.
 */
int calc_dist (struct coordinate thisCoord, struct coordinate otherCoord) {
	int x  = thisCoord.x - otherCoord.x;
	int y = thisCoord.y - otherCoord.y;

	if(x < 0)
		x = -x;
	if(y < 0)
		y = -y;

	return x + y;
}

struct coordinate copy_coordinate (struct coordinate coord) {
	struct coordinate retCoord;

	retCoord.x = coord.x;
	retCoord.y = coord.y;

	return retCoord;
}
