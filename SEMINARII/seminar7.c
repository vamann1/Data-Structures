#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Carte
{
    int id;
    char *titlu;
    int nrPagini;
    float pret;
} Carte;

struct Nod
{
    Carte info;
    Nod *stanga;
    Nod *dreapta;
};


void afisareCarte(Carte carte)
{
    printf("%d. Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.id, carte.titlu, carte.nrPagini, carte.pret);
}


Carte initCarte(int id, const char *titlu, int nrPagini, float pret)
{
    Carte c;
    c.id=id;
    c.nrPagini = nrPagini;
    c.pret = pret;
    c.titlu = (char *)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);

    return c;
}

void inserareInABC(Nod **radacina, Carte carte){
    if(*radacina==NULL){
        Nod *nou = (Nod*)malloc(sizeof(Nod));
        nou->info=carte;
        nou->stanga=NULL;
        nou->dreapta=NULL;
        *radacina=nou;
    } else if(carte.id<(*radacina)->info.id)
    {
        inserareInABC(&(*radacina)->stanga, carte);

    } else 
    {
        inserareInABC(&(*radacina)->dreapta, carte);
    }
}

void inOrdine(Nod *rad){
    if(rad){
        inOrdine(rad->stanga);
        afisareCarte(rad->info);
        inOrdine(rad->dreapta);
    }
}

void preOrdine(Nod*rad){
    if (rad)
    {
        afisareCarte(rad->info);
        inOrdine(rad->stanga);
        inOrdine(rad->dreapta);
    }
}

void postOrdine(Nod *rad){
    if (rad)
    {
        inOrdine(rad->stanga);
        inOrdine(rad->dreapta);
        afisareCarte(rad->info);
    }
}

Carte cautareDupaId(Nod *rad, int id){
    if(rad==NULL){
        return initCarte(-1, "Necunoscut", 0, 0);
    } else if(id==rad->info.id){
        return initCarte(rad->info.id, rad->info.titlu, rad->info.nrPagini, rad->info.pret);
    }
    else if(id< rad->info.id){
        return cautareDupaId(rad->stanga, id);
    } else {
        return cautareDupaId(rad->dreapta, id);
    }
}

void dezalocare(Nod **rad){
    if(*rad!=NULL){
    dezalocare(&(*rad)->stanga);
    dezalocare(&(*rad)->dreapta);
    free((*rad)->info.titlu);
    free(*rad);
    }
}

int maxim(int a, int b)
{
    return (a > b) ? a : b;
}

int calculInaltimeArbore(Nod *rad){
    if(rad){
        return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta)) +1;
    } else {
        return 0;
    }
}

int main()
{
    //7, 4, 10, 2, 6, 8, 11
    Nod *rad = NULL;
    inserareInABC(&rad, initCarte(7, "Carte1", 100, 55.0));
    inserareInABC(&rad, initCarte(4, "Carte2", 200, 65.0));
    inserareInABC(&rad, initCarte(10, "Carte3", 120, 57.0));
    inserareInABC(&rad, initCarte(2, "Carte4", 250, 58.0));
    inserareInABC(&rad, initCarte(6, "Carte5", 270, 59.0));
    inserareInABC(&rad, initCarte(8, "Carte6", 210, 60.0));
    inserareInABC(&rad, initCarte(11, "Carte7", 190, 55.0));

    printf("\nParcurgere inordine:\n");
    inOrdine(rad);

    Carte carteaCautata = cautareDupaId(rad, 8);
    printf("\nCarte cautata:\n");
    afisareCarte(carteaCautata);
    free(carteaCautata.titlu);

    int inaltime = calculInaltimeArbore(rad);
    printf("\nInaltime arbore: %d", inaltime);
    

    dezalocare(&rad);
}