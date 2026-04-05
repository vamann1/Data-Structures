#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Nod Nod;

typedef struct Carte
{
    char *titlu;
    int nrPagini;
    float pret;
} Carte;

struct Nod{
    Carte info;
    Nod *next;
};

void inserareLaInceput(Nod **cap, Carte c){
    Nod *nou = (Nod*) malloc(sizeof(Nod));
    nou->info=c; //shallow copy util
    nou->next= *cap;
    *cap = nou;
}

void inserareLaSfarsit(Nod **cap, Carte c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy util
    nou->next = NULL;
    if((*cap)==NULL)
        *cap = nou;
    else {
        Nod *aux=*cap;
        while(aux->next != NULL)
        {
            aux=aux->next;
        }
        aux->next=nou;

    }
    
}

Carte citireCarte(FILE *file)
{
    char buffer[30];
    Carte c;
    fscanf(file, "%s %d %f", buffer, &c.nrPagini, &c.pret);

    c.titlu = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(c.titlu, buffer);
    return c;
}

void afisareCarte(Carte carte)
{
    printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

Nod* citireListaCarti(const char *numeFisier)
{
    FILE *file = fopen(numeFisier, "r");
    if (!file)
    {
        printf("Eroare la deschiderea fisierului!\n");
        return NULL;
    }
    Nod *cap = NULL;
    inserareLaSfarsit(&cap, citireCarte(file));
    inserareLaSfarsit(&cap, citireCarte(file));
    inserareLaSfarsit(&cap, citireCarte(file));

    fclose(file);
    return cap;
}

void afisareListaCarti(Nod*cap)
{
    while(cap!=NULL)
    {
        afisareCarte(cap->info);
        cap=cap->next;
    }
}

void dezalocare(Nod **cap){
    while((*cap) != NULL){
        free((*cap)->info.titlu);
        Nod *aux= *cap;
        (*cap) = (*cap)->next;
        free(aux);
    }

}

float pretMediuCarte(Nod *cap){
    int nrCarti=0;
    float sumaPreturi=0;
    while(cap != NULL ){
        sumaPreturi+=cap->info.pret;
        nrCarti++;
        cap=cap->next;
    }

    if(nrCarti!=0)
        return sumaPreturi/nrCarti;
    else return 0;
}

char* titlulCartii(Nod *cap, float pret){
    while(cap != NULL){
        if(cap->info.pret == pret)
            {
                char *titlu;
                titlu = (char *)malloc(sizeof(char) * (31));
                strcpy(titlu, cap->info.titlu);
                return titlu;
            }
    }
    char *titlu;
    titlu = (char *)malloc(sizeof(char) * 10);
    strcpy(titlu, "Nu s-a gasit");
    return titlu;
}
int main()
{
    Nod *cap = citireListaCarti("carti.txt");

    afisareListaCarti(cap);

    printf("\nPretul mediu pentru o carte este %.2f lei", pretMediuCarte(cap));
    dezalocare(&cap);
    printf("%s", titlulCartii(cap, 54.20)) ;
    return 0;
}