#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tietorakenne.h"


tuotetiedot* lueTuotetiedot(tuotetiedot* listanalku) /* Luetaan tuotetiedosto.txt ja parsitaan siitä tiedot tietorakenteissa määriteltyihin elementteihin. Mainista tarvitaan pointteri linkitettyyn listaan. lisaaTuotelistaan hoitaa tallennuksen. Palauttaa nollan jos kaikki OK.*/ 
{
	FILE *tiedosto;
	int tuotenumero = 1;
	char tyyppi[40];
	float koko;
	float pantti;
	
	if ((tiedosto = fopen("tuotetiedosto.txt", "r")) == NULL) 
	{
		perror("Tiedoston avaus epäonnistui.\n");
		exit(1);
	}
	
	/* fscanf palauttaa oikein luettujen kenttien määrän*/
	while (fscanf(tiedosto, "%s %f %f", tyyppi, &koko, &pantti) == 3)
	{
		listanalku = lisaaTuotelistaan(listanalku, tuotenumero, tyyppi, koko, pantti);
		tuotenumero++;
	}
	
	
	fclose(tiedosto);
	return listanalku;
}
		
int kirjoitaTilapaistiedosto(char *tyyppi, float koko, float pantti)
{
	time_t raakaAika;
	struct tm *aika;
	FILE *tiedosto;
	char puskuri[40];
	
	time(&raakaAika);
	
	aika = localtime(&raakaAika);
	strftime(puskuri,40,"%d.%m.%Y %H:%M:%S", aika);
	
	if ((tiedosto = fopen("tilapaistiedosto.txt", "a")) == NULL) 
	{
		perror("Tiedoston avaus epäonnistui.\n");
		exit(1);
	}
	
	fprintf(tiedosto, "%s:%s-%.2fl:%.2f€\n", puskuri, tyyppi, koko, pantti);
	
	fclose(tiedosto);
	return 0;
} 

int kirjoitaLokitiedosto(int maara, float pantit)
{
	time_t raakaAika;
	struct tm *aika;
	FILE *tiedosto;
	char puskuri[40];
	
	time(&raakaAika);
	
	aika = localtime(&raakaAika);
	strftime(puskuri,40,"%d.%m.%Y %H:%M:%S", aika);
	
	if ((tiedosto = fopen("lokitiedosto.txt", "a")) == NULL) 
	{
		perror("Tiedoston avaus epäonnistui.\n");
		exit(1);
	}
	
	fprintf(tiedosto, "%s - Palautukset %d kpl. Pantit %.2f€.\n", puskuri, maara, pantit);
	fclose(tiedosto);
	return 0;
}
	
int tyhjennaTilapaistiedosto(void)
{
	FILE *tiedosto;
	
	if ((tiedosto = fopen("tilapaistiedosto.txt", "w")) == NULL) 
	{
		perror("Tiedoston avaus epäonnistui.\n");
		exit(1);
		
	}
	fprintf(tiedosto,"Tilapäinen lokitiedosto\n\n");
	fclose(tiedosto);
	return 0;
}


