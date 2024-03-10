#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "structures.h"
#include "mainloop.h"
#include "shop.h"
#include "fight.h"
#include "center.h"

/*
	Mon psy m'a dit que c'était la merde en terme
	de santé mentale à cause du langage C, donc
	pour éviter de faire un burn out j'ai décidé
	de mettre un ASCII art d'un renard !

	   /\   /\   U can do it
	  //\\_//\\     ____
	  \_     _/    /   /
	   / * * \    /^^^]
	   \_\O/_/    [   ]
		/   \_    [   /
		\     \_  /  /
		 [ [ /  \/ _/
		_[ [ \  /_/

	A ne pas prendre au sérieux (je le dis au cas ou)
*/

supemon getStarterSupemon(short supemonId) {
	// Définir tous les mouvements
	move scratch;
	strcpy(scratch.name, "Scratch");
	strcpy(scratch.type, "dmg");
	scratch.value = 3;

	move grawl;
	strcpy(grawl.name, "Grawl");
	strcpy(grawl.type, "att");
	grawl.value = 1;

	move pound;
	strcpy(pound.name, "Pound");
	strcpy(pound.type, "dmg");
	pound.value = 2;

	move foliage;
	strcpy(foliage.name, "Foliage");
	strcpy(foliage.type, "eva");
	foliage.value = 1;

	move shell;
	strcpy(shell.name, "Shell");
	strcpy(shell.type, "def");
	shell.value = 1;

	// Créer un starter
	supemon starter;
	starter.level = 1;
	starter.exp = 0;

	switch (supemonId) {
	case 1: ; // Ne pas retirer le ";", sans lui, c'est la merde !
		strcpy(starter.name, "Supmander");
		starter.hp = 10;
		starter.maxHp = 10;
		starter.att = 1;
		starter.baseAtt = 1;
		starter.def = 1;
		starter.baseDef = 1;
		starter.eva = 1;
		starter.baseEva = 1;
		starter.acc = 2;
		starter.baseAcc = 2;
		starter.speed = 1;
		starter.moves[0] = scratch;
		starter.moves[1] = grawl;
		break;

	case 2: ;
		strcpy(starter.name, "Supasaur");
		starter.hp = 9;
		starter.maxHp = 9;
		starter.att = 1;
		starter.baseAtt = 1;
		starter.def = 1;
		starter.baseDef = 1;
		starter.eva = 3;
		starter.baseEva = 3;
		starter.acc = 2;
		starter.baseAcc = 2;
		starter.speed = 2;
		starter.moves[0] = pound;
		starter.moves[1] = foliage;
		break;

	case 3: ;
		strcpy(starter.name, "Supirtle");
		starter.hp = 11;
		starter.maxHp = 11;
		starter.att = 1;
		starter.baseAtt = 1;
		starter.def = 2;
		starter.baseDef = 2;
		starter.eva = 2;
		starter.baseEva = 2;
		starter.acc = 1;
		starter.baseAcc = 1;
		starter.speed = 2;
		starter.moves[0] = pound;
		starter.moves[1] = shell;
		break;
	}

	return starter;
}

supemon generateEnemySupemon(short level) {
	// Initialiser le le Supémon
	short id = (rand() % 3) + 1;
	supemon enemy = getStarterSupemon(id);

	// Level up le Supémon
	while (enemy.level < level) {
		levelUpSupemon(&enemy);
	}

	// Mettre sa vie au maximum et appliquer les stats de base
	enemy.hp = enemy.maxHp;
	enemy.att = enemy.baseAtt;
	enemy.def = enemy.baseDef;
	enemy.eva = enemy.baseEva;
	enemy.acc = enemy.baseAcc;

	return enemy;
}

int main() {
	srand(time(NULL));
	// Initialiser les variables
	char playerName[32];
	int balance = 0;
	supemon supemonList[50];
	short selectedSupemon, possessedSupemons;
	inventory playerInventory;
	playerInventory.potion = 0;
	playerInventory.super_potion = 0;
	playerInventory.rare_candy = 0;

	printf("Enter your name: ");
	gets(playerName);
	printf("\nHello %s!\nWelcome to Supemon World!\n\n", playerName);
	short selection;
	while (1) {
		printf("+----------------------------+\n");
		printf("|Choose your starter Supemon:|\n");
		printf("|    1 - Supmander           |\n");
		printf("|    2 - Supasaur            |\n");
		printf("|    3 - Supirtle            |\n");
		printf("+----------------------------+\n");
		printf("\n1, 2 or 3: ");
		scanf("%hd", &selection);
		if (selection > 0 && selection < 4) {
			break;
		}
	}
	supemonList[0] = getStarterSupemon(selection);
	selectedSupemon = 0;
	possessedSupemons = 1;

	short gameRunning = 1;
	while (gameRunning) {
		switch(mainMenuLoop()) {
		case 1: ;
			supemon enemy = generateEnemySupemon(supemonList[selectedSupemon].level);
			startFight(&enemy, supemonList, &selectedSupemon, &playerInventory, playerName, &balance, &possessedSupemons);
			break;

		case 2:
			shopLoop(&balance, &playerInventory);
			break;

		case 3:
			supemonCenterLoop(supemonList, possessedSupemons);
			break;

		case 4:
			printf("Exiting Supemon...\n");
			gameRunning = 0;
			break;
		}
	}

	return 0;
}
