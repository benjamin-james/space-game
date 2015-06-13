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
	int x = thisShip.x - otherShip.x;
	int y = thisShip.y - otherShip.y;

	if(x < 0)
		x = -x;
	if(y < 0)
		y = -y;

	return x + y;
}

/*
 * Return the damage inflicted upon the other ship.
 * Does not actually deal the damage.
 * May need rebalancing.
 */
int calc_dmg (struct ship thisShip, struct ship otherShip, short manualFire) {
	int avgDmg = calc_attack(thisShip) - calc_shield_strength(otherShip);
	if(avgDmg < 0)
		return 0;
	if(manualFire == 1)
		return (rand() * 0.4 * avgDmg) + (0.85 * avgDmg);
	else
		return calc_attack(thisShip) - calc_shield_strength(otherShip);
}

/*
 * Returns the percentage chance of thisShip hitting otherShip.
 * Depends on the distance and the engine power of the otherShip.
 * All the numbers may need to be tweaked. They are currently balanced around:
 * Manual: distance = 1 : chance = 1.0 :: distance = 10 : chance = 0.25
 * Auto:   distance = 1 : chance = 1.0 :: distance = 10 : chance = 0.75
 */
double calc_hit_chance (struct ship thisShip, struct ship otherShip, short manualFire) {
	if(manualFire == 1)
		return (-0.083 * calc_dist(thisShip, otherShip) + 1.083) - (0.05 * (otherShip.enginePower - (otherShip.maxEnergy / 4))) + (0.025 * thisShip.weapon.accuracy);
	else
		return (-0.028 * calc_dist(thisShip, otherShip) + 1.028) - (0.025 * (otherShip.enginePower - (otherShip.maxEnergy / 4))) + (0.025 * thisShip.weapon.accuracy);
}

/*
 * Takes two ship structs, calculates and deals damage from thisShip to otherShip, and returns resulting ship health.
 * Will not return negative numbers as health.
 * Returns -1 if a miss.
 */
int handle_attack (struct ship *thisShip, struct ship *otherShip, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance(*thisShip, *otherShip, manualFire)) //If miss
		return -1;

	otherShip->shield.currentStrength -= calc_dmg(*thisShip, *otherShip, manualFire);

	if(otherShip->shield.currentStrength < 0) {
		otherShip->health += otherShip->shield.currentStrength;
		otherShip->shield.currentStrength = 0;

		if(otherShip->health < 0)
			otherShip->health = 0;
	}

	return otherShip->health;
}
