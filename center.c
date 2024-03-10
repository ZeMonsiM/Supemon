#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "center.h"

void supemonCenterLoop(supemon supemons[], short possessedSupemons) {
	while (1) {
		short supemonId;
		printf("+--------------------------------------------------+\n");
		printf("| ID    Name            Level   Health  Max Health |\n");
		printf("+--------------------------------------------------+\n");
		for (short id = 0; id < possessedSupemons; id++) {
		printf("| %hd\t%s\t%hd\t%hd\t%hd\t   |\n", id + 1, supemons[id].name, supemons[id].level, supemons[id].hp, supemons[id].maxHp);
		}
		printf("+--------------------------------------------------+\n");
		printf("\nWhich Supemon do you want to heal (enter Supemon ID or '0' to exit): ");
		scanf("%hd", &supemonId);

		if (supemonId == 0) {
			break;
		}

		if (supemonId > 0 && supemonId <= possessedSupemons) {
			// Soigner le Supémon sélectionné si il n'est pas déjà full HP
			if (supemons[supemonId - 1].hp == supemons[supemonId - 1].maxHp) {
				printf("%s is already at full health!\n", supemons[supemonId - 1].name);
				continue;
			}
			supemons[supemonId - 1].hp = supemons[supemonId - 1].maxHp;
			printf("%s has been fully healed!\n", supemons[supemonId - 1].name);
			sleep(1);
		}
	}
}
