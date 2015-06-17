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

	double price;
};

#endif
