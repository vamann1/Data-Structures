#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Nod Nod;

typedef struct Student{
    char *nume;
    int varsta;
    float medie;
} Student;

struct Nod{
    Student info;
    Nod *next;
};

typedef struct HashTable{
    Nod **vector;
    int size;
} HashTable;

Student citireStudent(FILE *f){
    Student stud;
    char buffer[30];
    fscanf(f, "%s %d %f", buffer, &(stud.varsta), &(stud.medie));
    stud.nume=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(stud.nume, buffer);
    return stud;
}

void inserareLaSfarsit(Nod **cap, Student s){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=s;
    nou->next=NULL;
    if(*cap==NULL){
        *cap=nou;
    } else {
        Nod *aux=*cap;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=nou;
    }
}

int hash(int varsta,int size){
    return varsta%size;
}

HashTable initTabela(int size){
    HashTable table;
    table.size=size;
    table.vector=(Nod**)malloc(sizeof(Nod*)*size);
    for(int i=0; i<table.size; i++){
        table.vector[i]=NULL;
    }
    return table;
}

void inserareInTabela(HashTable table, Student s){
    if(table.size<=0)
        return;
    int pozitie=hash(s.varsta, table.size);
    if(pozitie>=0 && pozitie<table.size)
        {
            inserareLaSfarsit(&(table.vector[pozitie]), s);
        }
}

void afisareStudent(Student s){
    printf("\nNume: %s | Varsta: %d | Medie: %.2f", s.nume, s.varsta, s.medie);
}

void afisareListaStudenti(Nod *cap){
    while(cap!=NULL){
        afisareStudent(cap->info);
        cap=cap->next;
    }
}

void parcurgereTabela(HashTable ht){
    for(int i=0; i<ht.size; i++){
        afisareListaStudenti(ht.vector[i]);
    }
}

void dezalocareTabela(HashTable ht){
    for(int i=0; i<ht.size; i++){
        for (int i = 0; i < ht.size; i++)
        {
            dezalocare(&ht.vector[i]);
        }
        free(ht.vector);
    }
}

void dezalocare(Nod **cap)
{
    while ((*cap) != NULL)
    {
        free((*cap)->info.nume);
        Nod *aux = *cap;
        *cap = (*cap)->next;
        free(aux);
    }
}

// void ListaToVector(Nod *cap, Student **vector, int nrStudenti){
//     *vector=(Student*)malloc(sizeof(Student)*nrStudenti);
//     int i=0;
//     while(cap!=NULL)
//     {
//         vector[i]->medie=cap->info.medie;
//         vector[i]->varsta=cap->info.varsta;
//         vector[i]->nume=(char)malloc(sizeof(char)*(strlen(cap->info.nume)+1));
//         strcpy(vector[i]->nume, cap->info.nume);
//         cap=cap->next;
//     }
// }

int main(){

    HashTable ht= initTabela(5);
    FILE *f=fopen("studenti.txt", "r");
    if(!f)
        {
            printf("Eroare la deschiderea fisierului");
            return -1;
        }
    inserareInTabela(ht, citireStudent(f));
    inserareInTabela(ht, citireStudent(f));
    inserareInTabela(ht, citireStudent(f));
    inserareInTabela(ht, citireStudent(f));

    parcurgereTabela(ht);


    dezalocareTabela(ht);
    return 0;
}