#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "shop.h"

void shopLoop(int *balance, inventory *playerInventory) {
	while (1) {
		char action[5];
		short amount;
		char item[16];
		printf("+------------------------------+----------------------+\n");
		printf("| Available items:             | Your inventory       |\n");
		printf("| > potion (100 Supcoins)      | %hd\t potion       |\n", playerInventory->potion);
		printf("| > super_potion (300 Supcoins)| %hd\t super_potion |\n", playerInventory->super_potion);
		printf("| > rare_candy (700 Supcoins)  | %hd\t rare_candy   |\n", playerInventory->rare_candy);
		printf("+------------------------------+----------------------+\n");
		printf("| Enter 'EXIT' to return to the main menu.            |\n");
		printf("+-----------------------------------------------------+\n");
		printf("You currently have %d Supcoins\n", *balance);
		printf("Do you want to 'buy', 'sell' or 'EXIT' the shop ? ");
		scanf("%s", &action);

		// Quitter vers le menu principal
		// Ces 3 lignes de code ont trigger mon antivirus 7 fois à cause des crashes
		if (strcmp(action, "EXIT") == 0) {
			break;
		}

		// Vérifier si la commande est valide
		if (strcmp(action, "buy") != 0 && strcmp(action, "sell") != 0) {
			continue;
		}

		printf("What do you want to buy/sell\nSyntax: <amount> <item>\n> ");
		scanf("%hd %s", &amount, &item);

		if (amount <= 0) {
			continue;
		}

		if (strcmp(item, "potion") == 0 || strcmp(item, "super_potion") == 0 || strcmp(item, "rare_candy") == 0) {
			strcmp(action, "buy") == 0 ? purchaseItem(item, amount, balance, playerInventory) : sellItem(item, amount, balance, playerInventory);
		}
	}
}

short getItemPrice(char itemname[16]) {
	if (strcmp(itemname, "potion") == 0) {
		return 100;
	} else if (strcmp(itemname, "super_potion") == 0) {
		return 300;
	} else if (strcmp(itemname, "rare_candy") == 0) {
		return 700;
	}

	// bah c'est pas bien...
	return -1;
}

void purchaseItem(char itemname[16], short amount, int *balance, inventory *playerInventory) {
	short costPerItem = getItemPrice(itemname);
	int totalCost = amount * costPerItem;
	if (totalCost > *balance) {
		printf("You cannot afford to buy %hd %s!\n", amount, itemname);
	} else {
		printf("Purchasing %hd %s for %d Supcoins...\n", amount, itemname, totalCost);
		*balance -= totalCost;
		if (strcmp(itemname, "potion") == 0) {
			playerInventory->potion += amount;
		} else if (strcmp(itemname, "super_potion") == 0) {
			playerInventory->super_potion += amount;
		} else if (strcmp(itemname, "rare_candy") == 0) {
			playerInventory->rare_candy += amount;
		}
	}
}

void sellItem(char itemname[16], short amount, int *balance, inventory *playerInventory) {
	short costPerItem = getItemPrice(itemname) / 2;
	int totalGain = amount * costPerItem;
	if (strcmp(itemname, "potion") == 0) {
		if (amount > playerInventory->potion) {
			printf("You don't have enough potions to sell!\n");
			return;
		} else {
			playerInventory->potion -= amount;
		}
	} else if (strcmp(itemname, "super_potion") == 0) {
		if (amount > playerInventory->super_potion) {
			printf("You don't have enough super_potions to sell!\n");
			return;
		} else {
			playerInventory->super_potion -= amount;
		}
	} else if (strcmp(itemname, "rare_candy") == 0) {
		if (amount > playerInventory->rare_candy) {
			printf("You don't have enough rare_candies to sell!\n");
			return;
		} else {
			playerInventory->rare_candy -= amount;
		}
	}

	printf("Selling %hd %s...\n", amount, itemname);
	*balance += totalGain;
}
