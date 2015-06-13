#include "ship.h"

/*
 * Return the distance in tiles between two ships.
 * This will mostly be used in hit chance calculations.
 */
int calc_dist (struct ship thisShip, struct ship otherShip) {
	return (thisShip.x - otherShip.x) + (thisShip.y - otherShip.y);
}

/*
 * May need tweaking.
 * Add item/weapon values into dmg value.
 */
int calc_dmg (struct ship thisShip, struct ship otherShip) {
	return thisShip.attack - otherShip.shields;
}
