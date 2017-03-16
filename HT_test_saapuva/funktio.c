#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "tiedosto.h"
#include "tietorakenne.h"
#include "funktio.h"
int alkuvalikko(void) /*Tulostaa valikon ja palauttaa valinnan*/
{
	int valinta;
	printf("\nPULLONPALAUTUSAUTOMAATTI\n");
	while (1)
	{
		
		printf("\nAutomaatti on valmis ottamaan vastaan pullot ja tölkit.\n\n");
		printf("1) Aloita palautus\n");
		printf("0) Lopeta\n");
		printf("\nValitse: ");
		valinta = tarkistaSyote();
		
		
		switch (valinta)
		{
			case 1:
				break;
			case 0:
				break;
			default:
				printf("\nVäärä valinta!\n");
				continue;
		}
		break;
	}
	return valinta;
}

palautustiedot* palautusvalikko(tuotetiedot *pTuotteet, palautustiedot *pPalautetut) /*Tulostaa listan tuotteista ja lisää valintaa vastaavan tuotenumeron palautuslistaan, parametrinä osoitin tuotetietoihin. Palauttaa nollan kun palautus halutaan lopettaa. Lisää valitun tuotteen listaan, kirjoittaa väliaikaslokiin.*/
{
	int valinta, maara;
	tuotetiedot* pTiedot = NULL;
	while (1)
	{
		printf("\nSyötä uusi pullo tai tölkki.\n\n");
		maara = tulostaTuotelista(pTuotteet);
		printf("--> ");
		valinta = tarkistaSyote();
		
		if (valinta <= 0 || valinta > maara + 1)
		{
			printf("Väärä valinta!\n");
		}
		else if (valinta > 0 && valinta <= maara)
		{
			pPalautetut = lisaaPalautuslistaan(pPalautetut, valinta);
			pTiedot = etsiTuotetiedot(valinta, pTuotteet);
			kirjoitaTilapaistiedosto(pTiedot->tyyppi, pTiedot->koko, pTiedot->pantti); 
			printf("\n\nSyötetty: %s %.2fl", pTiedot->tyyppi, pTiedot->koko);
		}
		else if (valinta == maara + 1)
		{
			return pPalautetut;
		}	
		
	}
}

void kuittitulostin(palautustiedot *palautusAlku, tuotetiedot *tuotetiedotAlku) /*Tulostaa tiedot palautuksista ja kirjoittaa pysyväislokiin, parametrinä osoitin palautustietojen listaan*/
{
	tuotetiedot* etsitty = NULL;
	palautustiedot *ptr;
	ptr = palautusAlku;
	float kokoPantti, summa;
	int yhteensa = 0;
	
	time_t raakaAika;
	struct tm *aika;
	char puskuri[40];
	
	time(&raakaAika);
	
	aika = localtime(&raakaAika);
	strftime(puskuri,40,"%d.%m.%Y %H:%M:%S", aika);
	
	printf("\n\n\nKuitti %s\n", puskuri);
	while (ptr != NULL) {
	yhteensa=yhteensa+ptr->maara;
	ptr=ptr->seuraava;
	}
	printf("\nPalautetut pullot ja tölkit yhteensä %d kappaletta.\n\n",yhteensa);
	ptr= palautusAlku;
	while (ptr != NULL) {
		etsitty = etsiTuotetiedot(ptr->tuotenro, tuotetiedotAlku);
		summa = ptr->maara * etsitty->pantti;
		printf("%s %.2fl \t\tpantit %d x %.2f = %.2f€\n", etsitty->tyyppi, etsitty->koko, ptr->maara, etsitty->pantti, summa);
		kokoPantti += summa;
		ptr = ptr->seuraava;
	}
	printf("\n\nPantit yhteensä %.2f€\n\n\n", kokoPantti); 
	
	kirjoitaLokitiedosto(yhteensa, kokoPantti);
}	

int tarkistaSyote(void)
{
    char buf[20];
    int arvo, end;
    
    fflush(stdout);
    
    if (fgets(buf, sizeof buf, stdin) == NULL || sscanf(buf, "%d%n", &arvo, &end) != 1 || !isspace(buf[end]))
    {
        fflush(stdout);
        return(-1);
    }
    else
    {
    	return(arvo);
    }
}

