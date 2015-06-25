#ifndef CARRIER_H
#define CARRIER_H

#define CARRIER_NAME_LENGTH 12

#include "ship/ship.h"
#include "carrier/carrierEngine.h"
#include "carrier/carrierItem.h"
#include "carrier/carrierArtillery.h"
#include "carrier/carrierTurret.h"
#include "carrier/carrierHangar.h"

struct carrier {
	//Coordinates for the center of the ship. All other subsystem coordinates will be set relative to these
	struct pt coord;

	char name[CARRIER_NAME_LENGTH];
	int team;

	int maxHealth;
	int currentHealth;

	struct carrierHangar hangar;

	//The carrier's inventory
	struct carrierEngine engine;
	struct carrierArtillery artillery;
	struct carrierTurret turret;
	struct carrierItem shield;
};

struct carrier copy_carrier (struct carrier carrier);

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
