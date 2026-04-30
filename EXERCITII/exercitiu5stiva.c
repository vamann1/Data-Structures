#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Pagina{
    char *url;
    char*titlu;
    int timp;
} Pagina;

struct Nod {
    Pagina info;
    Nod *next;
};

Pagina initPagina(char *url, char * titlu, int timp){
    Pagina pagina;
    pagina.timp=timp;
    pagina.url=(char*)malloc(sizeof(char)*(strlen(url)+1));
    strcpy(pagina.url, url);
    pagina.titlu = (char *)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(pagina.titlu, titlu);
    return pagina;
}

void push(Nod **varf, Pagina pagina){
    Nod *nou = (Nod*)malloc(sizeof(Nod));
    nou->info=pagina;
    nou->next=*varf;
    *varf=nou;
}

Pagina pop(Nod **varf){
    if((*varf)==NULL){
        return initPagina(NULL, NULL, 0);
    }
    Pagina pagina = (*varf)->info;
    Nod *copie=*varf;
    *varf=(*varf)->next;
    free(copie);
    return pagina;
}

void afisarePagina(Pagina pagina){
    printf("\nURL: %s | Titlu: %s | Timp de navigare: %d", pagina.url, pagina.titlu, pagina.timp);
}

void dezalocare(Nod **stiva){
    
}


int main(){
    Nod *stiva=NULL;
    push(&stiva, initPagina("facebook.com", "Facebook", 30));
    push(&stiva, initPagina("github.com", "GitHub", 230));
    push(&stiva, initPagina("Leetcode.com", "Leetcode", 5400));

    while(stiva!=NULL){
        Pagina p=pop(&stiva);
        afisarePagina(p);
        free(p.titlu);
        free(p.url);
    }

    return 0;
}