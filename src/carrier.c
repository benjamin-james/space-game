#include "carrier.h"

/*
 * Returns the base attack damage from the ship's artillery.
 */
int calc_attack_artillery (struct carrierArtillery artillery) {
	return artillery.strength * (artillery.currentHealth / artillery.maxHealth);
}

/*
 * Returns the base attack damage fro the ship's turret.
 */
int calc_attack_turret (struct carrierTurret turret) {
	return turret.strength * (turret.currentHealth / turret.maxHealth);
}

/*
 * Returns the damage dealt by the carrier's artillery on a ship but doesn't actually deal damage.
 */
