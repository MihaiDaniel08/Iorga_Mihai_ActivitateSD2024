#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


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

void marire_pret(struct Masina* m) {

	m->pret = m->pret * 1.1;

}

void setNume(struct Masina* m, const char* numeNou) {

	free(m->nume);
	m->nume = (char*)malloc(sizeof(char) * strlen(numeNou) + 1);
	strcpy(m->nume, numeNou);
}

//functie ce creeaza un vector de obiecte cu cele care au numarul de kilometri <= nrKm
struct Masina* createVectorKM(struct Masina* masini,int nrMasini,int nrKm,int* nrMasiniConditie,struct Masina* masiniCond) {

	

	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrKm <= nrKm)
		{
			(*nrMasiniConditie)++;
		}
	}
	masiniCond = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniConditie));
	int j = 0;

	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrKm <= nrKm) {
			masiniCond[j] = masini[i];
			j++;
		}
	}
	return masiniCond;
	
}

//functie ce creaza un nou vector de obiecte cu cele care au pretul <= pret
struct Masina* creareVectorPret(struct Masina* masini, int nrMasini, int pret, int* nrMasiniConditie) {

	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].pret <= pret)
		{
			(*nrMasiniConditie)++;
		}
	}
	struct Masina* masiniCond = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniConditie));
	int j = 0;

	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].pret <= pret) {
			masiniCond[j] = masini[i];
			j++;
		}
	}
	return masiniCond;

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


//functie ce afiseaza un vector de obiecte
void display_vector(struct Masina* m, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_masina(m[i]);
		printf("\n");
	}
}


int main() {
	
	struct Masina masina1 = createMasina("Ford", 20000, 120, 24999.99);
	struct Masina masina2 = createMasina("Logan", 80000, 60, 4999.99);
	struct Masina masina3 = createMasina("Mazda", 35000, 100, 13000);
	struct Masina masina4 = createMasina("BWM", 8000, 320, 24999.99);
	struct Masina masina5 = createMasina("Aro", 200000, 40, 1000);

	int nrMasini = 5;
	struct Masina* masini = (struct Masina*)malloc(sizeof(struct Masina) * nrMasini);
	masini[0] = masina1;
	masini[1] = masina2;
	masini[2] = masina3;
	masini[3] = masina4;
	masini[4] = masina5;

	display_vector(masini, nrMasini);

	printf("******************************************************\n");
	struct Masina* masiniCond = NULL;
	int nrMasiniConditie = 0;
	int kilometri = 30000;
	masiniCond = createVectorKM(masini, nrMasini, kilometri, &nrMasiniConditie, masiniCond);
	display_vector(masiniCond, nrMasiniConditie);

	printf("******************************************************\n");
	struct Masina* masiniPret = NULL;
	int nrMasiniPret = 0;
	int pret = 10000;
	masiniPret = creareVectorPret(masini, nrMasini, pret, &nrMasiniPret);
	display_vector(masiniPret,nrMasiniPret);


	printf("**************************CONCAT**********************\n");

	struct Masina* concatenare = NULL;
	int marimeConcatenare = 0;
	concatenare = concatVector(masiniCond, nrMasiniConditie, masiniPret, nrMasiniPret, &marimeConcatenare);
	display_vector(concatenare, marimeConcatenare);


}