#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Student{
    char *nume;
    int varsta;
    float medie;
}Student;

struct Nod
{
    Student info;
    Nod *next;
};

Student citireStudent(FILE *f){
    char buffer[30];
    Student student;
    fscanf(f, "%s %d %f", buffer, &student.varsta, &student.medie);
    student.nume=(char*)malloc(sizeof(char)*strlen(buffer)+1);
    strcpy(student.nume, buffer);
    return student;
}

void afisareStudent(Student student){
    printf("\nNume: %s | Varsta: %d | Medie: %.2f", student.nume, student.varsta, student.medie);
}

void inserareLaInceput(Nod **cap, Student student){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=student;
    nou->next=*cap;
    *cap=nou;
}

void inserareLaSfarsit(Nod **cap, Student student){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=student;
    nou->next=NULL;
    if((*cap)==NULL){
        *cap=nou;
    }
    else {
        Nod *aux=*cap;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=nou;
    }
}

Nod *citireListaStudenti(const char *numeFisier)
{
    FILE *f = fopen(numeFisier, "r");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului!");
        return NULL;
    }

    Nod *cap = NULL;
    inserareLaSfarsit(&cap, citireStudent(f));
    inserareLaSfarsit(&cap, citireStudent(f));
    inserareLaSfarsit(&cap, citireStudent(f));

    fclose(f);
    return cap;
}

void afisareListaCarti(Nod *cap){
    while(cap!=NULL){
        afisareStudent(cap->info);
        cap=cap->next;
    }
}

void dezalocare(Nod **cap){
    while((*cap)!=NULL){
        free((*cap)->info.nume);
        Nod *aux=*cap;
        (*cap) = (*cap)->next;
        free(aux);
    }
}

int main(){

    Nod *cap=citireListaStudenti("studenti.txt");

    afisareListaCarti(cap);
    
    return 0;
}