#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct Produs{
    int prioritate_id;
    char *nume;
    int cantitate;
    float pret;
} Produs;

struct Nod{
    Produs info;
    Nod *next;
    Nod *st, *dr;
};

Produs initProdus(int prioritate_id, char *nume, int cantitate, float pret){
    Produs p;
    p.prioritate_id=prioritate_id;
    p.cantitate=cantitate;
    p.pret=pret;
    p.nume=(char*)malloc(strlen(nume)+1);
    strcpy(p.nume, nume);

    return p;
}

void afisareProdus(Produs p){
    printf("\nPrioritate/Id: %d Nume: %s Cantitate: %d Pret: %.2f", p.prioritate_id, p.nume, p.cantitate, p.pret);
}

//Arbore binar de cautare 

void inserareInABC(Nod **radacina, Produs p){
    if(*radacina==NULL){
        Nod *nou = (Nod*)malloc(sizeof(Nod));
        nou->info=p;
        nou->st=NULL;
        nou->dr=NULL;
        *radacina=nou;
    }
    else if (p.prioritate_id < (*radacina)->info.prioritate_id)
    {
        inserareInABC(&(*radacina)->st, p);
    }
    else 
    {
        inserareInABC(&(*radacina)->dr, p);
    }
}

//parcurgeri afisari

void parcurgereInOrdine(Nod *rad){
    if(rad)
    {
    parcurgereInOrdine(rad->st);
    afisareProdus(rad->info);
    parcurgereInOrdine(rad->dr);
    }
}

void parcurgerePreordine(Nod *rad){
    if (rad)
    {
        afisareProdus(rad->info);
        parcurgerePreordine(rad->st);
        parcurgerePreordine(rad->dr);
    }
}

void parcurgerePostordine(Nod *rad){
    if(rad){
        parcurgerePostordine(rad->st);
        parcurgerePostordine(rad->dr);
        afisareProdus(rad->info);
    }
}

void dezalocareABC(Nod **rad){
    if(*rad==NULL)
        return;
    dezalocareABC(&(*rad)->st);
    dezalocareABC(&(*rad)->dr);
    free((*rad)->info.nume);
    free(*rad);
}

void afisareFrunze(Nod *radacina){
    if(radacina){
    if(radacina->st==NULL && radacina->dr==NULL)
    {
        afisareProdus(radacina->info);
        afisareFrunze(radacina->st);
        afisareFrunze(radacina->dr);
    }
    }
}

int numaraFrunze(Nod *radacina){
    if(radacina==NULL){
        return 0;
    }

    if(radacina->st == NULL && radacina->dr == NULL){
        return 1;
    }

    return numaraFrunze(radacina->st) + numaraFrunze(radacina->dr);
}

Nod *gasesteMin(Nod *radacina){
    while(radacina->st != NULL)
        radacina=radacina->st;
    return radacina;
}

void stergereNodABC(Nod **radacina, int id)
{
    if((*radacina)->info.prioritate_id == id)
    {
        if((*radacina)->st == NULL && (*radacina)->dr == NULL){
            free((*radacina)->info.nume);
            free(*radacina);
            *radacina = NULL;
        }
        else if((*radacina)->st == NULL) {
            Nod *aux = *radacina;
            *radacina = (*radacina)->dr;
            free(aux->info.nume);
            free(aux);
        } 
        else if ((*radacina)->dr == NULL) {
            Nod *aux = *radacina;
            *radacina = (*radacina)->st;
            free(aux->info.nume);
            free(aux);
        } else {
            Nod *succesor = gasesteMin((*radacina)->dr);
            free((*radacina)->info.nume);
            (*radacina)->info = succesor->info;
            // realoca nume pentru ca succesor->info.nume va fi eliberat
            (*radacina)->info.nume = (char *)malloc(strlen(succesor->info.nume) + 1);
            strcpy((*radacina)->info.nume, succesor->info.nume);
            stergereNodABC(&(*radacina)->dr, succesor->info.prioritate_id);
        }
    }

    else if(id < (*radacina)->info.prioritate_id)
    {
        stergereNodABC(&(*radacina)->st, id);
    }

    else 
    {
        stergereNodABC(&(*radacina)->dr, id);
    }
}

Produs cautaraDupaIdABC(Nod *radacina, int id){
    if(radacina==NULL)
        return initProdus(-1, "", 0, 0.0);
    else if ( radacina->info.prioritate_id == id)
    {
        return initProdus(radacina->info.prioritate_id, radacina->info.nume,
        radacina->info.cantitate, radacina->info.pret);
    }
    else if (id < radacina->info.prioritate_id)
    {
        return cautaraDupaIdABC(radacina->st, id);
    } 
    else 
    {
        return cautaraDupaIdABC(radacina->dr, id);
    }
}

//AVL 

int maxim(int a, int b){
    return a>b?a:b;
}

int inaltimeArbore(Nod *radacina){
    if(radacina==NULL)
    {
        return 0;
    }
    return maxim(inaltimeArbore(radacina->st), inaltimeArbore(radacina->dr)) +1;
}

int diferentaInaltimiSubarbori(Nod *radacina){
    if(radacina==NULL){
        return 0;
    }
    return inaltimeArbore(radacina->st)-inaltimeArbore(radacina->dr);
}

void rotireLaStanga(Nod **rad){
    Nod *aux = (*rad)->dr;
    (*rad)->dr = aux->st;
    aux->st=*rad;
    *rad=aux;
}

void rotireLaDreapta(Nod **rad){
    Nod *aux=(*rad)->st;
    (*rad)->st = aux->dr;
    aux->dr=*rad;
    *rad=aux;
}

void echilibrare(Nod **radacina){
    if(*radacina==NULL)
        return;

    int hDiff = diferentaInaltimiSubarbori(*radacina);

    if (hDiff == -2 ) //dezechilbru pe dreapta 
    {
        if( diferentaInaltimiSubarbori((*radacina)->dr) == 1 )
            rotireLaDreapta(&(*radacina)->dr);
        rotireLaStanga(radacina);
    }

    if (hDiff == 2 ) //dezechilibru pe stanga
    {
        if(diferentaInaltimiSubarbori((*radacina)->st) == -1)
            rotireLaStanga(&(*radacina)->st);
        rotireLaDreapta(radacina);
    }
}

void inserareInAVL(Nod **radacina, Produs p){
    if(*radacina==NULL){
        Nod *nou=(Nod*)malloc(sizeof(Nod));
        nou->info=p;
        nou->st=NULL;
        nou->dr=NULL;
        *radacina=nou;
    } 
    else if(p.prioritate_id < (*radacina)->info.prioritate_id)
    {
        inserareInAVL(&(*radacina)->st, p);
    }
    else 
    {
        inserareInAVL(&(*radacina)->dr, p);
    }

    echilibrare(radacina);
}

//parcurgere, dezalocare, cautare in arbore la fel ca la ABC

typedef struct MaxHeap MaxHeap;

struct MaxHeap{
    Produs *vector;
    int size;
};

void parcurgereMaxHeap(MaxHeap heap){
    for(int i=0; i<heap.size; i++){
        afisareProdus(heap.vector[i]);
    }
}

void heapify(MaxHeap heap, int index){
    int pozMax = index;
    int pozSt = 2*index+1;
    int pozDr = 2*index+2;

    if(pozSt < heap.size && heap.vector[pozMax].prioritate_id < heap.vector[pozSt].prioritate_id)
    {
        pozMax = pozSt;
    }

    if(pozDr < heap.size && heap.vector[pozMax].prioritate_id < heap.vector[pozDr].prioritate_id)
    {
        pozMax = pozDr;
    }

    if(pozMax!=index)
    {
        Produs aux = heap.vector[pozMax];
        heap.vector[pozMax] = heap.vector[index];
        heap.vector[index] = aux;

        heapify(heap, pozMax);
    }
}

Produs extragereDinHeap(MaxHeap *heap){
    Produs p = initProdus((*heap).vector[0].prioritate_id, (*heap).vector[0].nume,
            (*heap).vector[0].cantitate, (*heap).vector[0].pret);

    Produs aux = (*heap).vector[0];
    (*heap).vector[0]=(*heap).vector[(*heap).size-1];
    (*heap).vector[(*heap).size-1]=aux;

    (*heap).size--;
    heapify(*heap, 0);

    return p;
}

void dezalocareHeap(MaxHeap heap){
    for(int i=0; i<heap.size; i++)
    {
        free(heap.vector[i].nume);
    }
    free(heap.vector);
}

//Hash table

typedef struct HashTable HashTable;

struct HashTable{
   Nod **vector;
   int size;
};


void afisareListaProduse(Nod *cap){
    while(cap!=NULL)
    {
        afisareProdus(cap->info);
        cap=cap->next;
    }
}

void dezalocareLista(Nod **cap){
    while(*cap!=NULL)
    {
        free((*cap)->info.nume);
        Nod *aux = *cap;
        *cap=(*cap)->next;
        free(aux);
    }
}

void inserareLaSfarsit(Nod **cap, Produs p){
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = p;
    nou->next = NULL;
    if(*cap==NULL)
    {
        *cap=nou;
    }
    else 
    {
        Nod *aux = *cap;
        while(aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=nou;
    }
}

int hash(int size, int cantitate)
{
    return cantitate % size;
}

HashTable initTabela(int dim)
{
    HashTable tabela;
    tabela.size = dim;
    tabela.vector = (Nod**)malloc(sizeof(Nod*)*dim);
    for(int i=0; i<tabela.size; i++)
        tabela.vector[i]=NULL;
    
    return tabela;
}

void inserareInHashTable(HashTable tabela, Produs p){
    if(tabela.size>0)
    {
    int pozitie = hash(tabela.size, p.cantitate);

    if(pozitie>=0 && pozitie<tabela.size)
        inserareLaSfarsit(&(tabela.vector[pozitie]), p);
    }
}

void afisareTabela(HashTable tabela){
    for(int i=0; i<tabela.size; i++)
    {
        afisareListaProduse(tabela.vector[i]);
    }
}

void dezalocareTabela(HashTable tabela){
    for(int i=0; i<tabela.size; i++){
        dezalocareLista(&tabela.vector[i]);
    }
    free(tabela.vector);
}

Produs cautaProdus(HashTable tabela, int id){
    if(tabela.size > 0)
    {
        for(int i = 0; i<tabela.size; i++)
        {
            Nod *aux = tabela.vector[i];
            while(aux != NULL)
            {
                if(aux->info.prioritate_id == id){
                    return initProdus(aux->info.prioritate_id, aux->info.nume,
                    aux->info.cantitate, aux->info.pret);
                    aux = aux->next;
                    }
            }
        }
        return initProdus(-1, "", 0, 0.0);
    }
    return initProdus(-1, "", 0, 0.0);
}

// hash to abc, avl, maxheap

void hashToABC(HashTable tabela, Nod **radacina){
    for(int i =0; i<tabela.size; i++){
        Nod *cap = tabela.vector[i];
        while(cap!=NULL){
            inserareInABC(radacina, cap->info);
            cap=cap->next;
        }
    }
}

void hashToAVL(HashTable tabela, Nod **radacina){
    for(int i=0; i<tabela.size; i++){
        Nod *cap = tabela.vector[i];
        while(cap!=NULL){
            inserareInAVL(radacina, cap->info);
            cap=cap->next;
        }
    }
}

void hashToMaxHeap(HashTable tabela, MaxHeap *heap){
    int k = 0;
    for(int i=0; i<tabela.size; i++){
        Nod *cap = tabela.vector[i];
        while(cap!=NULL){
            heap->vector[k++]=cap->info;
            cap=cap->next;
        }
    }
    heap->size=k;

    for(int i=heap->size/2-1; i>=0; i--){
        heapify(*heap, i);
    }
}

// avl to hash,, abc, maxheap
void AVltoHash(Nod *radacina, HashTable tabela){
    if(radacina!=NULL){
        AVltoHash(radacina->st, tabela);
        inserareInHashTable(tabela, radacina->info);
        AVltoHash(radacina->dr, tabela);
    }
}

void AVLtoABC(Nod *radAVL, Nod **radABC){
    if(radAVL){
    AVLtoABC(radAVL->st, radABC);
    inserareInABC(radABC, radAVL->info);
    AVLtoABC(radAVL->dr, radABC);
    }
}

void AVLtoMaxHeap(Nod *radAVl, MaxHeap *heap){
    if(radAVl){
        AVLtoMaxHeap(radAVl->st, heap);
        (*heap).vector[(*heap).size]=radAVl->info;
        (*heap).size++;
        AVLtoMaxHeap(radAVl->dr, heap);
    }
}

// abc to hash, avl, maxheap la fel ca AVL

void ABCtoAVl(Nod *radABC, Nod **radAVL){
    if(radABC){
        ABCtoAVl(radABC->st, radAVL);
        inserareInAVL(radAVL, radABC->info);
        ABCtoAVl(radABC->dr, radAVL);
    }
}

// maxheap to hash, abc, avl

void heapToHash(MaxHeap heap, HashTable tabela){
    for(int i=0; i<heap.size; i++){
        inserareInHashTable(tabela, heap.vector[i]);
    }
}

void heapToABC(MaxHeap heap, Nod **radacina){
    for(int i=0; i<heap.size; i++){
        inserareInABC(radacina, heap.vector[i]);
    }
}

void heapToAVL(MaxHeap heap, Nod **radacina)
{
    for (int i = 0; i < heap.size; i++)
    {
        inserareInAVL(radacina, heap.vector[i]);
    }
}


int main()
{
        // Initializare date
        Produs produse[] = {
            initProdus(5, "Faina", 100, 10.0),
            initProdus(3, "Oua", 50, 5.0),
            initProdus(7, "Branza", 30, 20.0),
            initProdus(1, "Lapte", 200, 8.0),
            initProdus(9, "Carne", 20, 50.0),
            initProdus(2, "Ulei", 80, 12.0),
            initProdus(6, "Zahar", 150, 7.0),
        };
        int n = 7;

        // ── HashTable ──────────────────────────────────────────
        HashTable tabela = initTabela(5);
        for (int i = 0; i < n; i++)
            inserareInHashTable(tabela, produse[i]);

        printf("\n=== Hash Table ===");
        afisareTabela(tabela);

        // Hash → ABC
        Nod *radABC = NULL;
        hashToABC(tabela, &radABC);
        printf("\n=== Hash -> ABC (inordine) ===");
        parcurgereInOrdine(radABC);

        // Hash → AVL
        Nod *radAVL = NULL;
        hashToAVL(tabela, &radAVL);
        printf("\n=== Hash -> AVL (inordine) ===");
        parcurgereInOrdine(radAVL);

        // Hash → MaxHeap
        MaxHeap heapDinHash;
        heapDinHash.size = 0;
        heapDinHash.vector = (Produs *)malloc(sizeof(Produs) * n);
        hashToMaxHeap(tabela, &heapDinHash);
        printf("\n=== Hash -> MaxHeap ===");
        parcurgereMaxHeap(heapDinHash);

        // ── AVL → altele ───────────────────────────────────────
        // AVL → Hash
        HashTable tabelaDinAVL = initTabela(5);
        AVltoHash(radAVL, tabelaDinAVL);
        printf("\n=== AVL -> Hash ===");
        afisareTabela(tabelaDinAVL);

        // AVL → ABC
        Nod *radABCdinAVL = NULL;
        AVLtoABC(radAVL, &radABCdinAVL);
        printf("\n=== AVL -> ABC (inordine) ===");
        parcurgereInOrdine(radABCdinAVL);

        // AVL → MaxHeap
        MaxHeap heapDinAVL;
        heapDinAVL.size = 0;
        heapDinAVL.vector = (Produs *)malloc(sizeof(Produs) * n);
        AVLtoMaxHeap(radAVL, &heapDinAVL);
        // build-heap după populare
        for (int i = heapDinAVL.size / 2 - 1; i >= 0; i--)
            heapify(heapDinAVL, i);
        printf("\n=== AVL -> MaxHeap ===");
        parcurgereMaxHeap(heapDinAVL);

        // ── ABC → altele ───────────────────────────────────────
        // ABC → AVL
        Nod *radAVLdinABC = NULL;
        ABCtoAVl(radABC, &radAVLdinABC);
        printf("\n=== ABC -> AVL (inordine) ===");
        parcurgereInOrdine(radAVLdinABC);

        // ── MaxHeap → altele ───────────────────────────────────
        // MaxHeap → Hash
        HashTable tabelaDinHeap = initTabela(5);
        heapToHash(heapDinHash, tabelaDinHeap);
        printf("\n=== MaxHeap -> Hash ===");
        afisareTabela(tabelaDinHeap);

        // MaxHeap → ABC
        Nod *radABCdinHeap = NULL;
        heapToABC(heapDinHash, &radABCdinHeap);
        printf("\n=== MaxHeap -> ABC (inordine) ===");
        parcurgereInOrdine(radABCdinHeap);

        // MaxHeap → AVL
        Nod *radAVLdinHeap = NULL;
        heapToAVL(heapDinHash, &radAVLdinHeap);
        printf("\n=== MaxHeap -> AVL (inordine) ===");
        parcurgereInOrdine(radAVLdinHeap);

        // ── Cautari ────────────────────────────────────────────
        printf("\n=== Cautare id=3 in Hash ===");
        afisareProdus(cautaProdus(tabela, 3));

        printf("\n=== Cautare id=7 in ABC ===");
        afisareProdus(cautaraDupaIdABC(radABC, 7));

        // ── Dezalocari ─────────────────────────────────────────
        dezalocareTabela(tabela);
        dezalocareTabela(tabelaDinAVL);
        dezalocareTabela(tabelaDinHeap);
        dezalocareABC(&radABC);
        dezalocareABC(&radABCdinAVL);
        dezalocareABC(&radABCdinHeap);
        dezalocareABC(&radAVL);
        dezalocareABC(&radAVLdinABC);
        dezalocareABC(&radAVLdinHeap);
        dezalocareHeap(heapDinHash);
        dezalocareHeap(heapDinAVL);

        for (int i = 0; i < n; i++)
            free(produse[i].nume);

        return 0;
    }
