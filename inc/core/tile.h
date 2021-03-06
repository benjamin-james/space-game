#ifndef TILE_H
#define TILE_H

#include "core/pt.h"
#include "ship/ship.h"
#include "carrier/carrier.h"

#define SHIP_TYPE 1
#define CARRIER_TYPE 2

struct tile {
	struct pt point;
	int type;
	struct ship *ship;
	struct carrier *carrier;
};

void init_tile(struct tile *tile, int x, int y);
#endif
