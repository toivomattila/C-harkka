#ifndef FUNKTIO_H
#define FUNKTIO_H

#include "tietorakenne.h"

int alkuvalikko(void);
palautustiedot* palautusvalikko(tuotetiedot *pTuotteet, palautustiedot *pPalautetut);
void kuittitulostin(palautustiedot *palautusAlku, tuotetiedot *tuotetiedotAlku);
int tarkistaSyote(void);

#endif
