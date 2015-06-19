#ifndef COORDINATE_H
#define COORDINATE_H

struct coordinate {
	int x;
	int y;
};

int calc_dist (struct coordinate thisCoord, struct coordinate otherCoord);

struct coordinate copy_coordinate (struct coordinate coord);

#endif
