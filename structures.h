/*
 * structures.h
 *
 *  Created on: 22 févr. 2024
 *      Author: matth
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

// Créer les structures pour move, supemon et inventory
typedef struct {
	char name[32];
	char type[3];
	short value;
} move;

typedef struct {
	char name[32];
	short level, exp;
	short hp, maxHp;
	short att, baseAtt;
	short def, baseDef;
	short eva, baseEva;
	short acc, baseAcc;
	short speed;
	move moves[2];
} supemon;

typedef struct {
	short potion;
	short super_potion;
	short rare_candy;
} inventory;

void levelUpSupemon(supemon *ptSupemon);

#endif /* STRUCTURES_H_ */
