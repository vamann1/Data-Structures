#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MaxHeap MaxHeap;
typedef struct Student{
    int prioritate;
    char *nume;
    int varsta;
    float medie;
} Student;

struct MaxHeap{
    Student *vector;
    int size;
}; 

Student initStudent(int prioritate, char *nume, int varsta, float medie){
    Student s;
    s.prioritate=prioritate;
    s.medie=medie;
    s.varsta=varsta;
    s.nume=(char*)malloc(strlen(nume)+1);
    strcpy(s.nume, nume);

    return s;
}

void afisareStudent(Student s){
    printf("\n%d. Nume: %s Varsta: %d Medie: %.2f", s.prioritate, s.nume, s.varsta, s.medie);
}

void parcurgereMaxHeap(MaxHeap heap){
    for(int i = 0; i<heap.size; i++){
        afisareStudent(heap.vector[i]);
    }
}

void heapify(MaxHeap heap, int index){
    int pozMax = index;
    int pozSt = 2*index+1;
    int pozDr = 2*index+2;

    if(pozSt<heap.size && heap.vector[pozMax].prioritate < heap.vector[pozSt].prioritate)
    {
        pozMax = pozSt;
    }

    if (pozDr < heap.size && heap.vector[pozMax].prioritate < heap.vector[pozDr].prioritate) 
    {
        pozMax = pozDr;
    }

    if(pozMax != index){
        Student aux = heap.vector[pozMax];
        heap.vector[pozMax] = heap.vector[index];
        heap.vector[index]=aux;

        if(pozMax <= heap.size/2-1){
        heapify(heap, pozMax);
        }
    }
}

Student extragereStudent(MaxHeap *heap){
    Student s = initStudent(heap->vector->prioritate, heap->vector->nume,
                            heap->vector->varsta, heap->vector->medie);
    Student aux = heap->vector[0];
    heap->vector[0]=heap->vector[heap->size-1];
    heap->vector[heap->size-1]=aux;
    heap->size--;
    heapify(*heap, 0);
    return s;
}

int main(){
    
    MaxHeap heap;
    heap.size = 8;
    int initialSize = 8;

    heap.vector=(Student*)malloc(heap.size*sizeof(Student));
    heap.vector[0] = initStudent(3, "Ana", 20, 8.75);
    heap.vector[1] = initStudent(7, "Mara", 22, 8.00);
    heap.vector[2] = initStudent(4, "Alex", 21, 9.25);
    heap.vector[3] = initStudent(2, "Elena", 20, 6.35);
    heap.vector[4] = initStudent(1, "Bogdan", 23, 5.80);
    heap.vector[5] = initStudent(8, "Denisa", 19, 9.50);
    heap.vector[6] = initStudent(6, "George", 20, 9.10);
    heap.vector[7] = initStudent(5, "Denis", 22, 8.50);

    printf("\nHeap inainte de heapify: ");
    parcurgereMaxHeap(heap);

    for(int i = heap.size/2-1; i>=0; i--){
        heapify(heap, i);
    }
    printf("\nMax Heap valid: ");
    parcurgereMaxHeap(heap);

    printf("\nExtragere si afisare studenti in ordinea prioritatii: ");
    while(heap.size!=0){
        Student s = extragereStudent(&heap);
        afisareStudent(s);
        free(s.nume);
    }

    for (int i = 0; i < initialSize; i++)
    {
        free(heap.vector[i].nume);
    }
    free(heap.vector);

    return 0;
}