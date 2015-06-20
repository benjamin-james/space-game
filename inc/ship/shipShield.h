#ifndef SHIP_SHIELD_H
#define SHIP_SHIELD_H

#include "ship/shipItem.h" //For constants

struct shipShield {
	struct shipItem super;
	int currentStrength;
};

#endif
