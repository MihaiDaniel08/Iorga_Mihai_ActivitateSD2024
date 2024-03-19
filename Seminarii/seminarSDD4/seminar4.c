#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include < stdlib.h>


struct Maisna {

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


void citireMatrice(const char* numef,struct Masina** matrice, int* nrLinii,int* nrCol) {

	FILE* file = fopen(numef, "r");

	//fscanf citeste pana la spatiu, fgets citeste o linie intreaga
	char buffer[100];

	while (fgets(buffer, 100, file) != NULL)
	{
		char delimitator[] = ",\n";
		char* element = strtok(buffer, delimitator);

		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitator);

		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);

		element = strtok(NULL, delimitator);
		m.nrUsi = atoi(element);

		element = strtok(NULL, delimitator);
		m.pret = atof(element);
		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrCol[m.nrUsi - 2]));
	}
	fclose(file);
	
}



void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			printf("%i, %s, %i, %f		", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
		}
		printf("\n");
	}

}


//functie care calculeaza pretul mediu al masinulor cu numar de usi dat ca paramatru
float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {

	if (nrUsi <= 1 && nrUsi > 4) 
		return 0;
	else
	{
		float pretTotal = 0;
		int index = nrUsi - 2;
		if (nrColoane[index] == 0) 
			return 0;
		else
		{
			for (int i = 0; i < nrColoane[i]; i++) {
				pretTotal += (float)matrice[index][i].pret;
			}
			return (float)(pretTotal / nrColoane[index]); //cast la float optional, se va face oricum
		}
	}

}

//functie care cauta o masina dupa id

struct Masina cautareMasinaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			if (matrice[i][j].id == id)
				return matrice[i][j];
		}
	}

	struct Masina m;
	m.id = -1;
	m.producator = "";
	m.nrUsi = 0;
	m.pret = 0.0;
	return m;
}

//functie de dezalocare de memorie TIP: tot ce dezalocam e trimis cu o steluta in plus

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrCol)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < (*nrCol)[i]; j++)
		{
			free((*matrice)[i][j].producator);
		}
		free((*matrice)[i]);
	}
	free((*nrCol));
	(*nrCol) = NULL;
	free((*matrice));
	(*matrice) = NULL;
}


int main() {

	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	nrCol = (int*)malloc(sizeof(int)*nrLinii); //vectorul de lungimi
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrCol[i] = 0;
		matrice[i] = NULL;
	}
		
	citireMatrice("masini.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrLinii, nrCol);

	float pretMediuMatrice = pretMediu(matrice, nrLinii, nrCol, 2);
	printf("\nPretul mediu este: %.2f", pretMediuMatrice);

	dezalocareMatrice(&matrice, nrLinii, &nrCol);
}