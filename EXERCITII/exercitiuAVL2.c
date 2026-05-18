#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//ABC

typedef struct Nod Nod;
typedef struct Student{
    int id;
    char *nume;
    int grupa;
    float medie;
} Student;


struct Nod{
    Student info;
    Nod *st, *dr;
};

Student initStudent(int id, char *nume, int grupa, float medie){
    Student s;
    s.id=id;
    s.grupa=grupa;
    s.medie=medie;
    s.nume=(char*)malloc(strlen(nume)+1);
    strcpy(s.nume, nume);

    return s;
}

void afisareStudent(Student s){
    printf("\nId: %d Nume: %s Grupa: %d Medie: %.2f", s.id, s.nume, s.grupa, s.medie);
}

int maxim(int a, int b)
{
    return a>b?a:b;
}

int inaltimeArbore(Nod *radacina){
    if(radacina==NULL)
        return 0;
    return maxim(inaltimeArbore(radacina->st), inaltimeArbore(radacina->dr))+1;
}

int diferentaInaltimiSubarbori(Nod *radacina){
    if(radacina==NULL)
        return 0;
    return inaltimeArbore(radacina->st)-inaltimeArbore(radacina->dr);
}

void rotireLaDreapta(Nod **rad){
    Nod *aux =(*rad)->st;
    (*rad)->st = aux->dr;
    aux->dr=*rad;
    *rad=aux;
}

void rotireLaStanga(Nod **rad){
    Nod *aux = (*rad)->dr;
    (*rad)->dr = aux->st;
    aux->st=*rad;
    *rad=aux;
}

void echilibrare(Nod **rad){
    if(*rad==NULL)
        return;

    int heightDiff = diferentaInaltimiSubarbori(*rad);

    if (heightDiff == -2 ) //debalansare de la dreapta
    {
        if(diferentaInaltimiSubarbori((*rad)->dr) == 1)
            rotireLaDreapta(&(*rad)->dr);
        rotireLaStanga(rad);
    }

    if(heightDiff == 2) //debalansare la stanga
    {
        if(diferentaInaltimiSubarbori((*rad)->st) == -1)
            rotireLaStanga(&(*rad)->st);
        rotireLaDreapta(rad);
    }
}

void inserareInAVL(Nod **radacina, Student s){
    if(*radacina==NULL){
        Nod *nou=(Nod*)malloc(sizeof(Nod));
        nou->info=s;
        nou->dr=NULL;
        nou->st=NULL;
        *radacina=nou;
    }
    else if (s.id < (*radacina)->info.id)
    {
        inserareInAVL(&(*radacina)->st, s);
    }
    else 
    {
        inserareInAVL(&(*radacina)->dr, s);
    }

    echilibrare(radacina);
}

void parcurgereInOrdine(Nod *rad){
    if(rad){
        parcurgereInOrdine(rad->st);
        afisareStudent(rad->info);
        parcurgereInOrdine(rad->dr);
    }
}

int numaraNoduri(Nod *radacina){
    if(radacina==NULL)
        return 0;
    return numaraNoduri(radacina->st) + numaraNoduri(radacina->dr) +1;
}

void AVLtoVector(Nod *radacina, Student *vector, int *index){
    if(radacina==NULL)
        return;
    AVLtoVector(radacina->st, vector, index);
    vector[(*index)++]=radacina->info;
    AVLtoVector(radacina->dr, vector, index);
}

void dezalocare(Nod **radacina){
    if(*radacina){
        dezalocare(&(*radacina)->st);
        dezalocare(&(*radacina)->dr);
        free((*radacina)->info.nume);
        free(*radacina);
        *radacina=NULL;
    }
}

int main(){
    Nod *radacina = NULL;
    inserareInAVL(&radacina, initStudent(1, "Alex", 1061, 9.80));
    inserareInAVL(&radacina, initStudent(5, "Alex", 1061, 9.80));
    inserareInAVL(&radacina, initStudent(4, "Alex", 1061, 9.80));
    inserareInAVL(&radacina, initStudent(3, "Alex", 1061, 9.80));
    inserareInAVL(&radacina, initStudent(2, "Alex", 1061, 9.80));
    inserareInAVL(&radacina, initStudent(6, "Alex", 1061, 9.80));

    parcurgereInOrdine(radacina);

    int dim = numaraNoduri(radacina);
    Student *vector = (Student *)malloc(sizeof(Student) * dim);
    int index = 0;
    AVLtoVector(radacina, vector, &index);

    printf("\n===================");
    for(int i=0; i<dim; i++){
        afisareStudent(vector[i]);
    }

    free(vector);
    dezalocare(&radacina);
    return 0;
}


