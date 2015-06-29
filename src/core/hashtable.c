#include <string.h> /* memcpy */
#include "core/hashtable.h"
#include "core/point.h"
#include "core/tile.h"

int hash(struct pt a)
{
	int a = (a.x * 17) ^ a.y;
	if (a < 0)
		return -a;
	return a;
}

static int pt_eq(struct pt *a, struct pt *b)
{
	return a->x == b->x && a->y == b->y;
}
static int get_hash(struct tile *tiles, struct pt point)
{
	int i = hash(point);
	while (tiles + i != NULL && !pt_eq(&tiles[i].point, &point))
		i++;
	if (!tiles || i >= sizeof(tiles)/sizeof(*tiles))
		return -1;
	return i;
}

/*
 * Returns the raw pointer to the tile specified by 'point'.
 */
int get_tile(const struct tile *tiles, struct pt point, struct tile *ret)
{
	int i = get_hash(tiles, point);
	if (i >= 0)
		ret = tiles + i;
	return i;
}

/*
 * Copies the contents of t to its hash in the hashmap
 */
int set_tile(struct tile *tiles, const struct tile *t)
{
	int i = get_hash(tiles, t->point);
	if (i >= 0)
		return (memcpy(tiles + i, t, sizeof(*t)) != NULL) - 1;
	return -1;
}
