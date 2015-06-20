#ifndef SHIP_WEAPON_H
#define SHIP_WEAPON_H

#include "ship/shipItem.h" //For constants

struct shipWeapon {
	struct shipItem super;
	int accuracy; //Gives flat bonus to hit chance
};

#endif
