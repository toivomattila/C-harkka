#ifndef FUNKTIO_H
#define FUNKTIO_H

#include "tietorakenne.h"
#include <time.h>

/* Get current time in format DD.MM.YYYY HH:MM */
/* Put the resulting string to destination variable */
/* Variable max size is 80 */
void timeNow(char * destination);

/* Integer-valinta */
int getIntOption(int switchMain);

/* Päävalikko */
int printMenu(void);

/* Pullovalikko */
int printBottles(bottleLink b, int bottleNumber);

/* Kuittitulostus  */
void receipt(bottleLink a, bottleLink b, char *text, int addTime);

#endif
