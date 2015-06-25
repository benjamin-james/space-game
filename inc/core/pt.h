#ifndef PT_H
#define PT_H

/*
 * Note: Can we change this to
 * be a shorter name like 'struct pt'
 * or 'struct vec2'?
 */
struct pt {
	int x;
	int y;

	void *sub;
};

int calc_dist (struct pt thisPt, struct pt otherPt);

#endif
