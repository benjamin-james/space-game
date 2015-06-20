#include "carrier/carrier.h"

/*
 * Returns the base attack damage from the ship's artillery.
 */
int calc_attack_artillery (struct carrierArtillery artillery) {
	return artillery.strength * (artillery.super.currentHealth / artillery.super.maxHealth);
}

/*
 * Returns the base attack damage from the ship's turret.
 */
int calc_attack_turret (struct carrierTurret turret) {
	return turret.strength * (turret.super.currentHealth / turret.super.maxHealth);
}

/*
 * Returns the damage dealt by the carrier's artillery on a ship but doesn't actually deal damage.
 */
int calc_dmg_artillery_to_ship (struct carrierArtillery artillery, struct ship otherShip) {
	if(artillery.manualFire == 1)
		return (((double)rand() / RAND_MAX) * 0.65  + 1) + calc_attack_artillery(artillery);
	else
		return calc_attack_artillery(artillery);
}

/*
 * Returns the damage dealt by the carrier's turret on a ship but doesn't actually deal damage.
 */
int calc_dmg_turret_to_ship (struct carrierTurret turret, struct ship otherShip) {
	int avgDmg = calc_attack_turret(turret) - calc_shield_strength(otherShip) / 2;
	if(avgDmg < 0)
		return 0;
	if(turret.manualFire == 1)
		return (((double)rand() / RAND_MAX) * 0.65  * avgDmg) + avgDmg;
	else
		return avgDmg;
}

/*
 * Returns the damage dealt by the carrier's artillery against the opposing carrier but doesn't actually deal damage.
 */
int calc_dmg_artillery_to_carrier (struct carrierArtillery artillery, struct carrier otherCarrier) {
	if(otherCarrier.shield.currentHealth > 0)
		return 0;
	if(artillery.manualFire == 1)
		return (((double)rand() / RAND_MAX) * 0.65  + 1) * calc_attack_artillery(artillery);
	else
		return calc_attack_artillery(artillery);
}

/*
 * Returns the percentage chance of artillery hitting otherShip.
 * Depends on the artillery's accuracy, distance, and otherShip's engine power.
 * Currently balanced around:
 * Manual: distance = 1 : chance = 0.75 :: distance = 11 : chance = 0.25
 *         y - 0.75 = (-0.050)(x - 1)
 * Auto:   distance = 1 : chance = 0.85 :: distance = 11 : chance = 0.50
 *         y - 0.85 = (-0.035)(x - 1)
 */
double calc_hit_chance_artillery_to_ship (struct carrierArtillery artillery, struct ship otherShip) {
	if(artillery.manualFire == 1)
		return (-0.050 * calc_dist(artillery.super.coord, otherShip.coord) + 1.050)
			- (0.200 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * artillery.accuracy);
	else
		return (-0.035 * calc_dist(artillery.super.coord, otherShip.coord) + 1.035)
			- (0.150 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * artillery.accuracy);
}

/*
 * Returns the percentage chance of the turret hitting otherShip.
 * Depends on the turret's accuracy, distance, and otherShip's engine power.
 * Currently balanced around:
 * Manual: distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.75
 *         y - 1.0 = (-0.025)(x - 1)
 * Auto:   distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.85
 *         y - 1.0 = (-0.015)(x - 1)
 */
double calc_hit_chance_turret_to_ship (struct carrierTurret turret, struct ship otherShip) {
	if(turret.manualFire == 1)
		return (-0.025 * calc_dist(turret.super.coord, otherShip.coord) + 1.025)
			- (0.025 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * turret.accuracy);
	else
		return (-0.015 * calc_dist(turret.super.coord, otherShip.coord) + 1.015)
			- (0.010 * (otherShip.enginePower - (otherShip.maxHealth / 4)))
			+ (0.025 * turret.accuracy);
}

/*
 * Returns the percentage chance of the artillery hitting otherCarrier.
 * Depends on the artillery's accuracy and distance.
 * Currently balanced around:
 * Manual: distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.95
 *         y - 1.0 = (-0.005)(x - 1)
 * Auto:   distance = 1 : chance = 1.0 :: distance = 11 : chance = 0.98
 *         y - 1.0 = (-0.002)(x - 1)
 */
double calc_hit_chance_artillery_to_carrier (struct carrierArtillery artillery, struct carrier otherCarrier) {
	if(artillery.manualFire == 1)
		return (-0.005 * calc_dist(artillery.super.coord, otherCarrier.coord) + 1.005)
			+ (0.025 * artillery.accuracy);
	else
		return (-0.002 * calc_dist(artillery.super.coord, otherCarrier.coord) + 1.002)
			+ (0.025 * artillery.accuracy);
}

/*
 * Takes an artillery struct and a ship struct and deals damage from the artillery to the ship and returns the resulting ship health.
 * Will not return negative numbers as health.
 * Returns a -1 if miss.
 */
int handle_attack_artillery_to_ship (struct carrierArtillery artillery, struct ship *otherShip) {
	if((double)rand() / RAND_MAX > calc_hit_chance_artillery_to_ship(artillery, *otherShip)) //If miss
		return -1;

	otherShip->shield.currentStrength -= calc_dmg_artillery_to_ship(artillery, *otherShip);

	if(otherShip->shield.currentStrength < 0) {
				otherShip->currentHealth += otherShip->shield.currentStrength;
		otherShip->shield.currentStrength = 0;

		if(otherShip->currentHealth < 0)
			otherShip->currentHealth = 0;

		realloc_energy(otherShip);
	}

	return otherShip->currentHealth;
}

/*
 * Takes a turret struct and a ship struct and deals damage from turret to otherShip and returns the resulting ship health.
 * Will not return negative numbers as health.
 * Returns -1 if miss.
 */
int handle_attack_turret_to_ship (struct carrierTurret turret, struct ship *otherShip) {
	if((double)rand() / RAND_MAX > calc_hit_chance_turret_to_ship(turret, *otherShip)) //If miss
		return -1;

	otherShip->shield.currentStrength -= calc_dmg_turret_to_ship(turret, *otherShip);

	if(otherShip->shield.currentStrength < 0) {
				otherShip->currentHealth += otherShip->shield.currentStrength;
		otherShip->shield.currentStrength = 0;

		if(otherShip->currentHealth < 0)
			otherShip->currentHealth = 0;

		realloc_energy(otherShip);
	}

	return otherShip->currentHealth;
}

/*
 * Takes an artillery struct and a carrier struct, deals damage from the artillery struct to the carrier struct, and returns the resulting carrier health.
 * Will not return a negative number as health.
 * Returns a -1 if miss.
 */
int handle_attack_artillery_to_carrier (struct carrierArtillery artillery, struct carrier *otherCarrier) {
	if((double)rand() / RAND_MAX > calc_hit_chance_artillery_to_carrier(artillery, *otherCarrier)) //If miss
		return -1;

	otherCarrier->currentHealth -= calc_dmg_artillery_to_carrier(artillery, *otherCarrier);

	if(otherCarrier->currentHealth < 0)
		otherCarrier->currentHealth = 0;

	return otherCarrier->currentHealth;
}
