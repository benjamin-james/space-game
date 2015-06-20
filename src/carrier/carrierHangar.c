#include "carrier/carrierHangar.h"

/*
 * Passes a ship struct to be "stored" in the hangar's array.
 * Creates a copy of the ship in the array.
 */
void enter_hangar (struct carrierHangar *thisHangar, struct ship thisShip) {
	short index = -1;
	while(thisHangar->fleet[++index] == NULL);

	struct ship holder;
	holder = copy_ship(thisShip);
	thisHangar->fleet[index] = &holder;
}

/*
 * Removes the ship at the given index and returns it.
 */
struct ship leave_hangar (struct carrierHangar *thisHangar, short index) {
	struct ship retShip = copy_ship(*thisHangar->fleet[index]);
	thisHangar->fleet[index] = NULL;
	return retShip;
}
