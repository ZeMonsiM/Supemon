/*
 * fight.h
 *
 *  Created on: 5 mars 2024
 *      Author: matth
 */

#ifndef FIGHT_H_
#define FIGHT_H_

void printSupemonStats(supemon *enemy, supemon playerSupemons[], short selectedSupemon, char playerName[32]);
short launchSelectionMenu(supemon playerSupemons[], short selectedSupemon);

short actionMove(supemon *enemy, supemon playerSupemons[], short selectedSupemon);
short actionChange(supemon playerSupemons[], short *selectedSupemon, short possessedSupemons);
short actionUseItem(inventory *playerInventory, supemon supemons[], short selectedSupemon, short *ptUsedItems);
short actionCapture(supemon supemonList[], supemon enemy, short *ptPossessedSupemons);
short actionRunAway(supemon selectedSupemon, supemon enemy);

void switchPlayer(short *player);
void endFight(short victory, int *ptBalance, short enemyLevel, supemon playerSupemon);

short startFight(supemon *enemy, supemon playerSupemons[], short *selectedSupemon, inventory *playerInventory, char playerName[32], int *balance, short *possessedSupemons);

#endif /* FIGHT_H_ */
