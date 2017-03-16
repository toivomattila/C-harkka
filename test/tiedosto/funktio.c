#include "funktio.stub.h"
#include <stdlib.h>
#include <stdio.h>
#include "tietorakenne.stub.h"
#include <ctype.h>
#include <string.h>

/* Get current time in format DD.MM.YYYY HH:MM */
/* Put the resulting string to destination variable */
/* Variable max size is 80 */
void timeNow(char * destination) {
	strcpy(destination, "30.04.2016 10:46");
}
