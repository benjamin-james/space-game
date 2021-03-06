#ifndef CARRIER_ITEM
#define CARRIER_ITEM

#include "core/pt.h"
#include "core/buyable.h"

struct carrierItem {
	struct pt coord;

	struct buyable super;
	void *sub;

	int maxHealth;
	int currentHealth;
};

#endif
