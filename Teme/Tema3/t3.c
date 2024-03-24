#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include < stdlib.h> //ca sa mearga atof!!!!


struct Masina {

	char* nume;
	int nrKm;
	int caiPutere;
	float pret;

};


struct Masina createMasina(const char* nume, int nrKm, int caiPutere, float pret) {

	struct Masina m;
	m.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(m.nume, nume);
	m.nrKm = nrKm;
	m.caiPutere = caiPutere;
	m.pret = pret;

	return m;
}

void afisare_masina(struct Masina m) {

	printf("Nume: %s\n", m.nume);
	printf("Kilometri: %i\n", m.nrKm);
	printf("Cai putere: %i\n", m.caiPutere);
	printf("Pretul: %.2f\n", m.pret);

}

//functie ce realizeaza concatenarea a doi vectori
struct Masina* concatVector(struct Masina* v1, int nrv1, struct Masina* v2, int nrv2, int* nrv3) {

	(*nrv3) = nrv1 + nrv2;
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * (*nrv3));
	int j = 0;
	for (int i = 0; i < nrv1; i++) {
		aux[j] = v1[i];
		j++;
	}

	for (int i = 0; i < nrv2; i++) {
		aux[j] = v2[i];
		j++;
	}
	return aux;
}



void copyVector(struct Masina* masini, int nrMasini, struct Masina** vectorNou,int* nrMasiniNou) {

	(*nrMasiniNou) = nrMasini;
	(*vectorNou) = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniNou));
	
	for (int i = 0; i < nrMasini; i++) {
		(*vectorNou)[i].nume = (char*)malloc(sizeof(char)*strlen(masini[i].nume) + 1);
		strcpy((*vectorNou)[i].nume, masini[i].nume);
		(*vectorNou)[i].nrKm = masini[i].nrKm;
		(*vectorNou)[i].caiPutere = masini[i].caiPutere;
		(*vectorNou)[i].pret = masini[i].pret;
		
	}
}



void adaugareInVector(struct Masina** m, int* nrMasini, struct Masina element) {


	struct Masina* aux = NULL;
	int nrAux;
	copyVector((*m), (*nrMasini), &aux, &nrAux);
	(*nrMasini)++;
	for (int i = 0; i < (*nrMasini) - 1; i++) {
		free((*m)[i].nume);
	}
	free((*m));

	(*m) = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasini));


	for (int i = 0; i < nrAux; i++) {
		(*m)[i].nume = (char*)malloc(sizeof(char) * strlen(aux[i].nume) + 1);
		strcpy((*m)[i].nume, aux[i].nume);
		(*m)[i].nrKm = aux[i].nrKm;
		(*m)[i].caiPutere = aux[i].caiPutere;
		(*m)[i].pret = aux[i].pret;

	}
	(*m)[(*nrMasini)-1].nume = (char*)malloc(sizeof(char) * strlen(element.nume) + 1);
	strcpy((*m)[(*nrMasini)-1].nume, element.nume);
	(*m)[(*nrMasini)-1].nrKm = element.nrKm;
	(*m)[(*nrMasini)-1].caiPutere = element.caiPutere;
	(*m)[(*nrMasini)-1].pret = element.pret;


	for (int i = 0; i < nrAux; i++) {
		free(aux[i].nume);
	}
	free(aux);

}

struct Masina* citireFisier(const char* numef, int* nrMasini) {


	FILE* file = fopen(numef, "r");
	char buffer[100];
	struct Masina* aux = NULL;
	struct Masina m;

	while (fgets(buffer, 100, file) != NULL) {
		char delimitator[] = ",\n";
		char* element = strtok(buffer, delimitator);
		m.nume = malloc(strlen(element) + 1);
		strcpy(m.nume, element);

		element = strtok(NULL, delimitator);
		m.nrKm = atoi(element);

		element = strtok(NULL, delimitator);
		m.caiPutere = atoi(element);

		element = strtok(NULL, delimitator);
		m.pret = atof(element);
		
		adaugareInVector(&aux, nrMasini, m);

	}
	fclose(file);
	return aux;

}

//printf("Nume: %s\n", m.nume);
//printf("Kilometri: %i\n", m.nrKm);
//printf("Cai putere: %i\n", m.caiPutere);
//printf("Pretul: %.2f\n", m.pret);

void masinaToFisier(const char* numef, struct Masina m) {

	FILE* file = fopen(numef, "w");

	if (file == NULL) {

		printf("Eroare la deschiderea fisierului text!");
	}
	else {
		fprintf(file,"%s,%i,%i,%.2f,\n", m.nume, m.nrKm, m.caiPutere, m.pret);
		fclose(file);
	}

}

void vectorToFisier(const char* numef, struct Masina* m, int nrMasini) {

	FILE* file = fopen(numef, "w");

	if (file == NULL) {
		printf("EROARE!");
	}
	else
	{
		for (int i = 0; i < nrMasini; i++) {
			fprintf(file, "%s,%i,%i,%.2f,\n", m[i].nume, m[i].nrKm, m[i].caiPutere, m[i].pret);
		}
		fclose(file);
	}

}


//functie ce afiseaza un vector de obiecte
void display_vector(struct Masina* m, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_masina(m[i]);
		printf("\n");
	}
}


int main() {


	printf("***********************Fisiere************************\n");

	struct Masina* masiniFisier = NULL;
	int nrMasiniFisier = 0;
	masiniFisier = citireFisier("masini.txt", &nrMasiniFisier);
	display_vector(masiniFisier, nrMasiniFisier);

	struct Masina masinuta = createMasina("Opel", 2000, 100, 15000);
	masinaToFisier("scriere.txt", masinuta);

	vectorToFisier("vectorF.txt", masiniFisier, nrMasiniFisier);

}