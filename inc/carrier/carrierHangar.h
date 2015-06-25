#ifndef CARRIER_HANGAR_H
#define CARRIER_HANGAR_H

#define MAX_SHIPS 12 //Totally arbitrary at this point

#include "ship/ship.h"
#include "core/pt.h"

struct carrierHangar {
	struct pt coord;

	struct ship *fleet[MAX_SHIPS];

	int maxHealth;
	int currentHealth;
};

void enter_hangar (struct carrierHangar *thisHangar, struct ship thisShip);
struct ship leave_hangar (struct carrierHangar *thisHangar, short index);

#endif
