#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Arbore binar de cautare

typedef struct Nod Nod;

typedef struct Student
{
    int id;
    char *nume;
    float medie;
} Student;

struct Nod
{
    Student info;
    Nod *stanga, *dreapta;
};

Student initStudent(int id, char *nume, float medie)
{
    Student s;
    s.id = id;
    s.medie = medie;
    s.nume = (char *)malloc(strlen(nume) + 1);
    strcpy(s.nume, nume);

    return s;
}

void afisareStudent(Student s)
{
    printf("\nId: %d Nume: %s Medie %.2f", s.id, s.nume, s.medie);
}

void inserareInABC(Nod **rad, Student s)
{
    if (*rad == NULL)
    {
        Nod *nou = (Nod *)malloc(sizeof(Nod));
        nou->info = s;
        nou->dreapta = NULL;
        nou->stanga = NULL;
        *rad = nou;
    }
    else
    {
        if ((*rad)->info.id < s.id)
            inserareInABC(&(*rad)->dreapta, s);
        else
            inserareInABC(&(*rad)->stanga, s);
    }
}

void inOrdine(Nod *rad, Student *lista, int *index)
{
    if (rad)
    {
        inOrdine(rad->stanga, lista, index);
        if (lista != NULL)
        {
            lista[*index] = rad->info;
        }
        (*index)++;
        inOrdine(rad->dreapta, lista, index);
    }
}

void preOrdine(Nod *rad)
{
    if (rad)
    {
        afisareStudent(rad->info);
        preOrdine(rad->stanga);
        preOrdine(rad->dreapta);
    }
}

void postOrdine(Nod *rad)
{
    if (rad)
    {
        postOrdine(rad->stanga);
        postOrdine(rad->dreapta);
        afisareStudent(rad->info);
    }
}

Student cautareDupaId(Nod *rad, int id)
{
    if (rad == NULL)
    {
        return initStudent(-1, NULL, 0.0);
    }
    else if (rad->info.id == id)
    {
        return initStudent(rad->info.id, rad->info.nume, rad->info.medie);
    }
    else if (id < rad->info.id)
    {
        return cautareDupaId(rad->stanga, id);
    }
    else
    {
        return cautareDupaId(rad->dreapta, id);
    }
}

int maxim(int a, int b)
{
    return a > b ? a : b;
}

int calculInaltimeArbore(Nod *rad)
{
    if (rad)
    {
        return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta)) + 1;
    }
    else
    {
        return 0;
    }
}

void dezalocare(Nod **rad)
{
    if (*rad)
    {
        dezalocare(&(*rad)->stanga);
        dezalocare(&(*rad)->dreapta);
        free((*rad)->info.nume);
        free(*rad);
    }
}

Student *ABCtoArray(Nod *rad, int *count)
{
    int index = 0;
    inOrdine(rad, NULL, &index); // prima trecere: numara
    *count = index;
    Student *lista = (Student *)malloc((*count) * sizeof(Student));
    index = 0;
    inOrdine(rad, lista, &index); // a doua trecere: umple
    return lista;
}

int main()
{
    Nod *radacina = NULL;

    inserareInABC(&radacina, initStudent(3, "Andrei", 9.23));
    inserareInABC(&radacina, initStudent(2, "Andreea", 8.45));
    inserareInABC(&radacina, initStudent(1, "Marcela", 7.34));
    inserareInABC(&radacina, initStudent(4, "Denisa", 9.68));
    inserareInABC(&radacina, initStudent(5, "Alex", 5.45));
    inserareInABC(&radacina, initStudent(6, "George", 8.84));
    inserareInABC(&radacina, initStudent(7, "Daniela", 9.20));

    int dummy = 0;
    printf("\nParcurgere in ordine: ");
    inOrdine(radacina, NULL, &dummy);

    printf("\nParcurgere in preordine: ");
    preOrdine(radacina);

    printf("\nParcurgere in postordine: ");
    postOrdine(radacina);

    printf("\nCautare dupa id:\n");
    Student stud = cautareDupaId(radacina, 4);
    afisareStudent(stud);
    free(stud.nume);

    printf("\nInaltimea arborelui: %d\n", calculInaltimeArbore(radacina));

    printf("\nConversie de la arbore la lista: ");
    int count = 0;
    Student *lista = ABCtoArray(radacina, &count);

    for (int i = 0; i < count; i++)
    {
        afisareStudent(lista[i]);
    }

    dezalocare(&radacina);
    return 0;
}