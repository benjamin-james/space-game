#ifndef CARRIER_SHIELD_H
#define CARRIER_SHIELD_H

#include "core/coordinate.h"
#include "ship/shipItem.h" //For constants

struct carrierShield {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	double price;
};

struct carrierShield copy_carrier_shield (struct carrierShield shield) {
	struct carrierShield retShield;

	retShield.coord = copy_coordinate(shield.coord);

	for(short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retShield.name[ct] = shield.name[ct];
	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retShield.description[ct] = shield.description[ct];

	retShield.maxHealth = shield.maxHealth;
	retShield.currentHealth = shield.currentHealth;

	retShield.price = shield.price;

	return retShield;
}

#endif
