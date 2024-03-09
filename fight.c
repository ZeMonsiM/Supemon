#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"

void printSupemonStats(supemon *enemy, supemon playerSupemons[], short selectedSupemon, char playerName[32]) {
	printf("------------------------\n");
	printf("%s (enemy)\n", enemy->name);
	printf("HP: %hd/%hd\tLvl: %hd\n", enemy->hp, enemy->maxHp, enemy->level);
	printf("Atk: %hd\t\tDef: %hd\n", enemy->att, enemy->def);
	printf("Acc: %hd\t\tEva: %hd\n", enemy->acc, enemy->eva);
	printf("------------------------\n");
	printf("%s (%s)\n", playerSupemons[selectedSupemon].name, playerName);
	printf("HP: %hd/%hd\tLvl: %hd\n", playerSupemons[selectedSupemon].hp, playerSupemons[selectedSupemon].maxHp, playerSupemons[selectedSupemon].level);
	printf("Atk: %hd\t\tDef: %hd\n", playerSupemons[selectedSupemon].att, playerSupemons[selectedSupemon].def);
	printf("Acc: %hd\t\tEva: %hd\n", playerSupemons[selectedSupemon].acc, playerSupemons[selectedSupemon].eva);
	printf("------------------------\n\n");
}

short launchSelectionMenu(supemon playerSupemons[], short selectedSupemon) {
	while (1) {
		short selection;
		printf("+----------------------+\n");
		printf("|What will you do?     |\n");
		printf("|    1 - Move          |\n");
		printf("|    2 - Change Supemon|\n");
		printf("|    3 - Use Item      |\n");
		printf("|    4 - Capture       |\n");
		printf("|    5 - Run Away      |\n");
		printf("+----------------------+\n");
		printf("\n1, 2, 3, 4 or 5: ");
		scanf("%hd", &selection);

		if (selection > 0 && selection < 6) {
			return selection;
		}
	}
}

void switchPlayer(short *player) {
	*player = (*player + 1) %2;
}

void endFight(short victory, int *balance, short enemyLevel, supemon *playerSupemon) {
	if (victory) {
		// Donner de l'XP et récompenser le joueur avec des supcoins
		short reward = rand() %400 + 100;
		*balance += reward;

		int expReward = (rand() %400 + 100) * enemyLevel;
		playerSupemon->exp += expReward;
		while (playerSupemon->exp >= (playerSupemon->level * 1000 - 500)) {
			playerSupemon->exp -= (playerSupemon->level * 1000 - 500);
			levelUpSupemon(playerSupemon);
			printf("%s is now Level %hd!\n", playerSupemon->name, playerSupemon->level);
		}

		printf("\nYOU WIN!\nGained %hd Supcoins!\nGained %d Exp for %s!\n", reward, expReward, playerSupemon->name);
	} else {
		printf("\nBetter luck next time...\n");
	}
}








short actionMove(supemon *enemy, supemon playerSupemons[], short selectedSupemon) {
	// Récupérer le move que le joueur veut exécuter
	short selection;
	do {
		printf("\n1 - %s\n", playerSupemons[selectedSupemon].moves[0].name);
		printf("2 - %s\n", playerSupemons[selectedSupemon].moves[1].name);
		printf("3 - CANCEL\n");
		printf("1, 2 or 3: ");
		scanf("%hd", &selection);
	} while (selection < 1 || selection > 3);

	// Cas: CANCEL
	if (selection == 3) {
		return;
	}

	selection--;
	// Faire le move
	if (strcmp(playerSupemons[selectedSupemon].moves[selection].type, "dmg") == 0) {
		// Attaque
		float damageDealt = playerSupemons[selectedSupemon].moves[selection].value * playerSupemons[selectedSupemon].att / enemy->def;
		float integerPart;
		if (modff(damageDealt, &integerPart) != 0) {
			damageDealt = rand() %2 == 0 ? floorf(damageDealt) : ceilf(damageDealt);
		}
		enemy->hp -= damageDealt;
		printf("%s uses %s and deals %f damage!\n", playerSupemons[selectedSupemon].name, playerSupemons[selectedSupemon].moves[selection].name, damageDealt);
	} else {
		// Boost de stats
		if (strcmp(playerSupemons[selectedSupemon].moves[selection].type, "att") == 0) {
			playerSupemons[selectedSupemon].att += playerSupemons[selectedSupemon].moves[selection].value;
		} else if (strcmp(playerSupemons[selectedSupemon].moves[selection].type, "eva") == 0) {
			playerSupemons[selectedSupemon].eva += playerSupemons[selectedSupemon].moves[selection].value;
		} else if (strcmp(playerSupemons[selectedSupemon].moves[selection].type, "def") == 0) {
			playerSupemons[selectedSupemon].def += playerSupemons[selectedSupemon].moves[selection].value;
		}
		printf("%s uses %s!\n", playerSupemons[selectedSupemon].name, playerSupemons[selectedSupemon].moves[selection].name);
	}
}

short actionChange(supemon playerSupemons[], short *selectedSupemon, short possessedSupemons) {
	printf("Please select a Supemon from the list :\n");
	short selection;
	for (short i = 0; i < possessedSupemons; i++) {
		printf("%hd - %s (level %hd)\n", i + 1, playerSupemons[i].name, playerSupemons[i].level);
	}
	do {
		printf("\nChoose a Supemon: ");
		scanf("%hd", &selection);
	} while (selection < 1 || selection > possessedSupemons);

	*selectedSupemon = selection - 1;
}

short actionUseItem(inventory *ptPlayerInventory, supemon supemons[], short selectedSupemon, short *ptUsedItems) {
	// Vérifier si la limite d'items a été atteinte
	if (*ptUsedItems >= 4) {
		printf("You have already used 4 items during this fight!\n");
		return 0;
	}

	// Afficher le menu si le joueur peut encore utiliser un item
	while (1) {
		short item;
		printf("+---------------------+\n");
		printf("| Your inventory      |\n");
		printf("| %hd\t potion       |\n", ptPlayerInventory->potion);
		printf("| %hd\t super_potion |\n", ptPlayerInventory->super_potion);
		printf("| %hd\t rare_candy   |\n", ptPlayerInventory->rare_candy);
		printf("+---------------------+\n");
		printf("| ENTER '4' TO CANCEL |\n");
		printf("+---------------------+\n");
		do {
			printf("\nDo you want to use a potion (1), a super_potion (2) or a rare_candy (3): ");
			scanf("%hd", &item);
		} while (item < 1 || item > 4);

		switch (item) {
		case 1:
			if (ptPlayerInventory->potion < 1) {
				printf("You don't have any potions in your inventory!\n");
			} else {
				supemons[selectedSupemon].hp = supemons[selectedSupemon].hp + 5 > supemons[selectedSupemon].maxHp ? supemons[selectedSupemon].maxHp : supemons[selectedSupemon].hp + 5;
				ptPlayerInventory->potion--;
				printf("You used a potion!\n");
				printf("You have used %hd/4 items during this fight.\n", ++*ptUsedItems);
				return 1;
			}
			break;

		case 2:
			if (ptPlayerInventory->super_potion < 1) {
				printf("You don't have any super_potions in your inventory!\n");
			} else {
				supemons[selectedSupemon].hp = supemons[selectedSupemon].hp + 10 > supemons[selectedSupemon].maxHp ? supemons[selectedSupemon].maxHp : supemons[selectedSupemon].hp + 10;
				ptPlayerInventory->super_potion--;
				printf("You used a super_potion!\n");
				printf("You have used %hd/4 items during this fight.\n", ++*ptUsedItems);
				return 1;
			}
			break;

		case 3:
			if (ptPlayerInventory->rare_candy < 1) {
				printf("You don't have any rare_candy in your inventory!\n");
			} else {
				levelUpSupemon(&supemons[selectedSupemon]);
				ptPlayerInventory->rare_candy--;
				printf("You used a rare_candy!\n");
				printf("You have used %hd/4 items during this fight.\n", ++*ptUsedItems);
				return 1;
			}
			break;

		case 4:
			return 0;
		}
	}
}

short actionCapture(supemon supemonList[], supemon enemy, short *ptPossessedSupemons) {
	printf("You are trying to capture the enemy Supemon...\n");
	sleep(3);
	short successRate = ((enemy.maxHp - enemy.hp) * 100) / enemy.maxHp - 50;
	if (successRate <= rand() %100) {
		// Supemon capturé
		printf("You managed to capture the enemy Supemon!\n");
		supemonList[*ptPossessedSupemons] = enemy;
		(*ptPossessedSupemons)++;
		return 1;
	} else {
		printf("Failed!\n");
		return 0;
	}
}

short actionRunAway(supemon selectedSupemon, supemon enemy) {
	short successRate = (selectedSupemon.speed * 100) / (selectedSupemon.speed + enemy.speed);
	if (successRate <= rand() %100) {
		// Arrêter le combat
		printf("You ran away from the fight...\n");
		return 1;
	} else {
		printf("Failed to run away!\n");
		return 0;
	}
}






short startFight(supemon *enemy, supemon playerSupemons[], short *selectedSupemon, inventory *ptPlayerInventory, char playerName[32], int *ptBalance, short *ptPossessedSupemons) {
	// Choisir le premier joueur selon la stat speed et initialiser le compteur d'items
	short playerTurn = enemy->speed == playerSupemons[*selectedSupemon].speed ? rand() %2 == 1 : enemy->speed < playerSupemons[*selectedSupemon].speed;
	short usedItems = 0;

	// Remettre le Supemon a ses stats de base
	playerSupemons[*selectedSupemon].att = playerSupemons[*selectedSupemon].baseAtt;
	playerSupemons[*selectedSupemon].def = playerSupemons[*selectedSupemon].baseDef;
	playerSupemons[*selectedSupemon].eva = playerSupemons[*selectedSupemon].baseEva;
	playerSupemons[*selectedSupemon].acc = playerSupemons[*selectedSupemon].baseAcc;

	// Lancer la boucle
	while (playerSupemons[*selectedSupemon].hp > 0 && enemy->hp > 0) {
		if (playerTurn) {
			// Tour du joueur
			printf("Your turn...\n\n");
			printSupemonStats(enemy, playerSupemons, *selectedSupemon, playerName);
			short action = launchSelectionMenu(playerSupemons, *selectedSupemon);
			short success;
			switch (action) {
			case 1:
				if (actionMove(enemy, playerSupemons, *selectedSupemon)) {
					switchPlayer(&playerTurn);
				}
				break;

			case 2:
				if (actionChange(playerSupemons, selectedSupemon, *ptPossessedSupemons)) {
					switchPlayer(&playerTurn);
				}
				break;

			case 3: ;
				success =	actionUseItem(ptPlayerInventory, playerSupemons, *selectedSupemon, &usedItems);
				if (success) {
					switchPlayer(&playerTurn);
				}
				break;

			case 4: ;
				if(actionCapture(playerSupemons, *enemy, ptPossessedSupemons)) {
					endFight(1, ptBalance, enemy->level, &playerSupemons[*selectedSupemon]);
					return 1;
				}
				switchPlayer(&playerTurn);
				break;

			case 5:
				if (actionRunAway(playerSupemons[*selectedSupemon], *enemy)) {
					return 1;
				}
				switchPlayer(&playerTurn);
				break;
			}
		} else {
			// Tour de l'IA
			printf("[DEBUG] AI Turn\n");
			switchPlayer(&playerTurn);
		}
	}

	// Fin du combat
	endFight(playerSupemons[*selectedSupemon].hp > 0, ptBalance, enemy->level, &playerSupemons[*selectedSupemon]);
	return playerSupemons[*selectedSupemon].hp > 0;
}
