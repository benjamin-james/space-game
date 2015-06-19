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

struct shipShield copy_ship_shield (struct shipShield shield) {
	struct shipShield retShield;

	for(short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retShield.name[ct] = shield.name[ct];

	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retShield.description[ct] = retShield.description[ct];

	retShield.defaultStrength = shield.defaultStrength;
	retShield.currentStrength = shield.currentStrength;

	retShield.price = shield.price;

	return retShield;
}

#endif
