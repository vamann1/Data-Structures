#define _CRT_SECURE_NO_WARNINGS
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

void inserareLaSfarsit(Nod **cap, Carte c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy util
    nou->next = NULL;
    if ((*cap) == NULL)
    {
        *cap = nou;
    }
    else
    {
        Nod *aux = *cap;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = nou;
    }
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

void dezalocare(Nod **cap)
{
    while ((*cap) != NULL)
    {
        free((*cap)->info.titlu);
        Nod *aux = *cap;
        *cap = (*cap)->next;
        free(aux);
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

HashTable initTabela(int dim){
    HashTable tabela;
    tabela.size = dim;
    tabela.vector = (Nod **)malloc(dim * sizeof(Nod*));
    for(int i=0; i<dim; i++)
    {
        tabela.vector[i]=NULL;
    }
    return tabela;
}

int hash(int nrPagini, int size){
    return nrPagini % size;
}

//mecanismul de tratare a coliziunilor este chaining
void inserareInTabela(HashTable table, Carte c){
    if(table.size > 0)
    {
        int pozitie = hash(c.nrPagini, table.size);
        if(pozitie >= 0 && pozitie < table.size)
        {
            inserareLaSfarsit(&(table.vector[pozitie]), c);
        }

    }
}

void parcurgereTabela(HashTable tabela){
    for(int i=0; i<tabela.size; i++){
        printf("Pozitie: %d\n", i);
        afisareListaCarti(tabela.vector[i]);
    }
}

void dezalocareTabela(HashTable tabela)
{
    for (int i = 0; i < tabela.size; i++)
    {
        dezalocare(&tabela.vector[i]);
    }
    free(tabela.vector);
}

//calcularea pretului mediu pentru o carte pt toate cartile care au un numar de pagini dat ca parametru
float pretMediuDupaNrPagini(HashTable table, int nrPagini){
    float pretMediu =0;
    int nrCarti = 0;
    int key = hash(nrPagini, table.size); //2
    Nod *cap = table.vector[key];
    while (cap != NULL)
    {
        if(cap->info.nrPagini == nrPagini){
                pretMediu+=cap->info.pret;
                nrCarti++;
        }
        cap= cap->next;
    }

    return pretMediu/nrCarti;

}
int main()
{
    HashTable tabela = initTabela(6);
    inserareInTabela(tabela, initCarte("MiculPrint", 132, 35.2));
    inserareInTabela(tabela, initCarte("Nuntasii", 122, 46.9));
    inserareInTabela(tabela, initCarte("Dune Messiah", 122, 71.5));
    inserareInTabela(tabela, initCarte("Confess", 126, 34.3));

    parcurgereTabela(tabela);
    int nrPagini = 122;
    printf("Pretul mediu pentru o carte cu %d numar pagini este %.2f", nrPagini, pretMediuDupaNrPagini(tabela, nrPagini));
        dezalocareTabela(tabela);
}