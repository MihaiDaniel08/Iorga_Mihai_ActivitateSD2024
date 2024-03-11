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

void setNume(struct Masina *m, const char* numeNou) {

	free(m->nume);
	m->nume = (char*)malloc(sizeof(char) * strlen(numeNou) + 1);
	strcpy(m->nume, numeNou);
}


int main() {

	struct Masina masina1 = createMasina("Ford", 20000, 120, 24999.99);
	afisare_masina(masina1);
	printf("\n");
 
	marire_pret(&masina1);
	afisare_masina(masina1);
	printf("\n");

	setNume(&masina1, "Logan");
	afisare_masina(masina1);
	printf("\n");
	
}