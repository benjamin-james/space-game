#ifndef SHIP_H
#define SHIP_H

#define SHIP_NAME_LENGTH 12

#include "item.h"

/*
 * All the basic information and statistics on ships.
 * Also needs inventory implementation.
 */
struct ship {
	char name[SHIP_NAME_LENGTH];

	int x;
	int y;

	//The ship's inventory
	struct item engine;
	struct item weapon;
	struct item shield;
	struct item radar;

	//Sum of all system's power <= energy <= maxEnergy
	int maxEnergy;
	int energy;
	int enginePower;
	int weaponPower;
	int shieldPower;
	int radarPower;

	int health;

	int kills;
	int exp;
};

int calc_radar_range (struct ship);
int calc_attack (struct ship);
int calc_shield_strength(struct ship);
int calc_move_range (struct ship);

int calc_dist (struct ship thisShip, struct ship otherShip);
int calc_dmg (struct ship thisShip, struct ship otherShip);

#endif
