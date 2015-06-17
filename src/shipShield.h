#ifndef SHIP_SHIELD_H
#define SHIP_SHIELD_H

#include "shipItem.h" //For constants

struct shipShield {
	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;
	int currentStrength;

	double price;
};

#endif
