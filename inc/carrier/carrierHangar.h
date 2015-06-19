#ifndef CARRIER_HANGAR_H
#define CARRIER_HANGAR_H

#define MAX_SHIPS 12 //Totally arbitrary at this point

#include "core/coordinate.h"
#include "ship/ship.h"

struct carrierHangar {
	struct coordinate coord;

	struct ship *fleet[MAX_SHIPS];

	int maxHealth;
	int currentHealth;
};

struct carrierHangar copy_carrier_hangar(struct carrierHangar hangar);

void enter_hangar (struct carrierHangar *thisHangar, struct ship thisShip);
struct ship leave_hangar (struct carrierHangar *thisHangar, short index);

#endif
