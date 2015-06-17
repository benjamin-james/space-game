#ifndef SHIP_WEAPON_H
#define SHIP_WEAPON_H

#include "shipItem.h" //For constants

struct shipWeapon {
	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;
	int accuracy; //Gives flat bonus to hit chance

	double price;
};

#endif
