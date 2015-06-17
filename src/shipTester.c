#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ship.c"

int main(int argc, char **argv) {
	srand(time(NULL));

	struct ship alpha;
	struct ship beta;

	alpha.x = 0;
	alpha.y = 0;

	alpha.engine.defaultStrength = 5;

	alpha.weapon.defaultStrength = 4;
	alpha.weapon.accuracy = 4;

	alpha.shield.defaultStrength = 2;
	alpha.shield.currentStrength = 2;

	alpha.enginePower = 3;
	alpha.weaponPower = 5;
	alpha.radarPower = 3;
	alpha.shieldPower = 5;

	alpha.currentHealth = 10;

	beta.x = 5;
	beta.y = 5;

	beta.engine.defaultStrength = 5;

	beta.weapon.defaultStrength = 3;
	beta.weapon.accuracy = 4;

	beta.shield.defaultStrength = 5;
	beta.shield.currentStrength = 5;

	beta.enginePower = 3;
	beta.weaponPower = 5;
	beta.radarPower = 3;
	beta.shieldPower = 5;

	beta.maxHealth = 16;
	beta.currentHealth = 16;

	/*short ct = 0;
	printf("After %d attacks:\n----------\ncurrentHealth: %d\nenginePower: %d\nweaponPower: %d\nradarPower: %d\nshieldPower: %d\n----------\n\n", ct, beta.currentHealth, beta.enginePower, beta.weaponPower, beta.radarPower, beta.shieldPower);

	while(beta.currentHealth > 0) {
		ct++;
		if(handle_attack(&alpha, &beta, 1) == -1)
			printf("Miss!\n");
		//printf("After %d attacks, beta's shields are at %d and beta's currentHealth is at %d\n", ct, beta.shield.currentStrength, beta.currentHealth);
		printf("After %d attacks:\n----------\ncurrentHealth: %d\nenginePower: %d\nweaponPower: %d\nradarPower: %d\nshieldPower: %d\n----------\n\n", ct, beta.currentHealth, beta.enginePower, beta.weaponPower, beta.radarPower, beta.shieldPower);
	}

	printf("Beta is destroyed after %d attacks!\n", ct);*/

	int manualCt = 0;
	int autoCt = 0;

	for(short ct = 0; ct < 1000; ct++) {
		beta.currentHealth = beta.maxHealth;
		beta.shield.currentStrength = beta.shield.defaultStrength;
		beta.enginePower = 3;
		beta.weaponPower = 5;
		beta.radarPower = 3;
		beta.shieldPower = 5;

		while(handle_attack(&alpha, &beta, 1) != 0)
			manualCt++;

		beta.currentHealth = beta.maxHealth;
		beta.shield.currentStrength = beta.shield.defaultStrength;
		beta.enginePower = 3;
		beta.weaponPower = 5;
		beta.radarPower = 3;
		beta.shieldPower = 5;

		while(handle_attack(&alpha, &beta, 0) != 0)
			autoCt++;
	}

	printf("Over 1000 trials, auto finished on avg in %f turns,\nwhile manual finished in around %f turns.\n", autoCt / 1000.0, manualCt / 1000.0);
	return 0;
}
