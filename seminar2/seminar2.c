#include <stdio.h>
#include <stdlib.h>
void interschimbare(int *nr1, int *nr2)
{
    // dereferentiere
    int aux = *nr1;
    *nr1 = *nr2;
    *nr2 = aux;
}

void main()
{
    int an = 2026;
    char litera = 'B';
    float inaltime = 1.71;

    printf("An: %d, litera: %c, inaltime: %.2f, litera ca decimal: %d.", an, litera, inaltime, litera);

    char prenume[6]; // Rares
    prenume[0] = 82;
    prenume[1] = 97;
    prenume[2] = 114;
    prenume[3] = 101;
    prenume[4] = 115;
    prenume[5] = '\0';

    printf("\nPrenume: %s", prenume);

    char *strada = (char *)malloc(sizeof(char) * (strlen("Mihai Eminescu") + 1));
    strcpy(strada, "Mihai Eminescu");

    printf("\nStrada: %s", strada);

    int nr1 = 10, nr2 = 7;
    interschimbare(&nr1, &nr2);

    printf("\nNr1: %d, nr2: %d", nr1, nr2);

    // dezalocare
    free(strada);
}