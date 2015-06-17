#ifndef COORDINATE_H
#define COORDINATE_H

struct coordinate {
	int x;
	int y;
};

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


#endif
