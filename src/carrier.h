#ifndef CARRIER_H
#define CARRIER_H

#define CARRIER_NAME_LENGTH 12

#include "ship.h"
#include "carrierEngine.h"
#include "carrierShield.h"
#include "carrierArtillery.h"
#include "carrierTurret.h"
#include "carrierHangar.h"

struct carrier {
	//Coordinates for the center of the ship. All other subsystem coordinates will be set relative to these
	struct coordinate coord;

	char name[CARRIER_NAME_LENGTH];

	int maxHealth;
	int currentHealth;

	int maxHangarHealth;
	int currentHangarHealth;

	//The carrier's inventory
	struct carrierEngine engine;
	struct carrierArtillery artillery;
	struct carrierTurret turret;
	struct carrierShield shield;
};

int calc_attack_artillery (struct carrierArtillery artillery);
int calc_attack_turret (struct carrierTurret turret);

int calc_dmg_artillery_to_ship (struct carrierArtillery artillery, struct ship otherShip);
int calc_dmg_turret_to_ship (struct carrierTurret turret, struct ship otherShip);
int calc_dmg_artillery_to_carrier (struct carrierArtillery artillery, struct carrier otherCarrier);

double calc_hit_chance_artillery_to_ship (struct carrierArtillery artillery, struct ship otherShip);
double calc_hit_chance_turret_to_ship (struct carrierTurret turret, struct ship otherShip);
double calc_hit_chance_artillery_to_carrier (struct carrierArtillery artillery, struct carrier otherCarrier);

int handle_attack_artillery_to_ship (struct carrierArtillery artillery, struct ship *otherShip);
int handle_attack_turret_to_ship (struct carrierTurret turret, struct ship *otherShip);
int handle_attack_artillery_to_carrier (struct carrierArtillery artillery, struct carrier *otherCarrier);

#endif
