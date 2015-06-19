#ifndef ENTITY_H
#define ENTITY_H

#include "stdint.h"

/*
 * Object superclass that the game engine handles.
 * data -> the subclass data
 * id -> the hashed id, should be able to deduce subclass type (bitmask?)
 * todo: make a hashing function to do that ^
 */
struct sc { /*stands for superclass */
	void *data;
	int id;
};

/*
 * Some elements should be a pointer so that they can be overridden
 */
struct entity {
	struct sc super;
	struct coordinate *coord;
	char name[MAX_NAME_LEN];
};

#endif
