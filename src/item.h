#ifndef ITEM_H
#define ITEM_H

#define ITEM_NAME_LENGTH 12
#define ITEM_DESCRIPTION_LENGTH 50

struct item {
	char name[ITEM_NAME_LENGTH];
	char descritption[ITEM_DESCRIPTION_LENGTH];

	int defaultStrength;

	double price;
};

#endif
