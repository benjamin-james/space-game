#ifndef CARRIER_ITEM
#define CARRIER_ITEM

#include "core/coordinate.h"
#include "core/buyable.h"

struct carrierItem {
	struct coordinate coord;

	struct buyable super;

	int maxHealth;
	int currentHealth;
};

#endif
