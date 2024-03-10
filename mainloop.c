#include <stdio.h>
#include <stdlib.h>
#include "mainloop.h"

int mainMenuLoop() {
	while (1) {
		short selection;
		printf("+-----------------------------+\n");
		printf("|Where do you want to go?     |\n");
		printf("|    1 - Into the Wild        |\n");
		printf("|    2 - In the shop          |\n");
		printf("|    3 - In the Supemon Center|\n");
		printf("|    4 - Leave the Game       |\n");
		printf("+-----------------------------+\n");
		printf("\n1, 2, 3 or 4: ");
		scanf("%hd", &selection);
		fflush(stdin);

		// Petit easter egg ni vu ni connu !
		if (selection == 14298) {
			printf("- Quatorze mille deux cent nonante houite !\n- C'est quoi nonante ?\n- C'est le neuf et le houite.\n- ALORS C'EST GAGNE !\n");
			continue;
		}

		if (selection > 0 && selection < 5) {
			return selection;
		}
	}
}
