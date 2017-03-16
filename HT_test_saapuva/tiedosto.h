#ifndef TIEDOSTO_H
#define TIEDOSTO_H

#include "tietorakenne.h"

tuotetiedot* lueTuotetiedot(tuotetiedot* listanalku);
int kirjoitaTilapaistiedosto(char *tyyppi, float koko, float pantti);
int kirjoitaLokitiedosto(int maara, float pantit);
int tyhjennaTilapaistiedosto(void);


#endif
