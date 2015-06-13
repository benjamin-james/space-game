#include "ship.h"

/*
 * Returns the range in tiles that can be seen by this ship.
 * Needs item implementation.
 */
int calc_radar_range (struct ship thisShip) {
	return thisShip.radar.defaultStrength + (thisShip.radarPower - (thisShip.maxEnergy / 4));
}

/*
 * Returns the attack power of the ship.
 * Depends upon the equipped weapon and the weapon power.
 */
int calc_attack (struct ship thisShip) {
	return thisShip.weapon.defaultStrength + (thisShip.weaponPower - (thisShip.maxEnergy / 4));
}

/*
 * Returns the "health" of the shield, or the damage it can block.
 * Depends upon the equipped shield and shield power.
 */
int calc_shield_strength (struct ship thisShip) {
	return thisShip.shield.defaultStrength + (thisShip.shieldPower - (thisShip.maxEnergy / 4));
}

/*
 * Returns the max move range in tiles that the ship can move in a single turn.
 * May need rebalancing.
 */
int calc_move_range(struct ship thisShip) {
	return thisShip.engine.defaultStrength + (thisShip.enginePower - (thisShip.maxEnergy / 4));
}

/*
 * Return the distance in tiles between two ships.
 * This will mostly be used in hit chance calculations.
 */
int calc_dist (struct ship thisShip, struct ship otherShip) {
	return (thisShip.x - otherShip.x) + (thisShip.y - otherShip.y);
}

/*
 * Return the damage inflicted upon the other ship.
 * Does not actually deal the damage.
 * May need rebalancing.
 */
int calc_dmg (struct ship thisShip, struct ship otherShip) {
	return calc_attack(thisShip) - calc_shield_strength(otherShip);
}
