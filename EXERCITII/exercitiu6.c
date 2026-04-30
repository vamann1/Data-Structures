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

Student initStudent(char *nume, int varsta, float medie){
    Student s;
    s.nume=(char*)malloc(sizeof(char)*(strlen(nume)+1));
    strcpy(s.nume, nume);
    s.varsta=varsta;
    s.medie=medie;
    return s;
}

void afisareStudent(Student s){
    printf("\nNume: %s | Varsta: %d | Medie: %.2f", s.nume, s.varsta, s.medie);
}

void push(Nod **stiva, Student student){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=student;
    if((*stiva)==NULL)
    {
        *stiva=nou;
        nou->next=NULL;
    }
    else{
        nou->next=*stiva;
        *stiva=nou;
    }
}

void put(Nod **prim, Student s){
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->info=s;
    if(*prim==NULL){
        nou->next=NULL;
        *prim=nou;
    }
    else {
        Nod *aux=*prim;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=nou;
        nou->next=NULL;
    }
}

Student pop(Nod **stiva){
    if((*stiva)==NULL){
        return initStudent(NULL, 0, 0.0);
    }
    else {
        Student s =(*stiva)->info;
        Nod *aux=*stiva;
        *stiva=(*stiva)->next;
        free(aux);
        return s;
    }
}

float calculMedie(Nod *stiva){
    float medie=0;
    int cnt = 0 ;
    if(stiva==NULL){
        return medie;
    }
    while(stiva!=NULL){
        medie+=stiva->info.medie;
        cnt++;
        stiva=stiva->next;
    }
    medie/=cnt;
    return medie;
}

void dezalocare(Nod **stiva){
    if(*stiva==NULL)
        return;
    while(*stiva!=NULL){
        free((*stiva)->info.nume);
        Nod *aux=*stiva;
        *stiva=(*stiva)->next;
        free(aux);
    }
}

int main(){
    Nod *stiva=NULL;
    push(&stiva, initStudent("Laura", 21, 9.80));
    push(&stiva, initStudent("Andrei", 19, 7.42));
    push(&stiva, initStudent("Marcel", 23, 6.85));

    while(stiva!=NULL){
        Student s = pop(&stiva);
        afisareStudent(s);
    }

    push(&stiva, initStudent("Laura", 21, 9.80));
    push(&stiva, initStudent("Andrei", 19, 7.42));
    push(&stiva, initStudent("Marcel", 23, 6.85));

    float medie = calculMedie(stiva);
    printf("\nMedia studentilor = %.2f", medie);

    Nod *prim=NULL;
    put(&prim, initStudent("Laura", 21, 9.80));
    put(&prim, initStudent("Andrei", 19, 7.42));
    put(&prim, initStudent("Marcel", 23, 6.85));

    while(prim!=NULL){
        Student s = pop(&prim);
        afisareStudent(s);
        free(s.nume);
    }

    dezalocare(&stiva);
    dezalocare(&prim);

    return 0;
}