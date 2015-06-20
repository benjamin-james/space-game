#ifndef CARRIER_ENGINE_H
#define CARRIER_ENGINE_H

#include "core/coordinate.h"
#include "carrier/carrierItem.h"

struct carrierEngine {
	struct carrierItem super;

	int startChargeTime;
	int currentChargeTime;
};

#endif
