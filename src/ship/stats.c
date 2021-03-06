#include "ship/stats.h"
/*
 * Add the given exp to the current total.
 * If exp reaches 100, level will increase by 1 and exp will be reset to 0.
 * Returns the level after exp is added.
 */
int addExp(struct stats *stat, int add) {
	stat->exp += add;
	if(stat->exp >= 100) {
		stat->exp -= 100;
		stat->level++;
	}

	return stat->level;
}
