#ifndef CARRIER_TURRET_H
#define CARRIER_TURRET_H

#include "carrier/carrierItem.h"

struct carrierTurret {
	struct carrierItem super;

	int range;
	int strength;
	int accuracy;
	short manualFire;
};

#endif
