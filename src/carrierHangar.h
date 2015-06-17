#ifndef CARRIER_HANGAR_H
#define CARRIER_HANGAR_H

#define MAX_SHIPS 12 //Totally arbitrary at this point

#include "coordinate.h"
#include "ship.h"

struct carrierHangar {
	struct coordinate coord;

	struct ship[MAX_SHIPS] fleet;

	int maxHealth;
	int currentHealth;
};

void enter_hangar (struct carrierHangar *thisHangar, struct ship *thisShip);
ship leave_hangar (struct *thisHangar, short index);

#endif
