#ifndef SHIP_H
#define SHIP_H

#define NAME_LENGTH 12

/*
 * All the basic information and statistics on ships.
 * Also needs inventory implementation.
 */
struct ship {
	char[NAME_LENGTH] name;

	int x;
	int y;

	int energy;

	int enginePower;
	int weaponPower;
	int shieldPower;
	int radarPower;

	int health;
	int shield;
	int attack;

	int kills;
	int exp;
};

int calc_dist (struct ship thisShip, struct ship otherShip);
int calc_dmg (struct ship thisShip, struct ship otherShip);

#endif
