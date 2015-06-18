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
int calc_attack_ship (struct ship thisShip) {
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
 * Checks to see if total allocated power > currentHealth.
 * If so, lessens the power of the lowest powered system.
 * If there is a tie, it reduces power in: weapon -> radar -> engine -> shield.
 * Ends when allocated power <= currentHealth.
 */
void realloc_energy (struct ship *thisShip) {
	while(thisShip->enginePower + thisShip->weaponPower + thisShip->shieldPower
		+ thisShip->radarPower > thisShip->currentHealth) {
		short minType = -1; //Used to hold which will system will be cut
		short min = 1000; //Used to hold the min power

		if(thisShip->shieldPower <= min && thisShip->shieldPower != 0) {
			minType = 0;
			min = thisShip->shieldPower;
		}
		if(thisShip->enginePower <= min && thisShip->enginePower != 0) {
			minType = 1;
			min = thisShip->enginePower;
		}

		if(thisShip->radarPower <= min && thisShip->radarPower != 0) {
			minType = 2;
			min = thisShip->radarPower;
		}

		if(thisShip->weaponPower <= min && thisShip->weaponPower != 0) {
			minType = 3;
		}

		switch(minType) {
		case -1:
			break;
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
 * Return the damage inflicted upon the other ship.
 * Does not actually deal the damage.
 * May need rebalancing.
 */
int calc_dmg_vs_ship (struct ship thisShip, struct ship otherShip, short manualFire) {
	int avgDmg = calc_attack_ship(thisShip) - calc_shield_strength(otherShip);
	if(avgDmg < 0)
		return 0;
	if(manualFire == 1)
		return (((double)rand() / RAND_MAX) * 0.65  * avgDmg) + avgDmg;
	else
		return avgDmg;
}

/*
 * Return the damage inflicted upon the carrier subsystem.
 * Does not actually deal the damage.
 */
int calc_dmg_vs_carrier (struct ship thisShip, short manualFire) {
	if(manualFire == 1)
		return (((double)rand() / RAND_MAX) * 0.65 + 1) * calc_attack_ship(thisShip) / 1.5;
	else
		return calc_attack_ship(thisShip) / 1.5;
}

/*
 * Returns the percentage chance of thisShip hitting otherShip.
 * Depends on the distance and the engine power of the otherShip as well as thisShip's weapon accuracy.
 * All the numbers may need to be tweaked. They are currently balanced around:
 * Manual: distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.65
 *         y - 1.0 = (-0.035)(x - 1)
 * Auto:   distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.85
 *         y - 1.0 = (-0.015)(x - 1)
 */
double calc_hit_chance_vs_ship (struct ship thisShip, struct ship otherShip, short manualFire) {
	if(manualFire == 1)
		return (-0.035 * calc_dist(thisShip.coord, otherShip.coord) + 1.035)
			- (0.05 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * thisShip.weapon.accuracy);
	else
		return (-0.015 * calc_dist(thisShip.coord, otherShip.coord) + 1.015)
			- (0.025 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * thisShip.weapon.accuracy);
}

/*
 * Returns the percentage chance of thisShip hitting a carrier subsystem at coord.
 * Depends on the distance away from the target.
 * Currently balanced around:
 * Manual: distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.75
 *         y - 1.0 = (-0.025)(x - 1)
 * Auto:   distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.90
 *         y - 1.0 = (-0.010)(x - 1)
 */
double calc_hit_chance_vs_carrier (struct ship thisShip, struct coordinate coord, short manualFire) {
	if(manualFire == 1)
		return (-0.025 * calc_dist(thisShip.coord, coord) + 1.025)
			+ (0.025 * thisShip.weapon.accuracy);
	else
		return (-0.010 * calc_dist(thisShip.coord, coord) + 1.010)
			+ (0.025 * thisShip.weapon.accuracy);
}

/*
 * Takes two ship structs, calculates and deals damage from thisShip to otherShip, and returns resulting ship health.
 * Will not return negative numbers as health.
 * Returns -1 if a miss.
 */
int attack_ship (struct ship *thisShip, struct ship *otherShip, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_ship(*thisShip, *otherShip, manualFire)) //If miss
		return -1;

	otherShip->shield.currentStrength -= calc_dmg_vs_ship(*thisShip, *otherShip, manualFire);

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

/*
 * Takes a ship struct and a carrier struct and deals damage from thisShip to otherCarrier and returns the resulting carrier health.
 * Will not return negative numbers as health.
 * Returns a -1 if a miss.
 */
int attack_carrier (struct ship *thisShip, struct carrier *otherCarrier, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_carrier(*thisShip, otherCarrier->coord, manualFire)) //If miss
		return -1;

	otherCarrier->currentHealth -= calc_dmg_vs_carrier(*thisShip, manualFire);

	if(otherCarrier->currentHealth < 0) {
		otherCarrier->currentHealth = 0;

		thisShip->kills++;
		thisShip->exp += 50;

		if(thisShip->exp >= 100) {
			thisShip->exp -= 100;
			thisShip->level++;
		}
	}

	return otherCarrier->currentHealth;
}

/*
 * Takes a ship struct and an engine struct and deals damage from thisShip to otherEngine and returns the resulting engine health.
 * Will not return negative numbers as health.
 * Returns a -1 if a miss.
 */
int attack_engine (struct ship *thisShip, struct carrierEngine *otherEngine, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_carrier(*thisShip, otherEngine->coord, manualFire)) //If miss
		return -1;

	otherEngine->currentHealth -= calc_dmg_vs_carrier(*thisShip, manualFire);

	if(otherEngine->currentHealth < 0) {
		otherEngine->currentHealth = 0;

		thisShip->kills++;
		thisShip->exp += 50;

		if(thisShip->exp >= 100) {
			thisShip->exp -= 100;
			thisShip->level++;
		}
	}

	return otherEngine->currentHealth;
}

/*
 * Takes a ship struct and a shield struct and deals damage from thisShip to otherShield and returns the resulting shield health.
 * Will not return negative numbers as health.
 * Returns a -1 if a miss.
 */
int attack_shield (struct ship *thisShip, struct carrierShield *otherShield, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_carrier(*thisShip, otherShield->coord, manualFire)) //If miss
		return -1;

	otherShield->currentHealth -= calc_dmg_vs_carrier(*thisShip, manualFire);

	if(otherShield->currentHealth < 0) {
		otherShield->currentHealth = 0;

		thisShip->kills++;
		thisShip->exp += 50;

		if(thisShip->exp >= 100) {
			thisShip->exp -= 100;
			thisShip->level++;
		}
	}

	return otherShield->currentHealth;
}

/*
 * Takes a ship struct and an artillery struct and deals damage from thisShip to otherArtillery and returns the resulting artillery health.
 * Will not return negative numbers as health.
 * Returns a -1 if a miss.
 */
int attack_artillery (struct ship *thisShip, struct carrierArtillery *otherArtillery, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_carrier(*thisShip, otherArtillery->coord, manualFire)) //If miss
		return -1;

	otherArtillery->currentHealth -= calc_dmg_vs_carrier(*thisShip, manualFire);

	if(otherArtillery->currentHealth < 0) {
		otherArtillery->currentHealth = 0;

		thisShip->kills++;
		thisShip->exp += 50;

		if(thisShip->exp >= 100) {
			thisShip->exp -= 100;
			thisShip->level++;
		}
	}

	return otherArtillery->currentHealth;
}

/*
 * Takes a ship struct and a turret struct and deals damage from thisShip to otherTurret and returns the resulting turret health.
 * Will not return negative numbers as health.
 * Returns a -1 if a miss.
 */
int attack_turret (struct ship *thisShip, struct carrierTurret *otherTurret, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_carrier(*thisShip, otherTurret->coord, manualFire)) //If miss
		return -1;

	otherTurret->currentHealth -= calc_dmg_vs_carrier(*thisShip, manualFire);

	if(otherTurret->currentHealth < 0) {
		otherTurret->currentHealth = 0;

		thisShip->kills++;
		thisShip->exp += 50;

		if(thisShip->exp >= 100) {
			thisShip->exp -= 100;
			thisShip->level++;
		}
	}

	return otherTurret->currentHealth;
}

/*
 * Takes a ship struct and a hangar struct and deals damage from thisShip to otherHangar and returns the resulting hangar health.
 * Will not return negative numbers as health.
 * Returns a -1 if a miss.
 */
int attack_hangar (struct ship *thisShip, struct carrierHangar *otherHangar, short manualFire) {
	if((double)rand() / RAND_MAX > calc_hit_chance_vs_carrier(*thisShip, otherHangar->coord, manualFire)) //If miss
		return -1;

	otherHangar->currentHealth -= calc_dmg_vs_carrier(*thisShip, manualFire);

	if(otherHangar->currentHealth < 0) {
		otherHangar->currentHealth = 0;

		thisShip->kills++;
		thisShip->exp += 50;

		if(thisShip->exp >= 100) {
			thisShip->exp -= 100;
			thisShip->level++;
		}
	}

	return otherHangar->currentHealth;
}
