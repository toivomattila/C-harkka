#include <stdio.h>
#include "funktio.h"
#include "tiedosto.h"
#include "tietorakenne.h"

int main(void)
{
	palautustiedot* pPalautusAlku = NULL;
	tuotetiedot* pTuoteAlku = NULL;
	int alkuValinta;

	pTuoteAlku = lueTuotetiedot(pTuoteAlku);

	while (1)
	{
		alkuValinta = alkuvalikko();
		if (alkuValinta == 0)
		{
			printf("Suljetaan pullonpalautusautomaatti.\n");
			tyhjennaTuotelista(pTuoteAlku);
			return 0;
		}
		else if (alkuValinta == 1) 
		{
			/* Palautusalikko looppaa kunnes käyttäjä valitsee "lopeta ja tulosta kuitti" */
			pPalautusAlku = palautusvalikko(pTuoteAlku, pPalautusAlku);
			kuittitulostin(pPalautusAlku, pTuoteAlku);
			tyhjennaTilapaistiedosto();
			pPalautusAlku = tyhjennaPalautuslista(pPalautusAlku);
		}
	}
	
}
