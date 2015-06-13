#ifndef WEAPON_H
#define WEAPON_H

#include "item.h" //For constants

struct weapon {
	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;
	int accuracy; //Gives flat bonus to hit chance

	double price;
};

#endif
