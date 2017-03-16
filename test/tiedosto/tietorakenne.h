
#ifndef TIRA_H
#define TIRA_H

typedef struct bottle* bottleLink;
typedef struct bottle {
	char* name;
	float volume;
	float value;
	float count;
	bottleLink next;
} Bottle;

/*Varaa muistin, lisää listaan ja tallentaa annetut tiedot*/
bottleLink addBottle(bottleLink *, char *, float, float);

#endif
