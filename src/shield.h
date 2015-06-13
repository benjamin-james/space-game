#ifndef SHIELD_H
#define SHIELD_H

#include "item.h" //For constants

struct shield {
	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;
	int currentStrength;

	double price;
};

#endif
