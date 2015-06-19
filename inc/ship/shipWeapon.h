#ifndef SHIP_WEAPON_H
#define SHIP_WEAPON_H

#include "ship/shipItem.h" //For constants

struct shipWeapon {
	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;
	int accuracy; //Gives flat bonus to hit chance

	double price;
};

struct shipWeapon copy_ship_weapon (struct shipWeapon weapon) {
	struct shipWeapon retWeapon;

	for (short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retWeapon.name[ct] = weapon.name[ct];
	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retWeapon.description[ct] = weapon.description[ct];

	retWeapon.defaultStrength = weapon.defaultStrength;
	retWeapon.accuracy = weapon.accuracy;

	retWeapon.price = weapon.price;

	return retWeapon;
}

#endif
