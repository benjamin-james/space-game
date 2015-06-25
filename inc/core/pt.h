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

/*
 * this union may be better, but it can't have subclasses
 * because of the 'void  * sub' element.
 * But, it allows you to access the elements as if they were in an array,
 * i.e.
 * union pt point = { 2, 3 };
 * point.x += 5;
 * point.arr[1] -= 2;
 * would leave it at { 7, 1 }
 */
union pt {
	struct { int x, int y };
	int arr[2];
};

int calc_dist (struct pt thisPt, struct pt otherPt);

#endif
