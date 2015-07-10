#include "core/pt.h"

/*
 * Return the distance in tiles between two ships.
 * This will mostly be used in hit chance calculations.
 */
int calc_dist (const struct pt thisCoord, const struct pt otherCoord) {
	int x  = thisCoord.x - otherCoord.x;
	int y = thisCoord.y - otherCoord.y;

	if(x < 0)
		x = -x;
	if(y < 0)
		y = -y;

	return x + y;
}
