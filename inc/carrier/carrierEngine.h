#ifndef CARRIER_ENGINE_H
#define CARRIER_ENGINE_H

#include "core/coordinate.h"
#include "ship/shipItem.h" //For constants

struct carrierEngine {
	struct coordinate coord;

	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int maxHealth;
	int currentHealth;

	int startChargeTime;
	int currentChargeTime;

	double price;
};

struct carrierEngine copy_carrier_engine (struct carrierEngine engine) {
	struct carrierEngine retEngine;

	retEngine.coord = copy_coordinate(engine.coord);

	for(short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retEngine.name[ct] = engine.name[ct];
	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retEngine.description[ct] = engine.description[ct];

	retEngine.maxHealth = engine.maxHealth;
	retEngine.currentHealth = engine.currentHealth;

	retEngine.startChargeTime = engine.startChargeTime;
	retEngine.currentChargeTime = engine.currentChargeTime;

	retEngine.price = engine.price;

	return retEngine;
}

#endif
