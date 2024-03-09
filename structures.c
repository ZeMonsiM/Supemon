#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"

void levelUpSupemon(supemon *ptSupemon) {
	// Incrémenter le niveau
	ptSupemon->level++;

	// Level up les stats basiques
	float integerPart;
	float maxHpNew = ptSupemon->maxHp * 1.3;
	if (modff(maxHpNew, &integerPart) != 0) {
		// Valeur non entière
		ptSupemon->maxHp = rand() %2 == 1 ? floorf(maxHpNew) : ceilf(maxHpNew);
	} else {
		// Valeur entière
		ptSupemon->maxHp = maxHpNew;
	}

	float baseAttNew = ptSupemon->baseAtt * 1.3;
	if (modff(baseAttNew, &integerPart) != 0) {
		ptSupemon->baseAtt = rand() %2 == 1 ? floorf(baseAttNew) : ceilf(baseAttNew);
	} else {
		ptSupemon->baseAtt = baseAttNew;
	}

	float baseDefNew = ptSupemon->baseDef * 1.3;
	if (modff(baseDefNew, &integerPart) != 0) {
		ptSupemon->baseDef = rand() %2 == 1 ? floorf(baseDefNew) : ceilf(baseDefNew);
	} else {
		ptSupemon->baseDef = baseDefNew;
	}

	float baseEvaNew = ptSupemon->baseEva * 1.3;
	if (modff(baseEvaNew, &integerPart) != 0) {
		ptSupemon->baseEva = rand() %2 == 1 ? floorf(baseEvaNew) : ceilf(baseEvaNew);
	} else {
		ptSupemon->baseEva = baseEvaNew;
	}

	float baseAccNew = ptSupemon->baseAcc * 1.3;
	if (modff(baseAccNew, &integerPart) != 0) {
		ptSupemon->baseAcc = rand() %2 == 1 ? floorf(baseAccNew) : ceilf(baseAccNew);
	} else {
		ptSupemon->baseAcc = baseAccNew;
	}

	float speedNew = ptSupemon->speed = 1.3;
	if (modff(speedNew, &integerPart) != 0) {
		ptSupemon->speed = rand() %2 == 1 ? floorf(speedNew) : ceilf(speedNew);
	} else {
		ptSupemon->speed = speedNew;
	}

	// Level up les stats des moves
	float firstMoveNew = ptSupemon->moves[0].value * 1.3;
	if (modff(firstMoveNew, &integerPart) != 0) {
		ptSupemon->moves[0].value = rand() %2 == 1 ? floorf(firstMoveNew) : ceilf(firstMoveNew);
	} else {
		ptSupemon->moves[0].value = firstMoveNew;
	}

	float secondMoveNew = ptSupemon->moves[1].value * 1.3;
	if (modff(secondMoveNew, &integerPart) != 0) {
		ptSupemon->moves[1].value = rand() %2 == 1 ? floorf(secondMoveNew) : ceilf(secondMoveNew);
	} else {
		ptSupemon->moves[1].value = secondMoveNew;
	}
}
