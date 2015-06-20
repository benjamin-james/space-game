#ifndef CARRIER_ARTILLERY_H
#define CARRIER_ARTILLERY_H

#include "core/coordinate.h"
#include "carrier/carrierItem.h"

struct carrierArtillery {
	struct carrierItem super;

	int accuracy;
	int strength;
	short manualFire;
};

#endif
