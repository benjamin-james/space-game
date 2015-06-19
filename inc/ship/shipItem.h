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

struct shipItem copy_ship_item(struct shipItem item) {
	struct shipItem retItem;

	for(short ct = 0; ct < ITEM_NAME_LENGTH; ct++)
		retItem.name[ct] = item.name[ct];

	for(short ct = 0; ct < ITEM_DESCRIPTION_LENGTH; ct++)
		retItem.description[ct] = item.description[ct];

	retItem.defaultStrength = item.defaultStrength;

	retItem.price = item.price;

	return retItem;
}

#endif
