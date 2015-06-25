
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int safe_hash(int a, int b)
{
	int x = (a >= 0) ? 2 * a : -2 * a - 1;
	int y = (b >= 0) ? 2 * b : -2 * b - 1;
	int z = (a >= b) ? x * x + x + y : x + y * y;
	return z / 2;
}

int xor_hash(int a, int b)
{
	a = a ^ b;
	if (a < 0)
		return -a;
	return a;
}

#define P 17 /* has to be a prime and/or odd number close to a power of 2 */
int biased_hash(int a, int b)
{
	a = (a * P) ^ b;
	if (a < 0)
		return -a;
	return a;
}
#undef P

int main(void)
{
	srand(time(0));
	int i, a, b;
	for (i = 0; i < 20; i++) {
		a = rand() % 200;
		b = rand() % 200;
		printf("a=%d b=%d safe=%d xor=%d biased=%d\n", a, b, safe_hash(a, b), xor_hash(a, b), biased_hash(a, b));
	}
	return 0;
}
