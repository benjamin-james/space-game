#ifndef CARRIER_TURRET_H
#define CARRIER_TURRET_H

#include "coordinate.h"
#include "shipItem.h" //For constants

struct carrierTurret {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	int range;
	int strength;
	int accuracy;
	short manualFire;

	double price;
};

struct carrierTurret copy_carrier_turret (struct carrierTurret turret) {
	struct carrierTurret retTurret;

	retTurret.coord = copy_coordinate(turret.coord);

	for(short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retTurret.name[ct] = turret.name[ct];
	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retTurret.description[ct] = turret.description[ct];

	retTurret.maxHealth = turret.maxHealth;
	retTurret.currentHealth = turret.currentHealth;

	retTurret.range = turret.range;
	retTurret.accuracy = turret.accuracy;
	retTurret.manualFire = turret.manualFire;

	retTurret.price = turret.price;

	return retTurret;
}

#endif
