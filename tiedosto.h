
#ifndef TIEDOSTO_H
#define TIEDOSTO_H

#include "tietorakenne.h"

/* Deletes a file. Useful when creating new temp files for bottles */
void removeFile(char* filename);

/* Get bottles as linked list */
int getBottles(char* filename, bottleLink* bottleList);

/* Append new line formatted to match temporary log file */
void writeTempLogEntry(char* filename, bottleLink bottle, int addDate);

/* init temp log file with headers */
void initTempLogFile(char* filename);

/* Append new line formatted to match permanent log file */
/* set addDate to 1 to add date automatically */
void writePermLogEntry(char* filename, char* textvalue, int addDate);


#endif