#ifndef SHIP_ITEM_H
#define SHIP_ITEM_H

#include "inc/buyable.h"

struct shipItem {
	struct buyable super;

	int defaultStrength;
};

#endif
