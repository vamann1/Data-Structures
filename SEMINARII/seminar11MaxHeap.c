#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MaxHeap MaxHeap;

typedef struct Carte
{
    int prioritate;
    char *titlu;
    int nrPagini;
    float pret;
} Carte;

struct MaxHeap
{
    Carte *vector;
    int size;
};

Carte initCarte(int prioritate, const char *titlu, int nrPagini, float pret)
{
    Carte c;
    c.prioritate = prioritate;
    c.nrPagini = nrPagini;
    c.pret = pret;
    c.titlu = (char *)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);

    return c;
}

void afisareCarte(Carte carte)
{
    printf("%d. Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.prioritate, carte.titlu, carte.nrPagini, carte.pret);
}

void traversareMaxHeap(MaxHeap heap)
{
    for (int i = 0; i < heap.size; i++)
    {
        afisareCarte(heap.vector[i]);
    }
}

void heapify(MaxHeap heap, int index)
{
    if (heap.size > 0)
    {
        int pozMax = index;
        int pozSt = 2 * index + 1;
        int pozDr = 2 * index + 2;

        if (pozSt < heap.size && heap.vector[pozMax].prioritate < heap.vector[pozSt].prioritate)
        {
            pozMax = pozSt;
        }

        if (pozDr < heap.size && heap.vector[pozMax].prioritate < heap.vector[pozDr].prioritate)
        {
            pozMax = pozDr;
        }

        if (pozMax != index)
        {
            Carte aux = heap.vector[pozMax];
            heap.vector[pozMax] = heap.vector[index];
            heap.vector[index] = aux;

            if (pozMax <= heap.size / 2 - 1)
            {
                heapify(heap, pozMax);
            }
        }
    }
}

void extragereCarteDinMaxHeap(MaxHeap *heap, Carte *c)
{
    *c = initCarte(heap->vector[0].prioritate, heap->vector[0].titlu,
                   heap->vector[0].nrPagini, heap->vector[0].pret);
    Carte aux = heap->vector[0];
    heap->vector[0] = heap->vector[heap->size - 1];
    heap->vector[heap->size - 1] = aux;
    heap->size--;
    heapify(*heap, 0);
}

int main()
{
    MaxHeap heap;
    heap.size = 7;
    int initialSize = 7;
    heap.vector = (Carte *)malloc(sizeof(Carte) * heap.size);
    heap.vector[0] = initCarte(1, "Carte1", 100, 55);
    heap.vector[1] = initCarte(2, "Carte2", 200, 65);
    heap.vector[2] = initCarte(3, "Carte3", 120, 57);
    heap.vector[3] = initCarte(4, "Carte4", 250, 58);
    heap.vector[4] = initCarte(5, "Carte5", 270, 65);
    heap.vector[5] = initCarte(6, "Carte6", 210, 59);
    heap.vector[6] = initCarte(7, "Carte7", 190, 60);

    printf("\n Forma initiala: \n");
    traversareMaxHeap(heap);

    for (int i = heap.size / 2 - 1; i >= 0; i--)
    {
        heapify(heap, i);
    }

    printf("\n MaxHeap valid: \n");
    traversareMaxHeap(heap);

    printf("\n Extragere carti din max heap: \n");
    Carte c;
    while (heap.size != 0)
    {
        extragereCarteDinMaxHeap(&heap, &c);
        afisareCarte(c);
        free(c.titlu);
    }

    printf("\n MaxHeap in ordine crescatoare: \n");
    for (int i = 0; i < initialSize; i++)
    {
        afisareCarte(heap.vector[i]);
        free(heap.vector[i].titlu);
    }
    free(heap.vector);
    
    return 0;
}