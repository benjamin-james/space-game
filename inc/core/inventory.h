#ifndef INVENTORY_H
#define INVENTORY_H

#include "core/buyable.h"

#define INVENTORY_SIZE 100

struct inventory {
    struct buyable *inv[INVENTORY_SIZE];
};

int add_item (struct inventory *inventory, struct buyable item);
struct buyable remove_item (struct inventory *inventory, int index);

#endif
