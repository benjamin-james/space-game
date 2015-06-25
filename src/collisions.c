#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int count_collisions(int hash, int *data, int cur);
int test_pval(int pval, int num_runs, int len);
void test_all_pvals(int *pvals, int *collisions, int num, int num_runs, int len);

int bias_hash(int a, int b, int p);

/* all of these numbers are arbitrary*/
#define num_pvals 15
#define num_runs 500
#define num_times 10
#define length 200

int main(void)
{
	int pvals[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 33, 35, 37, 39, 41, 43};
	int i, collisions[num_pvals];
	srand(time(0));
	for (i = 0; i < num_pvals; i++)
		printf("%d\t", pvals[i]);
	puts("\n");
	for (i = 0; i < num_times; i++)
		test_all_pvals(pvals, collisions, num_pvals, num_runs, length);
	return 0;
}

#undef num_pvals
#undef num_runs
#undef num_times
#undef length

int bias_hash(int a, int b, int p)
{
	a = (p * a) ^ b;
	if (a < 0)
		return -a;
	return a;
}

int count_collisions(int hash, int *data, int cur)
{
	int i, collisions = 0;
	data[cur] = hash;
	for (i = 0; i < cur; i++) {
		if (data[i] == hash) {
			collisions++;
			data[cur] = -1;
		}
	}
	return collisions;
}
int test_pval(int pval, int num_runs, int len)
{
	int *data = malloc(sizeof(*data) * num_runs);
	int i, a, b, collisions = 0;
	for (i = 0; i < num_runs; i++) {
		a = rand() % (2 * len) - len;
		b = rand() % (2 * len) - len;
		collisions += count_collisions(bias_hash(a, b, pval), data, i);
	}
	free(data);
	return collisions;
}
void test_all_pvals(int *pvals, int *collisions, int num, int num_runs, int len) {
	int i;
	memset(collisions, 0, num);
	for (i = 0; i < num; i++) {
		collisions[i] = test_pval(i, num_runs, len);
		printf("%d\t", collisions[i]);
	}
	puts("");
}
