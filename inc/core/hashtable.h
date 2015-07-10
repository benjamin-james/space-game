#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "core/tile.h"

int hash(struct pt a);

int get_tile(const struct tile *tiles, struct pt point, struct tile *ret);

int set_tile(struct tile *tiles, const struct tile *t);
#endif
