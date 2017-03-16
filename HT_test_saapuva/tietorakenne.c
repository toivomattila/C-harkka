#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tietorakenne.h"

/* Linkitetyn listan luonti.
   tiedosto.c:ssä luetaan tiedoston riviltä muuttujat 
   ja kutsutaan niillä tätä funktiota silmukassa 
   niin kauan kuin tiedostossa riittää rivejä. */

tuotetiedot* lisaaTuotelistaan(tuotetiedot* listanalku, int tuotenro, char *tyyppi, float koko, float pantti) {

	tuotetiedot *uusi, *ptr;
	
	/* Muistin varaus, merkkijonoille pituuden mukaan */
	if ((uusi = (tuotetiedot*)malloc(sizeof(tuotetiedot))) == NULL) {
		perror("Muistin varaus epäonnistui.");
		exit(1);
	}
	if ((uusi->tyyppi = (char*)malloc((strlen(tyyppi) + 1)*sizeof(char))) == NULL) {
		perror("Muistin varaus epäonnistui.");
		exit(1);
	}
	/*if ((uusi->koko = (char*)malloc((strlen(koko) + 1)*sizeof(char))) == NULL) {
		perror("Muistin varaus epäonnistui.");
		exit(1);
	}*/

	/* Muuttujat paikoilleen */
	uusi->tuotenro = tuotenro;
	strcpy(uusi->tyyppi, tyyppi);
	uusi->koko = koko;
	uusi->pantti = pantti;

	/* ...ja lisätään alkio listan hännille */
	if (listanalku == NULL) {
		listanalku = uusi;
	} else {
		ptr = listanalku;
		while (ptr->seuraava != NULL) {
			ptr = ptr->seuraava;
		}
		ptr->seuraava = uusi;
	}
	return listanalku;
}

/* Tuotetietojen tulostus valikkoa varten. Palauttaa tuotteiden määrän.
   Tämän voi toki siirtää muitten valikkofunktioiden mukaan jos tuntuu järkevämmältä siellä */

int tulostaTuotelista(tuotetiedot *listanalku) {
	tuotetiedot *ptr = listanalku;
	int maara = 1;
	
	while (ptr != NULL) {
		printf("%d) %s %.2fl\n", ptr->tuotenro, ptr->tyyppi, ptr->koko);
		maara = ptr->tuotenro;
		ptr = ptr->seuraava;
	}
	printf("%d) Lopeta syöttö ja tulosta kuitti.\n", maara+1);
	return maara;
}

void tyhjennaTuotelista(tuotetiedot *listanalku) {
	tuotetiedot *ptr;
	ptr = listanalku;
	
	while (ptr != NULL) {
		listanalku = ptr->seuraava;
		free(ptr->tyyppi);
		/*free(ptr->koko);*/
		free(ptr);
		ptr = listanalku;
	}
}


palautustiedot* lisaaPalautuslistaan(palautustiedot* listanalku, int tuotenro) {
	palautustiedot *uusi = NULL;
	palautustiedot *ptr = NULL;
	
	/* Muistin varaus */
	if ((uusi = (palautustiedot*)malloc(sizeof(palautustiedot))) == NULL) {
		perror("Muistin varaus epäonnistui.");
		exit(1);
	}

	/* Muuttujat paikoilleen */
	uusi->tuotenro = tuotenro;
	uusi->maara = 1;
	uusi->seuraava = NULL;



	/* Jos saman tuotenumeron alkio löytyy listasta, kasvatetaan määrää yhdellä
	   Muuten lisätään alkio listan jatkoksi */
	if (listanalku == NULL) {
		listanalku = uusi;
	} else {
		ptr = listanalku;
		while (1) {
			if (ptr->tuotenro == uusi->tuotenro) {
				ptr->maara++;
				free(uusi);
				return listanalku;
			}
			if (ptr->seuraava == NULL) {
				break;
			} else {
				ptr = ptr->seuraava;
			}
		}
		ptr->seuraava = uusi;
	}
	return listanalku;
}

/* Kuittia tehtäessä jokaisesta palautuslistan alkiosta otetaan tuotenumero ja kutsutaan sillä tätä funktiota. 
   Funktio palauttaa tuotetiedot-listasta matchaavan alkion, josta voi lukea koon, pantin yms. */
/* HUOM. Jos tuotetta ei löydy listalta, funktio palauttaa NULL-pointterin. Tämän avulla voisi halutessaan pitää
   kirjaa hylätyistä tuotteista. Meidän versiossa tätä ei pitäisi koskaan tapahtua, koska valikkohan ei anna 
   palauttaa kuin listalta löytyviä tuotteita. */

tuotetiedot* etsiTuotetiedot(int tuotenumero, tuotetiedot *listanalku) {
	tuotetiedot *ptr = listanalku;
	
	/* Käydään tuotetiedot-listaa läpi kunnes oikea tietue löytyy */
	while (!(ptr->tuotenro == tuotenumero || ptr == NULL)) {
		ptr = ptr->seuraava;
	}
	return ptr;
}

/* Palauttaa tyhjän listan, jotta voidaan tehdä useampi palautus yhdellä ajokerralla */
palautustiedot* tyhjennaPalautuslista(palautustiedot *listanalku) {
	palautustiedot *ptr;
	ptr = listanalku;
	
	while (ptr != NULL) {
		listanalku = ptr->seuraava;
		free(ptr);
		ptr = listanalku;
	}
	return listanalku;
}
