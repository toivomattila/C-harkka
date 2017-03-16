
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

/*Käyttäytyy kuin lista: parametrilla 2 palauttaa listan 3. alkion*/
bottleLink getBottleNode(bottleLink, int);

/*Vapauttaa listalle varatun muistin ja asettaa sille annetun linkin NULLiksi*/
bottleLink freeBottle(bottleLink *);

/* Palauttaa alkioiden määrän*/
int getTotalNode(bottleLink);

#endif
