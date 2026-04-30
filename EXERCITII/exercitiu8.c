#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct HashTable HashTable;

typedef struct Carte
{
    char *titlu;
    int nrPagini;
    float pret;
} Carte;

struct Nod
{
    Carte info;
    Nod *next;
};

struct HashTable
{
    Nod **vector;
    int size;
};

Carte initCarte(char *titlu, int nrPagini, float pret){
    Carte c;
    c.nrPagini=nrPagini;
    c.pret=pret;
    c.titlu=(char*)malloc(sizeof(char)*(strlen(titlu)+1));
    strcpy(c.titlu, titlu);
    return c;
}

void insereazaLaSfarsit(Nod **cap, Carte c){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=c;
    nou->next=NULL;
    if((*cap)==NULL){
        *cap=nou;
    } else {
        Nod *aux=*cap;
        while(aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=nou;
    }
}

HashTable initTabela(int size){
    HashTable ht;
    ht.size=size;
    ht.vector=(Nod**)malloc(sizeof(Nod*)*size);
    for(int i=0; i<ht.size; i++)
        {
            ht.vector[i]=NULL;
        }
    return ht;
}

int hash(int nrPagini, int size){
    return nrPagini % size;
}

void insereazaInTabela(HashTable ht, Carte c){
    if(ht.size>0){

        int pozitie=hash(c.nrPagini, ht.size);
        if(pozitie>=0 && pozitie<ht.size)
            {
                insereazaLaSfarsit(&ht.vector[pozitie], c);
            }
    }
}

void afisareCarte(Carte c){
    printf("\nNume: %s | Nr. Pagini: %d | Pret: %.2f", c.titlu, c.nrPagini, c.pret);
}

void afisareLista(Nod *cap){
    if(cap==NULL){
        return;
    }
    while(cap!=NULL){
        afisareCarte(cap->info);
        cap=cap->next;
    }
}

void afisareTabela(HashTable ht){
    if(ht.size<=0)
        return;
    for(int i=0; i<ht.size; i++){
        printf("\nPozitie: %d", i);
        afisareLista(ht.vector[i]);
    }
}

void dezalocare(Nod **cap){
    while(*cap!=NULL){
        free((*cap)->info.titlu);
        Nod *aux=*cap;
        *cap=(*cap)->next;
        free(aux);
    }
}

void dezalocareTabela(HashTable ht){
    for(int i=0; i<ht.size; i++){
        dezalocare(&ht.vector[i]);
    }
    free(ht.vector);
}
int main(){
    HashTable ht= initTabela(5);
    insereazaInTabela(ht, initCarte("Metro", 234, 55.2));
    insereazaInTabela(ht, initCarte("NotesFromUnderground", 149, 60.3));
    insereazaInTabela(ht, initCarte("ThePlague", 392, 55.2));

    afisareTabela(ht);

    dezalocareTabela(ht);
    return 0;
}