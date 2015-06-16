#include "ship.h"

/*
 * Returns the range in tiles that can be seen by this ship.
 * Needs item implementation.
 */
int calc_radar_range (struct ship thisShip) {
	return thisShip.radar.defaultStrength + (thisShip.radarPower - (thisShip.maxHealth / 4));
}

/*
 * Returns the attack power of the ship.
 * Depends upon the equipped weapon and the weapon power.
 */
int calc_attack (struct ship thisShip) {
	return thisShip.weapon.defaultStrength + (thisShip.weaponPower - (thisShip.maxHealth / 4));
}

/*
 * Returns the "health" of the shield, or the damage it can block.
 * Depends upon the equipped shield and shield power.
 */
int calc_shield_strength (struct ship thisShip) {
	return thisShip.shield.defaultStrength + (thisShip.shieldPower - (thisShip.maxHealth / 4));
}

/*
 * Returns the max move range in tiles that the ship can move in a single turn.
 * May need rebalancing.
 */
int calc_move_range (struct ship thisShip) {
	return thisShip.engine.defaultStrength + (thisShip.enginePower - (thisShip.maxHealth / 4));
}

/*
 * Calculates the experience awarded to thisShip after successfully destroying otherShip.
 */
int calc_exp (struct ship thisShip, struct ship otherShip) {
	if(otherShip.level > thisShip.level + 1)
		return 45;
	if(thisShip.level > otherShip.level + 1)
		return 3;

	return (0.105) * ((thisShip.level - otherShip.level) * 100 + thisShip.exp - otherShip.exp + 200) + 3;
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
	int avgDmg = calc_attack(thisShip) - calc_shield_strength(otherShip) / 4;
	if(avgDmg < 0)
		return 0;
	if(manualFire == 1)
		return (((double)rand() / RAND_MAX) * 0.75  * avgDmg) + avgDmg;
	else
		return avgDmg;
}

/*
 * Returns the percentage chance of thisShip hitting otherShip.
 * Depends on the distance and the engine power of the otherShip.
 * All the numbers may need to be tweaked. They are currently balanced around:
 * Manual: distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.65
 *         y - 1.0 = (-0.035)(x - 1)
 * Auto:   distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.85
 *         y - 1.0 = (-0.015)(x - 1)
 */
double calc_hit_chance (struct ship thisShip, struct ship otherShip, short manualFire) {
	if(manualFire == 1)
		return (-0.035 * calc_dist(thisShip, otherShip) + 1.035)
			- (0.05 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * thisShip.weapon.accuracy);
	else
		return (-0.015 * calc_dist(thisShip, otherShip) + 1.015)
			- (0.025 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * thisShip.weapon.accuracy);
}

/*
 * Checks to see if total allocated power > currentHealth.
 * If so, lessens the power of the highest powered system.
 * If there is a tie, it reduces power in: weapon -> radar -> engine -> shield.
 * Ends when allocated power <= currentHealth.
 */
void realloc_energy (struct ship *thisShip) {
	while(thisShip->enginePower + thisShip->weaponPower + thisShip->shieldPower
		+ thisShip->radarPower > thisShip->currentHealth) {
		short maxType = 0; //Used to hold which will system will be cut
		short max = thisShip->shieldPower; //Used to hold the max power

		if(thisShip->enginePower >= max) {
			maxType = 1;
			max = thisShip->enginePower;
		}

		if(thisShip->radarPower >= max) {
			maxType = 2;
			max = thisShip->radarPower;
		}

		if(thisShip->weaponPower >= max) {
			maxType = 3;
		}

		switch(maxType) {
		case 0:
			thisShip->shieldPower--;
			break;
		case 1:
			thisShip->enginePower--;
			break;
		case 2:
			thisShip->radarPower--;
			break;
		case 3:
			thisShip->weaponPower--;
			break;
		}
	}
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
		otherShip->currentHealth += otherShip->shield.currentStrength;
		otherShip->shield.currentStrength = 0;

		if(otherShip->currentHealth < 0)
			otherShip->currentHealth = 0;

		realloc_energy(otherShip);
	}

	thisShip->kills++;
	thisShip->exp += calc_exp(*thisShip, *otherShip);

	if(thisShip->exp >= 100) {
		thisShip->exp -= 100;
		thisShip->level++;
	}

	return otherShip->currentHealth;
}
