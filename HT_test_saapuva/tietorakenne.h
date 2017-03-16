#ifndef TIETORAKENNE_H
#define TIETORAKENNE_H

/* Tietue tuotetietojen linkitettyä listaa varten. 
   Tiedostostaluvun yhteydessä jokaiselle tuotteelle oma numero järjestyksessä (käytetään palautusvalikossa) */
struct tuotetiedot 
{
	int tuotenro;
	char *tyyppi;
	float koko;
	float pantti;
	struct tuotetiedot *seuraava;
};
typedef struct tuotetiedot tuotetiedot;

/* Tietue palautustietojen linkitettyä listaa varten. */
struct palautustiedot 
{
	int tuotenro;
	int maara;
	struct palautustiedot *seuraava;
};
typedef struct palautustiedot palautustiedot;

/* Lisää alkio tuotetietojen listaan. Palauttaa listan ensimmäisen alkion. */
tuotetiedot* lisaaTuotelistaan(tuotetiedot* listanalku, int tuotenro, char *tyyppi, float koko, float pantti);

/* Tulostaa tuotteiden tiedot. Palauttaa tuotteiden määrän. */
int tulostaTuotelista(tuotetiedot *listanalku);

/* Vapauttaa tuotelistan muistin. */
void tyhjennaTuotelista(tuotetiedot *listanalku);

/* Lisää alkion palautettujen tuotteiden listaan. Palauttaa listan ensimmäisen alkion. */
palautustiedot* lisaaPalautuslistaan(palautustiedot* listanalku, int tuotenro);

/* Etsii tuotteen numeroa vastaavat tuotetiedot. Palauttaa alkion tuotetiedot-listasta, joka vastaa annettua
   tuotenumeroa, tai NULL jos numeroa ei ole listalla. */
tuotetiedot* etsiTuotetiedot(int tuotenumero, tuotetiedot *listanalku);

/* Vapauttaa palautuslistan muistin ja palauttaa tyhjän listan takaisin. */
palautustiedot* tyhjennaPalautuslista(palautustiedot *listanalku);

#endif
