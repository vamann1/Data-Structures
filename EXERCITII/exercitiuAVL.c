/*Exercițiu : Biblioteca Digitală
O bibliotecă dorește să își gestioneze colecția de cărți printr -
un arbore AVL, ordonat după un ID unic generat la inserare.
Fiecare carte are : un titlu, un număr de pagini și un preț.
Cerințe :
Implementați structura de date și 
funcțiile necesare pentru a construi și 
menține un arbore AVL echilibrat.

Afișați colecția în toate cele trei moduri de parcurgere.

Implementați o funcție de căutare după ID care returnează cartea găsită
sau un sentinel dacă nu există.

Convertiți arborele într - un array sortat după ID,
fără a folosi o funcție separată de numărare.

Implementați ștergerea unui nod după ID, tratând corect toate cele trei cazuri posibile.

Eliberați corect toată memoria alocată la finalul programului.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Carte{
    int id;
    char *titlu;
    int nrPagini;
    float pret;
} Carte;

struct Nod{
    Carte info;
    Nod *st, *dr;
};

Carte initCarte(int id, char *titlu, int nrPagini, float pret){
    Carte c;
    c.id=id;
    c.nrPagini=nrPagini;
    c.pret=pret;
    c.titlu=(char*)malloc(strlen(titlu)+1);
    strcpy(c.titlu, titlu);
    
    return c;
}

void afisareCarte(Carte c){
    printf("\nId: %d Titlu: %s Nr. Pagini: %d Pret: %.2f", c.id, c.titlu, c.nrPagini, c.pret);
}

int maxim(int a, int b)
{
    return a > b ? a : b;
}

void rotireStanga(Nod **rad){
    Nod *aux = (*rad)->dr;
    (*rad)->dr=aux->st;
    aux->st=*rad;
    *rad=aux;
}

void rotireDreapta(Nod **rad){
    Nod *aux=(*rad)->st;
    (*rad)->st=aux->dr;
    aux->dr=*rad;
    *rad=aux;
}

int calculInaltimeArbore(Nod *rad)
{
    if (rad == NULL)
        return 0;
    else
        return maxim(calculInaltimeArbore(rad->st), calculInaltimeArbore(rad->dr)) + 1;
}

int diferentaInaltimiSubarbori(Nod *rad)
{
    return calculInaltimeArbore(rad->st) - calculInaltimeArbore(rad->dr);
}

void parcurgereInOrdine(Nod *rad, int *index)
{
    if (rad)
    {
        parcurgereInOrdine(rad->st, index);
        afisareCarte(rad->info);
        parcurgereInOrdine(rad->dr, index);
    }
}

Carte *conversieLaLista(Nod *rad, int count){
    Carte *listaCarti = (Carte *)malloc(count*sizeof(Carte));
    


    return listaCarti;
}
void inserareInAVL(Nod **rad, Carte c){
    if((*rad)==NULL)
    {
        Nod *nou=(Nod*)malloc(sizeof(Nod));
        nou->info=c;
        nou->st=NULL;
        nou->dr=NULL;
        *rad=nou;
    }
    else 
    {
        if(c.id < (*rad)->info.id)
            inserareInAVL(&(*rad)->st, c);
        else inserareInAVL(&(*rad)->dr, c);
    }

    int heightDiff=diferentaInaltimiSubarbori(*rad);

    if (heightDiff == 2) // dezechilibru stanga
    { 
        if(diferentaInaltimiSubarbori((*rad)->st) == -1) //verificare dezechilibru la dreapta
            rotireStanga(&(*rad)->st);
        rotireDreapta(rad);

    }

    if (heightDiff == -2) // dezechilbru dreapta
    {
        if(diferentaInaltimiSubarbori((*rad)->dr) == 1) //verificare dezechilibru la stanga
            rotireDreapta(&(*rad)->dr);
        rotireStanga(rad);
    }
}

Carte cautareDupaId(Nod *rad, int id){
    if(rad==NULL)
        return initCarte(-1, "", 0, 0.0);
    if(rad->info.id == id)
        return initCarte(rad->info.id, rad->info.titlu, rad->info.nrPagini, rad->info.pret);
    else if (id < rad->info.id) 
        return cautareDupaId(rad->st, id);
    else 
        return cautareDupaId(rad->dr, id);
}



void parcurgerePreOrdine(Nod *rad){
    if(rad){
        afisareCarte(rad->info);
        parcurgerePreOrdine(rad->st);
        parcurgerePreOrdine(rad->dr);
    }
}

void parcurgerePostOrdine(Nod *rad){
    if(rad){
        parcurgerePostOrdine(rad->st);
        parcurgerePostOrdine(rad->dr);
        afisareCarte(rad->info);
    }
}


int main(){
    Nod *radacina=NULL;

    inserareInAVL(&radacina, initCarte(1, "Ion", 333, 45.99));
    inserareInAVL(&radacina, initCarte(2, "Morometii", 412, 39.99));
    inserareInAVL(&radacina, initCarte(3, "Enigma", 289, 52.50));
    inserareInAVL(&radacina, initCarte(6, "Padurea", 378, 47.50));
    inserareInAVL(&radacina, initCarte(4, "Baltagul", 198, 29.99));
    inserareInAVL(&radacina, initCarte(5, "Maitreyi", 256, 34.99));
    inserareInAVL(&radacina, initCarte(7, "Ultima noapte",301, 41.99));
    inserareInAVL(&radacina, initCarte(7, "Razboiul", 200, 45));

    int dummy = 0 ;
    printf("\nParcurgere inordine: ");
    parcurgereInOrdine(radacina, dummy);

    printf("\nParcurgere preordine: ");
    parcurgerePreOrdine(radacina);

    printf("\nParcurgere postOrdine ");
    parcurgerePostOrdine(radacina);

    printf("\nInaltime arbore: %d", calculInaltimeArbore(radacina));


    printf("\nCautare dupa ID:");
    Carte c = cautareDupaId(radacina, 3);
    afisareCarte(c);
    free(c.titlu);


}