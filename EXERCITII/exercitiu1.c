#include <stdio.h>
#include <string.h>
#include <stdlib.h> //<malloc.h>

typedef struct Student
{
    char* nume;
    int varsta;
    float medie;
} Student;

void citireStudent(FILE *f, Student *student){
    char buffer[30];
    fscanf(f, "%s %d %f", buffer, &student->varsta, &student->medie);
    student->nume = (char*)malloc(sizeof(char)* strlen(buffer)+1);
    strcpy(student->nume, buffer);   
}

void afisareStudent(Student student){
    printf("\nNume: %s | Varsta: %d | Medie: %.2f", student.nume, student.varsta, student.medie);
}

Student *citireStudenti(const char* numeFisier, int *nrStudenti){
    FILE *f = fopen(numeFisier, "r");
    if(!f){
        printf("Eroare la deschiderea fisierului");
        return NULL;
    }
    fscanf(f, "%d", nrStudenti);
    Student *vectorStudenti=(Student*)malloc(sizeof(Student)*(*nrStudenti));
    for(int i=0; i<(*nrStudenti); i++){
        citireStudent(f, &(vectorStudenti[i]));
    }
    fclose(f);

    return vectorStudenti;
}

void afisareStudenti(Student *studenti, int nrStudenti){
    for(int i=0; i<nrStudenti; i++){
        afisareStudent(studenti[i]);
    }

}

void dezalocare(Student **studenti, int *nrStudenti){
    for(int i=0; i<(*nrStudenti); i++){
        free((*studenti)[i].nume);
    }
    free(*studenti);
    *nrStudenti=0;
    *studenti=NULL;
}

Student *filtrareStudenti(Student *studenti, int nrStudenti, float medieMinima, int *nrFiltrati){
    for(int i=0; i<nrStudenti; i++)
    {
        if(studenti[i].medie>=medieMinima)
            (*nrFiltrati)++;
    }

    Student *studentiFiltrati = (Student*)malloc(sizeof(Student)*(*nrFiltrati));
    int j=0;
    for(int i=0; i<nrStudenti; i++)
    {
        if (studenti[i].medie >= medieMinima)
        {
        studentiFiltrati[j].nume = (char*)malloc(sizeof(char)*strlen(studenti[i].nume)+1);
        strcpy(studentiFiltrati[j].nume, studenti[i].nume);
        studentiFiltrati[j].varsta=studenti[i].varsta;
        studentiFiltrati[j].medie=studenti[i].medie;
        j++;
        }
    }

    return studentiFiltrati;
}

int main()
{
    Student student;
    FILE *f = fopen("student.txt", "r");
    citireStudent(f, &student);
    afisareStudent(student);
    fclose(f);
    free(student.nume);
    printf("\n");

    int nrStudenti=0;
    Student *studenti = citireStudenti("studenti.txt", &nrStudenti);
    afisareStudenti(studenti, nrStudenti);
    printf("\n");

    int nrFiltrati=0;
    Student *studentiFiltrati=filtrareStudenti(studenti, nrStudenti, 8.20, &nrFiltrati);
    afisareStudenti(studentiFiltrati, nrFiltrati);

    dezalocare(&studenti, &nrStudenti);
    dezalocare(&studentiFiltrati, &nrFiltrati);
}