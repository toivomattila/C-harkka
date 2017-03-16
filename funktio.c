#include "funktio.h"
#include <stdlib.h>
#include <stdio.h>
#include "tietorakenne.h"
#include <ctype.h>
#include <string.h>

/* Get current time in format DD.MM.YYYY HH:MM */
/* Put the resulting string to destination variable */
/* Variable max size is 80 */
void timeNow(char * destination) {
	time_t timer;
	time(&timer);
	strftime(destination, 80, "%d.%m.%Y %H:%M", localtime(&timer));
}

/* Palauttaa valikkovalinnan integerinä, kytkin päävalikon ja pullovalinnan toiminnoille */
int getIntOption(int switchMain) {
	char opt[100];
	fgets(opt, sizeof(opt), stdin);
	if (opt[strlen(opt)-1] == '\n') {
		opt[strlen(opt)-1] = '\0';
	}
	for (int i = 0; i < strlen(opt); i++) {
		if (isdigit(opt[i]) == 0) return 0;
	}
	if (switchMain == 1) {
		return atoi(opt)+1;
	} else return atoi(opt);
}

/* Tulostaa päävalikon ja palauttaa valinnan. */
int printMenu(void) {
	int option;

	printf("Automaatti on valmis ottamaan vastaan pullot ja tölkit.\n\n"
		"1) Aloita palautus\n"
		"0) Lopeta\n\n"
		"Valitse: ");

	option = getIntOption(1);
	return option;
	
}

/* Tulostaa tiedostossa olevat pullot valikoksi ja palauttaa valinnan tai nollan (lopetusvalinta) */
int printBottles(bottleLink b, int bottleNumber) {
	int option;
	int i;
	bottleLink ptr = NULL;

	/* Pullonpalautusvalintojen tulostaminen */
 	printf("\nSyötä uusi pullo tai tölkki.\n\n");
	
	for (i = 0; i < bottleNumber; i++) {
		ptr = getBottleNode(b, i);
		if (ptr == NULL) continue; /* skip invalid values */
		printf("%d) %s %.2fl\n", i+1, ptr->name, ptr->volume);
	} 
	printf("%d) Lopeta syöttö ja tulosta kuitti.\n--> ", i+1);

	/* Valinta */
	option = getIntOption(0);
	return option;
}

void receipt(bottleLink a, bottleLink b, char *text, int addTime) {
	int totalBottleT = 0;
	int totalBottleR = 0;
	float totalValue = 0;
	bottleLink ptr = NULL;

	/* Aikaleima */
	if (addTime == 1) {
		char t_now[80];
		timeNow(t_now);
		printf("\n\nKuitti %s\n\n", t_now); 
	} else {
		printf("\n\nKuitti\n\n");
	}

	/* Yhteensä */
	totalBottleR = getTotalNode(a);
	totalBottleT = getTotalNode(b);
	printf("Palautetut pullot ja tölkit yhteensä %d kappaletta.\n\n", totalBottleR);

	/* Kokonaisarvo pulloittain */
	ptr = NULL;
	ptr = b;
	for (int i=0; i<totalBottleT; i++) {
		if (ptr->count != 0) {
			printf("%s %.2fl pantit %.0f x %.2f = %.2f€\n", ptr->name, ptr->volume, ptr->count, ptr->value, 			(ptr->count * ptr->value));
		}
		totalValue = totalValue + (ptr->value * ptr->count);
		ptr = ptr->next;
	}
	printf("\n\nPantit yhteensä %.2f€\n\n\n\n", totalValue);

	/* Päälokitiedoston syötteen muokkaaminen */
	sprintf(text, "Palautukset %d kpl. Pantit %.2f€.", totalBottleR, totalValue);
}

