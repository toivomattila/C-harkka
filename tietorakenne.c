#include "tietorakenne.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bottleLink addBottle(bottleLink *b, char *c, float vol, float val) {
    bottleLink ptr1 = NULL, ptr2 = NULL;
    
    /*Muistien varaaminen*/
    if ((ptr2 = malloc(sizeof(Bottle))) == NULL) {
        perror("Muistin varaaminen epäonnistui!");
        exit(1);
    }    
    
    if ((ptr2->name = malloc(strlen(c))) == NULL) {
        perror("Muistin varaaminen epäonnistui!");
        exit(1);
    }
    
    /*Arvojen asettaminen*/
    strcpy(ptr2->name, c);
    

    ptr2->volume = vol;
    ptr2->value = val;    
    ptr2->next = NULL;
    
    /*Varatun muistin asettaminen listan viimeiseksi*/    
    if (*b == NULL) {
        *b = ptr2;
    } else {
        ptr1 = *b;
        while (ptr1->next != NULL) {
             
            ptr1 = ptr1->next;
        } 
        ptr1->next = ptr2;
    }
    
    return *b;
}

/*Toimii listamaisesti: n = 2 -> palauttaa 3. alkion*/
bottleLink getBottleNode(bottleLink b, int n) {
    int i = 0;
    while (i++ < n) b = (b == NULL) ? NULL : b->next;
    return b; 

}

/* Palauttaa listan pituuden */
int getTotalNode(bottleLink b) {
    int count = 0;
    while (b != NULL) {
        b = b->next;
        count++;
    }
    return count;
}

bottleLink freeBottle(bottleLink *b){
    bottleLink ptr = *b;
    while(ptr != NULL){
         
        *b = ptr->next;
        free(ptr->name);
	ptr->count = 0;
        free(ptr);
        ptr = *b;
    }
    *b = NULL;
    return *b;
}
