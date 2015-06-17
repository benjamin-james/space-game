#ifndef CARRIER_ARTILLERY_H
#define CARRIER_ARTILLERY_H

#include "coordinate.h"
#include "shipItem.h" //For constants

struct carrierArtillery {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	int accuracy;

	double price;
};

#endif
