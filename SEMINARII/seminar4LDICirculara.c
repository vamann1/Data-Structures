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
    nou->next = *cap;
    nou->prev = NULL;
    if (*cap == NULL)
    {
        *cap = *coada = nou;
    }
    else
    {
        (*cap)->prev = nou;
        *cap = nou;
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
        *cap = *coada = nou;
    }
    else
    {
        (*coada)->next = nou;
        *coada = nou;
    }
}

Carte initCarte(const char *titlu, int nrPagini, float pret)
{
    Carte c;
    c.nrPagini = nrPagini;
    c.pret = pret;
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
    while (cap != NULL)
    {
        afisareCarte(cap->info);
        cap = cap->next;
    }
}

void afisareInversaListaCarti(Nod *coada)
{
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
    *coada = NULL;
}

float pretMediuCarte(Nod *coada)
{
    int nrCarti = 0;
    float sumaPreturi = 0;
    while (coada != NULL)
    {
        sumaPreturi += coada->info.pret;
        nrCarti++;
        coada = coada->prev;
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

void afisareListaCircularaCarti(Nod *cap)
{
    if (!cap)
    {
        return;
    }
    Nod *aux = cap;
    afisareCarte(cap->info);
    cap = cap->next;
    while (cap != aux)
    {
        afisareCarte(cap->info);
        cap = cap->next;
    }
}

void afisareListaCircularaCarti2(Nod *cap)
{
    if (!cap)
    {
        return;
    }
    Nod *aux = cap;
    do
    {
        afisareCarte(cap->info);
        cap = cap->next;

    } while (cap != aux);
}

float pretCarteMaximListaCirculara(Nod *cap)
{
    if (!cap)
    {
        return 0.0;
    }
    float pretMax = 0;
    Nod *aux = cap;
    do
    {
        if (pretMax < cap->info.pret)
            pretMax = cap->info.pret;
        cap = cap->next;

    } while (cap != aux);

    return pretMax;
}

int main()
{
    Nod *cap = NULL, *coada = NULL;
    inserareLaSfarsit(&cap, &coada, initCarte("MiculPrint", 132, 35.2));
    inserareLaSfarsit(&cap, &coada, initCarte("Nuntasii", 122, 46.9));
    inserareLaSfarsit(&cap, &coada, initCarte("Confess", 126, 34.3));

    afisareInversaListaCarti(coada);

    printf("\nPretul mediu pentru o carte este %.2f lei!\n\n", pretMediuCarte(coada));

    // LDI circulara
    coada->next = cap;
    cap->prev = coada;

    afisareListaCircularaCarti2(cap);

    printf("\nCartea cea mai scumpa costa %.2f lei!", pretCarteMaximListaCirculara(cap));

    // dezalocare(&cap, &coada);

    return 0;
}