#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "tiedosto.h"
#include "tietorakenne.h"
#include "funktio.h"

#define ADD_TIME_STAMPS 0

int main(int argc, char *argv[]) {
	int optionMain = 2; // 2 = päällä, 1 = lopetus, muut = väärä valinta
	int optionReturn = 1;
	int bottleTotal;
	char logEntry[80];

	removeFile("tilapaistiedosto.txt");
	initTempLogFile("tilapaistiedosto.txt");

	while (optionMain == 2) {
		/* Päävalikon tulostaminen */
		printf("\nPULLONPALAUTUSAUTOMAATTI\n\n");
		while (1) {
			optionMain = printMenu();
			if (optionMain == 0 || optionMain > 2) {
				printf("Väärä valinta!\n");
			} else break;
		}
		
		if (optionMain == 2) {
			/* set these back to NULL, just in case... */
			bottleLink bottleTypes = NULL, bottleReturned = NULL, ptr = NULL;
			bottleTypes = NULL;
			bottleReturned = NULL;
			ptr = NULL;

			/* Hakee pullot listaan 'bottleTypes' */
			getBottles("tuotetiedosto.txt", &bottleTypes);

			/* Laskee pullojen määrän listassa (valikon tulostamiseen) */
			bottleTotal = getTotalNode(bottleTypes);

			while (1) {
				/* Pullonpalautusvalintojen tulostaminen */
				while (1) {
					optionReturn = printBottles(bottleTypes, bottleTotal);
					if (optionReturn > 0 && optionReturn <= bottleTotal + 1) break;
					printf("Väärä valinta!\n");
				}
				
				/* Lopetusehto */
				if (optionReturn == bottleTotal + 1) break;

				/* Pullotoiminnot */
				ptr = getBottleNode(bottleTypes, optionReturn-1);
				ptr->count++;
				addBottle(&bottleReturned, ptr->name, ptr->volume, ptr->value);
				writeTempLogEntry("tilapaistiedosto.txt", ptr, ADD_TIME_STAMPS);
				printf("\nSyötetty: %s %.2fl", ptr->name, ptr->volume);
			}

			/* Kuittilaskenta */
			receipt(bottleReturned, bottleTypes, logEntry, ADD_TIME_STAMPS);

			/* Päälokitiedosto */
			writePermLogEntry("lokitiedosto.txt", logEntry, ADD_TIME_STAMPS);

			/* Osoittimien vapauttaminen */
			bottleTypes = freeBottle(bottleTypes);
			bottleReturned = freeBottle(bottleReturned);
		}
	}

	/* reset temp log file */
	removeFile("tilapaistiedosto.txt");
	initTempLogFile("tilapaistiedosto.txt");

	printf("\nSuljetaan pullonpalautusautomaatti.\n");	
	return 0;
}
