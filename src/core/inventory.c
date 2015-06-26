#include "core/inventory.h"

/*
 * Adds a pointer to the given item to the first available NULL slot.
 * Returns the index the item was added to.
 * Returns -1 if failed.
 */
int add_item (struct inventory *inventory, struct buyable item) {
    int i = 0;
    while(inventory->inv[i] != NULL && i < INVENTORY_SIZE)
	i++;

    if(i >= INVENTORY_SIZE)
	return -1;

    inventory->inv[i] = &item;

    return i;
}

/*
 * Removes the item at the given index from the inventory.
 * Returns the item it removed or NULL if the index was empty;
 */
struct buyable remove_item (struct inventory *inventory, int index) {
    if(inventory->inv[index] == NULL)
	return NULL;

    struct buyable retVal = *inventory->inv[index];
    inventory->inv[index] = NULL;

    return retVal;
}
