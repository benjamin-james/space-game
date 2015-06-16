#ifndef SHIP_H
#define SHIP_H

#define SHIP_NAME_LENGTH 12

#include <stdlib.h> //For rand()

#include "item.h"
#include "shield.h"
#include "weapon.h"

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
	struct weapon weapon;
	struct shield shield;
	struct item radar;

	//Sum of all system's power <= currentHealth <= maxHealth
	int enginePower;
	int weaponPower;
	int shieldPower;
	int radarPower;

	int maxHealth;
	int currentHealth;

	int kills;
	int level;
	int exp; //Maxes out at 100
};

int calc_radar_range (struct ship);
int calc_attack (struct ship);
int calc_shield_strength(struct ship);
int calc_move_range (struct ship);

int calc_exp (struct ship thisShip, struct ship otherShip);
int calc_dist (struct ship thisShip, struct ship otherShip);
int calc_dmg (struct ship thisShip, struct ship otherShip, short manualFire);
double calc_hit_chance (struct ship thisShip, struct ship otherShip, short manualFire);
void realloc_energy (struct ship *thisShip);
int handle_attack (struct ship *thisShip, struct ship *otherShip, short manualFire);

#endif
