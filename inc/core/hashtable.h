#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "core/tile.h"

int hash(struct pt a);

int get_tile(struct tile *tiles, size_t num_tiles, struct pt point, struct tile *ret);

int set_tile(struct tile *tiles, size_t num_tiles, struct tile *t);
#endif
