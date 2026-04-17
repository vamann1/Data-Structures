#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Nod Nod;

typedef struct Student {
    char *nume;
    int varsta;
    float medie;
} Student;

struct Nod{
    Student info;
    Nod *next;
    Nod *prev;
};

Student initStudent(char *nume, int varsta, float medie){
    Student student;
    student.medie=medie;
    student.varsta=varsta;
    student.nume=(char*)malloc(sizeof(char)*strlen(nume)+1);
    strcpy(student.nume, nume);
    return student;
}

void inserareLaInceput(Nod **cap, Nod **coada, Student stud){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=stud;
    nou->next = *cap;
    nou->prev=NULL;
    if((*cap)==NULL){
        *cap=nou;
        *coada=nou;
    } else {
        (*cap)->prev=nou;
        *cap=nou;
    }
}

void inserareLaSfarsit(Nod **cap, Nod **coada, Student stud){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=stud;
    nou->next=NULL;
    nou->prev = *coada;
    if((*cap)==NULL){
        *cap = nou;
        *coada = nou;
    } else {
        (*coada)->next=nou;
        *coada=nou;
    }
}

void afisareLista(Nod *cap){
    while(cap!=NULL){
        printf("\nNume: %s | Varsta: %d | Medie: %.2f", cap->info.nume, cap->info.varsta, cap->info.medie);
        cap=cap->next;
    }
}

void afisareListaInversa(Nod *coada){
    printf("\n");
    while(coada!=NULL){
        printf("\nNume: %s | Varsta: %d | Medie: %.2f", coada->info.nume, coada->info.varsta, coada->info.medie);
        coada=coada->prev;
    }
}

void dezalocare(Nod **cap, Nod **coada){
    while((*cap)!=NULL){
        free((*cap)->info.nume);
        Nod *aux=(*cap);
        (*cap)=(*cap)->next;
        free(aux);
    }
    (*coada)=NULL;

}
int main(){
    Nod *cap = NULL;
    Nod *coada=NULL;

    inserareLaInceput(&cap, &coada, initStudent("Maria", 21, 9.35));
    inserareLaInceput(&cap, &coada, initStudent("Adrian", 20, 7.21));
    inserareLaInceput(&cap, &coada, initStudent("Fane", 22, 8.34));
    inserareLaSfarsit(&cap, &coada, initStudent("Denisa", 22, 8.34));
    afisareLista(cap);

    afisareListaInversa(coada);

    dezalocare(&cap, &coada);

    return 0;
}