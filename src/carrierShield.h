#ifndef CARRIER_SHIELD_H
#define CARRIER_SHIELD_H

#include "coordinate.h"
#include "shipItem.h" //For constants

struct carrierShield {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	double price;
};

#endif
