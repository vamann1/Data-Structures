#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Carte
{
    char *titlu;
    int nrPagini;
    float pret;
} Carte;

void citireCarte(FILE *file, Carte *carte)
{
    char buffer[30];
    fscanf(file, "%s %d %f", buffer, &(*carte).nrPagini, &carte->pret);

    carte->titlu = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(carte->titlu, buffer);
}

void afisareCarte(Carte carte)
{
    printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

Carte *citireCarti(const char *numeFisier, int *nrCarti)
{
    FILE *file = fopen(numeFisier, "r");
    if (!file)
    {
        printf("Eroare la deschiderea fisierului!\n");
        return NULL;
    }

    fscanf(file, "%d", nrCarti);
    Carte *vectorCarti = (Carte *)malloc(sizeof(Carte) * (*nrCarti));
    for (int i = 0; i < *nrCarti; i++)
    {
        citireCarte(file, &(vectorCarti[i]));
    }

    fclose(file);
    return vectorCarti;
}

void afisareCarti(Carte *carti, int nrCarti)
{
    for (int i = 0; i < nrCarti; i++)
    {
        afisareCarte(carti[i]);
    }
}

dezalocare(Carte **vectorCarti, int *nrCarti)
{
    for (int i = 0; i < *nrCarti; i++)
    {
        free((*vectorCarti)[i].titlu);
    }
    free(*vectorCarti);
    *nrCarti = 0;
    *vectorCarti = NULL;
}

void main()
{
    // carte.txt:
    // MiculPrint 132 35.2
    FILE *file = fopen("carte.txt", "r");
    if (!file)
    {
        printf("Eroare la deschiderea fisierului!\n");
    }
    Carte carte;
    citireCarte(file, &carte);
    afisareCarte(carte);

    free(carte.titlu);
    fclose(file);
    int nrCarti;

    // carti.txt:
    // 3
    // MiculPrint 132 35.2
    // Nuntasii 122 46.9
    // Confess 126 34.3
    Carte *vectorCarti = citireCarti("carti.txt", &nrCarti);

    if (vectorCarti)
    {
        printf("\n");
        afisareCarti(vectorCarti, nrCarti);
    }

    dezalocare(&vectorCarti, &nrCarti);
}