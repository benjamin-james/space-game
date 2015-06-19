#ifndef COORDINATE_H
#define COORDINATE_H

/*
 * Note: Can we change this to
 * be a shorter name like 'struct pt'
 * or 'struct vec2'?
 */
struct coordinate {
	int x;
	int y;
};

int calc_dist (struct coordinate thisCoord, struct coordinate otherCoord);

struct coordinate copy_coordinate (struct coordinate coord);

#endif
