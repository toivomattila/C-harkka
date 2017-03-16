#include "tiedosto.h"
#include "tietorakenne.h"
#include <stdlib.h>
#include <stdio.h>

/* Tää vuotaa muistia niin paljon ettei mitään järkeä... */

int main(int argc, char const *argv[])
{
	bottleLink bl = NULL;

	/* Get bottles from file */
	printf("TIE1 - Lue pullot tiedostosta\n");
	getBottles("tuotetiedosto.txt", &bl);
	printf("Tarkista että tuloste vastaa odotuksia ja että virheitä ei näy.\n Paina jotain jatkaaksesi.\n");
	getchar();

	/* reset log files */
	removeFile("tilapaistiedosto.txt");
	removeFile("lokitiedosto.txt");

	/* Test temp log file */
	writeTempLogEntry("tilapaistiedosto.txt", bl, 1);
	writeTempLogEntry("tilapaistiedosto.txt", bl->next, 0);

	/* Test permanent log file */
	writePermLogEntry("lokitiedosto.txt", "Palautukset 3 kpl. Pantit 0.50€", 1);
	writePermLogEntry("lokitiedosto.txt", "Palautukset 8 kpl. Pantit 2.70€", 0);



	return 0;
}
