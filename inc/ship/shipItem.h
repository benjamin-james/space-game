#ifndef SHIP_ITEM_H
#define SHIP_ITEM_H

#define ITEM_NAME_LENGTH 12
#define ITEM_DESCRIPTION_LENGTH 50

struct shipItem {
	char name[ITEM_NAME_LENGTH];
	char description[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;

	double price;
};

#endif
