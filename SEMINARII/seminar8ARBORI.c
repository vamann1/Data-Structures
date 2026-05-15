#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Nod Nod;

typedef struct Persoana {
	int id;
	char* nume;
	int varsta;
	float inaltime;
} Persoana;

struct Nod
{
	Persoana info;
	Nod* st;
	Nod* dr;
};

Persoana initPersoana(int id, const char* nume, int varsta, float inaltime) {
	Persoana p;
	p.id = id;
	p.varsta = varsta;
	p.inaltime = inaltime;
	p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(p.nume, nume);

	return p;
}

void afisarePersoana(Persoana persoana) {
	printf("%d. Nume: %s, varsta: %d, inaltime: %.2f.\n", persoana.id, persoana.nume, persoana.varsta, persoana.inaltime);
}

void inserareInBST(Nod** radacina, Persoana p) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->st = NULL;
		nou->dr = NULL;
		*radacina = nou;
	}
	else if (p.id < (*radacina)->info.id) {
		inserareInBST(&(*radacina)->st, p);
	}
	else {
		inserareInBST(&(*radacina)->dr, p);
	}
}

void inordine(Nod * rad) {
	if (rad) {
			inordine(rad->st);
		afisarePersoana(rad->info);
		inordine(rad->dr);
	}
}

void preordine(Nod* rad) {
	if (rad) {
		afisarePersoana(rad->info);
		preordine(rad->st);
		preordine(rad->dr);
	}
}

void postordine(Nod* rad) {
	if (rad) {
		postordine(rad->st);
		postordine(rad->dr);
		afisarePersoana(rad->info);
	}
}

Persoana cautarePersoanaById(Nod* rad, int id) {
	if (rad == NULL) {
		return initPersoana(-1, "", 0, 0);
	}
	else if (rad->info.id == id) {
		return initPersoana(rad->info.id, rad->info.nume, rad->info.varsta, rad->info.inaltime);
	}
	else if (id < rad->info.id) {
		return cautarePersoanaById(rad->st, id);
	}
	else {
		return cautarePersoanaById(rad->dr, id);
	}
}

void dezalocare(Nod** rad) {
	if (*rad) {
		dezalocare(&(*rad)->st);
		dezalocare(&(*rad)->dr);
		free((*rad)->info.nume);
		free(*rad);
	}
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(calculInaltimeArbore(rad->st), calculInaltimeArbore(rad->dr)) + 1;
	}
	return 0;
}

void main() {
	Nod* rad = NULL;
	inserareInBST(&rad, initPersoana(7, "Tudor", 20, 1.85));
	inserareInBST(&rad, initPersoana(5, "Vlad", 21, 1.80));
	inserareInBST(&rad, initPersoana(9, "Mihai", 22, 1.81));
	inserareInBST(&rad, initPersoana(3, "Ionut", 19, 1.82));
	inserareInBST(&rad, initPersoana(6, "Gabriel", 23, 1.83));
	inserareInBST(&rad, initPersoana(8, "Mihnea", 20, 1.79));
	inserareInBST(&rad, initPersoana(11, "Ana", 21, 1.80));

	printf("Parcurgere inordine: \n");
	inordine(rad);

	printf("Parcurgere preordine: \n");
	preordine(rad);

	printf("Parcurgere postordine: \n");
	postordine(rad);

	Persoana persCautata = cautarePersoanaById(rad, 6);
	printf("Persoana cautata: \n");
	afisarePersoana(persCautata);
	free(persCautata.nume);

	printf("\nInaltime arbore: %d", calculInaltimeArbore(rad));

	dezalocare(&rad);
}