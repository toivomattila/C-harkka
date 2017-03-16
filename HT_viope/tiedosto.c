
#include "tiedosto.h"
#include "tietorakenne.h"
#include "funktio.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/* Open file and handle possible errors */
FILE* getFileHandle(char* filename, char* mode) {
	FILE* f;
	if ((f = fopen(filename, mode)) == NULL) {
		perror("Error while opening file!\n");
		printf("Error while opening file!\n");
		exit(1);
		return NULL;
	}
	return f;
}

/* Deletes a file. Useful when creating new temp files for bottles */
void removeFile(char* filename) {
	remove(filename);
}

void initTempLogFile(char* filename) {
	FILE* datafile = getFileHandle(filename, "a");
	fprintf(datafile, "Tilapäinen lokitiedosto\n\n");
	fclose(datafile);
}

/* Append new line formatted to match temporary log file */
void writeTempLogEntry(char* filename, bottleLink b, int addDate) {
	if (b == NULL) return;
	FILE* datafile = getFileHandle(filename, "a");

	if (addDate == 1) {
		char t_now[80];

		/* Get current time */
		timeNow(t_now);

		/* Append line to file */
		fprintf(datafile, "%s:%s-%.2fl:%.2f€.\n", t_now, b->name, b->volume, b->value);
	} else {
		fprintf(datafile, "%s-%.2fl:%.2f€.\n", b->name, b->volume, b->value);
	}

	/* Append line to file */
	fclose(datafile);

}

/* Append new line formatted to match permanent log file */
void writePermLogEntry(char* filename, char* textvalue, int addDate) {
	FILE* datafile = getFileHandle(filename, "a");

	if (addDate == 1) {
		char t_now[80];
		/* Get current time */
		timeNow(t_now);
		fprintf(datafile, "%s - %s\n", t_now, textvalue);
	} else {
		fprintf(datafile, "%s\n", textvalue);
		
	}

	/* Append line to file */
	fclose(datafile);

}

int getBottles(char* filename, bottleLink* bottleList) {
	FILE* datafile = getFileHandle(filename, "r");
	char buffer[CHAR_MAX];
	char * p;
	char * results[3];
	int index = 0;

	while (fgets(buffer, CHAR_MAX, datafile) != NULL) {
		index = 0;

		/* string splitting... */
		p = strtok(buffer, " ");
		while (p != NULL) {

			results[index++] = p; /* store p to results */

			p = strtok(NULL, " ");
		}

		/* add bottle to list */
		addBottle(bottleList, results[0], atof(results[1]), atof(results[2]));
		
	}
	fclose(datafile);

	return 0;
}