#ifndef BUYABLE_H
#define BUYABLE_H

#define NAME_LENGTH 12
#define DESCRIPTION_LENGTH 50

struct buyable {
	char name[NAME_LENGTH];
	char description[DESCRIPTION_LENGTH];

	double price;

	void *sub;
};

#endif
