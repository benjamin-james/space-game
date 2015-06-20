#ifndef CARRIER_ITEM
#define CARRIER_ITEM

#include "core/coordinate.h"
#include "ship/shipItem.h"

struct carrierItem {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	double price;
};

#endif
