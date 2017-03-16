#include "tietorakenne.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bottleLink addBottle(bottleLink *b, char *c, float vol, float val) {
    bottleLink ptr1 = NULL, ptr2 = NULL;
    int len = 0;

    /*Nimen pituuden laskeminen*/
    while(c[len] != '\0'){
        len++;
    }
    /*Lisätään tila loppumerkille*/
    len++;
    
    /*Muistien varaaminen*/
    if ((ptr2 = malloc(sizeof(Bottle))) == NULL) {
        perror("Muistin varaaminen epäonnistui!");
        exit(1);
    }    
    
    if ((ptr2->name = malloc(len)) == NULL) {
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
    bottleLink temp = b;
    int i = 0;
    while (i++ < n) temp = (temp == NULL) ? NULL : temp->next;
    return temp; 

}

/* Palauttaa listan pituuden */
int getTotalNode(bottleLink b) {
    bottleLink temp = b;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

bottleLink freeBottle(bottleLink b){
    bottleLink ptr = b;
    while(ptr != NULL){
         
        b = ptr->next;
        free(ptr->name);
	ptr->count = 0;
        free(ptr);
        ptr = b;
    }
    b = NULL;
    b = NULL;
    return b;
}
