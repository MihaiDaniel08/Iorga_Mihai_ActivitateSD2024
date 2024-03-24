#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include < stdlib.h>


struct Masina {

	int id;
	char* producator;
	int nrUsi;
	float pret;

};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {

	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));

	for (int i = 0; i < (*nrMasini); i++) {
		aux[i] = masini[i];
	}

	aux[(*nrMasini)] = m;
	(*nrMasini)++;

	if (aux != NULL)
		free(masini);

	return aux;

}


struct Masina* citireFisier(const char* numef, int* nrMasini) {

	FILE* file = fopen(numef, "r");

	//fscanf citeste pana la spatiu, fgets citeste o linie intreaga
	char buffer[100];
	struct Masina* masini = NULL;

	while (fgets(buffer, 100, file) != NULL)
	{
		struct Masina m;
		char delimitator[] = ",\n";
		char* element = strtok(buffer, delimitator);
		m.id = atoi(element);

		element = strtok(NULL, delimitator);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);

		element = strtok(NULL, delimitator);
		m.nrUsi = atoi(element);

		element = strtok(NULL, delimitator);
		m.pret = atof(element);
		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(file);
	return masini;
}

void afisare(struct Masina m) {

	printf("\nID: %d", m.id);
	printf("\nProducator: %s", m.producator);
	printf("\nNumar usi: %i", m.nrUsi);
	printf("\nPret: %.2f\n", m.pret);

}


struct Masina* selectareNrUsi(struct Masina* masini, int nrMasini, int nrUsi, int* nrMasiniNoi) {

	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrUsi == nrUsi) {
			(*nrMasiniNoi)++;
		}
	}
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniNoi));

	int j = 0;
	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrUsi == nrUsi) {
			aux[j] = masini[i];
			j++;
		}
	}

	return aux;
}



int main() {

	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);

	for (int i = 0; i < nrMasini; i++)
	{
		afisare(masini[i]);

	}

	printf("\n***************************************");
	struct Masina* masiniDupaUsi = NULL;
	int nrMasiniNoi = 0;
	masiniDupaUsi = selectareNrUsi(masini, nrMasini, 4, &nrMasiniNoi);
	for (int i = 0; i < nrMasiniNoi; i++)
	{
		afisare(masiniDupaUsi[i]);

	}


}