#ifndef CARRIER_ENGINE_H
#define CARRIER_ENGINE_H

#include "coordinate.h"
#include "shipItem.h" //For constants

struct carrierEngine {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	int startChargeTime;
	int currentChargeTime;

	double price;
};

#endif
