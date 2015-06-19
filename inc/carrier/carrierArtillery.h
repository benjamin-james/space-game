#ifndef CARRIER_ARTILLERY_H
#define CARRIER_ARTILLERY_H

#include "core/coordinate.h"
#include "ship/shipItem.h" //For constants

struct carrierArtillery {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	int accuracy;
	int strength;
	short manualFire;

	double price;
};

struct carrierArtillery copy_carrier_artillery (struct carrierArtillery artillery) {
	struct carrierArtillery retArtillery;

	retArtillery.coord = copy_coordinate (artillery.coord);

	for(short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retArtillery.name[ct] = artillery.name[ct];
	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retArtillery.description[ct] = artillery.description[ct];

	retArtillery.maxHealth = artillery.maxHealth;
	retArtillery.currentHealth = artillery.currentHealth;

	retArtillery.accuracy = artillery.accuracy;
	retArtillery.strength = artillery.strength;
	retArtillery.manualFire = artillery.manualFire;

	retArtillery.price = artillery.price;

	return retArtillery;
}

#endif
