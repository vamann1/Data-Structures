//LIFO - ori inserare la sfarsit si extragere la sfarsit 
//       ori inserare la inceput extragere la extragere la inceput
//FIFO - inserare si extragere sunt inversate
// get = pop;

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
};

void push(Nod **stiva, Carte c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy util
    nou->next = *stiva;
    *stiva = nou;
}

void put(Nod **prim, Carte c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy util
    nou->next = NULL;
    if ((*prim) == NULL)
    {
        *prim = nou;
    }
    else
    {
        Nod *aux = *prim;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = nou;
    }
}

Carte initCarte(char *titlu, int nrPagini, float pret)
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

Carte pop(Nod** stiva)
{
    if(*stiva==NULL)
    {
        Carte c = {NULL, 0, 0};
        return c;
    }
    Carte c2 = initCarte((*stiva)->info.titlu, (*stiva)->info.nrPagini, (*stiva)->info.pret);
    Nod *copie = *stiva;
    *stiva = (*stiva)->next;
    free(copie);
    return c2;
}

void conversieDinCoadaInVector(Nod **coada, Carte **vectorCarti, int nrCarti){
    *vectorCarti= (Carte*)malloc(sizeof(Carte)*nrCarti);
    int i=0;
    while (*coada != NULL)
    {
        (*vectorCarti)[i]= pop(coada);
        i++;
    }
}

int main()
{
    Nod *stiva = NULL;

    push(&stiva, initCarte("Fratii Kamarazov", 320, 45.5));
    push(&stiva, initCarte("Norwegian Wood", 360, 60));
    push(&stiva, initCarte("Pride & Prejudice", 320, 45.5));

    printf("\nTraversare stiva: \n");
    Carte c;
    while(stiva != NULL)
    {
        c = pop(&stiva);
        afisareCarte(c);
        free(c.titlu);
    }

    Nod *coada = NULL;
    
    put(&coada, initCarte("Fratii Kamarazov", 320, 45.5));
    put(&coada, initCarte("Norwegian Wood", 360, 60));
    put(&coada, initCarte("Pride & Prejudice", 320, 45.5));

    // printf("\nTraversare coada: \n");
    // while (coada != NULL)
    // {
    //     c = pop(&coada);
    //     afisareCarte(c);
    //     free(c.titlu);
    // } 

    Carte *vectorCarti = NULL;
    int nrCarti = 4;
    conversieDinCoadaInVector(&coada, &vectorCarti, nrCarti);
    if(vectorCarti != NULL){
        printf("\nTraversare vector\n");
        for(int i = 0; i<nrCarti; i++){
            afisareCarte(vectorCarti[i]);
            free(vectorCarti[i].titlu);
            
        }
        free(vectorCarti);
    }

    //daca pe cerinta avem stiva si facem FIFO nu primim punctaj

    return 0;
}