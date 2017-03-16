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
