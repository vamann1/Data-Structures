#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Nod Nod;

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
    Nod *prev;
};

void inserareLaInceput(Nod **cap, Nod **coada, Carte c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy util
    nou->next = *cap; //prima legatura
    nou->prev=NULL;
    if(*cap == NULL)
    {
        *cap = nou;
        *coada = nou;
    }
    else 
    {
        (*cap)->prev=nou;
        *cap=nou;
    }

}

void inserareLaSfarsit(Nod **cap, Nod **coada, Carte c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy util
    nou->next = NULL;
    nou->prev = *coada;
    if ((*cap) == NULL)
    {
        *cap = nou;
        *coada=nou;
    }
    else
    {
        (*coada)->next=nou;
        *coada=nou;
    }
}

Carte initCarte(const char *titlu, int nrPagini, float pret)
{
    Carte c;
    c.nrPagini=nrPagini;
    c.pret=pret;
    c.titlu = (char *)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);

    return c;
}

void afisareCarte(Carte carte)
{
    printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareListaCarti(Nod *cap)
{
    printf("\n");
    while (cap != NULL)
    {
        afisareCarte(cap->info);
        cap = cap->next;
    }
}

void afisareInversaListaCarti(Nod *coada)
{
    printf("\n");
    while (coada != NULL)
    {
        afisareCarte(coada->info);
        coada = coada->prev;
    }
}

void dezalocare(Nod **cap, Nod **coada)
{
    while ((*cap) != NULL)
    {
        free((*cap)->info.titlu);
        Nod *aux = *cap;
        *cap = (*cap)->next;
        free(aux);
    }
    *coada=NULL;
}

float pretMediuCarte(Nod *cap)
{
    int nrCarti = 0;
    float sumaPreturi = 0;
    while (cap != NULL)
    {
        sumaPreturi += cap->info.pret;
        nrCarti++;
        cap = cap->next;
    }

    if (nrCarti != 0)
    {
        return sumaPreturi / nrCarti;
    }
    else
    {
        return 0;
    }
}

int main()
{
    Nod *cap=NULL, *coada=NULL;
    inserareLaSfarsit(&cap, &coada, initCarte("Micul print", 70, 20.5));
    inserareLaSfarsit(&cap, &coada, initCarte("Norwegian Wood", 650, 40.2));
    inserareLaSfarsit(&cap, &coada, initCarte("Picture of Dorian Gray", 234, 46.9));

    afisareInversaListaCarti(coada);

    printf("\nPretul mediu pentru o carte este %.2f lei!", pretMediuCarte(cap));

    dezalocare(&cap, &coada);

    return 0;
}