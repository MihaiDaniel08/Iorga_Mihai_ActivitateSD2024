#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;
};

struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata)
{
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;
}


void afisare_farmacie(struct Farmacie farmacie) {

	printf("%d. %s are o suprafata de %5.2f\n", farmacie.id, farmacie.nume, farmacie.suprafata);

}

void afisare_vector(struct Farmacie* farmacie, int nrFarmacii) {

	for (int i = 0; i < nrFarmacii; i++) {
		afisare_farmacie(farmacie[i]);
	}

}


struct Farmacie* copiazaNElemente(struct Farmacie* vectorInit, int nrFarmacii, int nrObiecte) {

	if (nrObiecte <= nrFarmacii && nrObiecte > 0) {

		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecte);

		for (int i = 0; i < nrObiecte; i++) {
			copiat[i] = initializareFarmacie(vectorInit[i].id, vectorInit[i].nume, vectorInit[i].suprafata);
		}

		return copiat;

	}
	else {

		return NULL;

	}

}



struct Farmacie* copiazaFarmaciiMici (struct Farmacie* farmacii, int nrFarmacii, int pragSuprafata, int* nrFarmaciiMici) {

	*nrFarmaciiMici = 0;
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < pragSuprafata) {
			(*nrFarmaciiMici)++;
		}
	}

	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici));
	int j = 0;
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < pragSuprafata) {

			vector[j] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
			j++;
			//se poate si vector[k++] = ...
		}
	}

	return vector;



}

struct Farmacie getFarmByID(struct Farmacie* vector, int nrFarmacii, int IDcautat) {

	for (int i = 0; i < nrFarmacii; i++) {

		if (vector[i].id == IDcautat) {
			return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}

	}
	return initializareFarmacie(0, "N/A", 0);

}

//functie de dezalocare
void dezalocareVectorFarmacii(struct Farmacie** vector,int* nrFarmacii) {	//** pentru ca trebuie sa dezalocam si vectorul in sine??
	
	for (int i = 0; i < (*nrFarmacii); i++) {
		free((*vector)[i].nume);
	}

	free(*vector);
	(*nrFarmacii) = 0;
	(*vector) = NULL;

}



int main() {

	/*int v1[40];
	int* v2;*/

	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);

	for (int i = 0; i < nrFarmacii; i++) {
		farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}

	afisare_vector(farmacii,4);


	int nrObiecteCopiate = 2;
	struct Farmacie* farmaciiCopiate = copiazaNElemente(farmacii, nrFarmacii, nrObiecteCopiate);

	printf("\n");
	afisare_vector(farmaciiCopiate, nrObiecteCopiate);

	farmacii[3].suprafata = 20;
	int prag = 80;
	int nrFarmaciiMici = 0;
	struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, prag, &nrFarmaciiMici);


	printf("\n");
	afisare_vector(farmaciiMici, nrFarmaciiMici);


	struct Farmacie f = getFarmByID(farmacii, nrFarmacii, 7);

	printf("\n");
	afisare_farmacie(f);
	free(f.nume);


	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
	dezalocareVectorFarmacii(&farmaciiCopiate, &nrObiecteCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);


}