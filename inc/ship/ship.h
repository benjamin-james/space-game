#ifndef SHIP_H
#define SHIP_H

#define SHIP_NAME_LENGTH 12

#include "carrier/carrier.h"
#include "core/coordinate.h"
#include "ship/shipItem.h"
#include "ship/shipShield.h"
#include "ship/shipWeapon.h"

/*
 * All the basic information and statistics on ships.
 * Also needs inventory implementation.
 */
struct ship {
	struct coordinate coord;

	char name[SHIP_NAME_LENGTH];

	//The ship's inventory
	struct shipItem engine;
	struct shipWeapon weapon;
	struct shipShield shield;
	struct shipItem radar;

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

int calc_radar_range (struct ship thisShip);
int calc_attack_ship (struct ship thisShip);
int calc_shield_strength(struct ship thisShip);
int calc_move_range (struct ship thisShip);
int calc_exp (struct ship thisShip, struct ship otherShip);
void realloc_energy (struct ship *thisShip);

int calc_dmg_vs_ship (struct ship thisShip, struct ship otherShip, short manualFire);
int calc_dmg_vs_carrier (struct ship thisShip, short manualFire);

double calc_hit_chance_vs_ship (struct ship thisShip, struct ship otherShip, short manualFire);
double calc_hit_chance_vs_carrier (struct ship thisShip, struct coordinate coord, short manualFire);

int attack_ship (struct ship *thisShip, struct ship *otherShip, short manualFire);
int attack_carrier (struct ship *thisShip, struct carrier *otherCarrier, short manualFire);
int attack_carrier_item (struct ship *thisShip, struct carrierItem *otherItem, short manualFire);

#endif
