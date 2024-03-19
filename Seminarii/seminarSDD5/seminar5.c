// vector -> zona de memorie contigua -> adica elem sunt stocate in memorie unul dupa altul
// lista nu stocheaza elementele unul dupa altul, deci la fiecare nod trb sa salvam adresa urmatorului nod
// ultimul nod are ultima pozitie null

//exista 3 moduri de inserare intr-o lista:
		//la inceput
		//la sfarsit
		//la mijloc

// primul nod => capul listei => pentru a avea acces la toata lista, incepem prin adresa primului nod
// daca am avea initial adresa celului de al doilea nod, nu am mai avea acces la primul nod

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
typedef struct Nod Nod;

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct Nod {
	Santier santier;
	Nod* next;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(sizeof(char) * strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;

	return santier;
}

Nod* inserareInceput(Santier santier, Nod* lista) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->santier = santier; //facem shallow copy asumandu-ne ca nu mai folosim Santer santier transmis ca parametru
	nod->next = lista;

	return nod;
}

void afisareSantier(Santier santier) {
	printf("\nNume Proiect: %s", santier.numeProiect);
	printf("\nNumar muncitori: %i", santier.nrMuncitori);
	printf("\nSuprafata: %.2f\n", santier.suprafata);
}

void afisareLista(Nod* lista){
	while (lista != NULL) { //parcurgerea clasica pentru o lista simplu inlantiuta

		afisareSantier(lista->santier);
		lista = lista->next;
	}
}

int sumaNrMuncitori(Nod* lista) {
	int suma = 0;
	while (lista != NULL) { 

		suma += lista->santier.nrMuncitori;
		lista = lista->next;
	}
	return suma;
}

float densitateaMunctorilor(Santier santier) {
	if (santier.suprafata > 0) {
		return santier.nrMuncitori / santier.suprafata;
	}
	else {
		return 0;
	}
}

//char* numeSantierDensitateMaxima(Nod* lista) {
//	float max = 0;
//	char* aux = NULL;
//	while (lista != NULL) {
//		if (densitateaMunctorilor(lista->santier) > max) {
//			max = densitateaMunctorilor(lista->santier);
//			aux = lista->santier.numeProiect;
//		}
//		lista = lista->next;
//	}
//	char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
//	strcpy(numeProiectDensitate, aux);
//	return  numeProiectDensitate;
//}

void stergereLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->santier.numeProiect);
		Nod* aux = (*lista)->next;
		free(*lista);
		(*lista) = aux;

	}
	(*lista) = NULL;
}



void stergereLista2(Nod* lista) {  //de verificat
	while (lista != NULL) {
		free(lista->santier.numeProiect);
		Nod* aux = lista->next;
		free(lista);
		lista = aux;
	}
	lista = NULL; //daca fac varianta asta,in main lista nu va fi NULL, iar modificare va fi facuta doar pe lista
}


int main() {

	Nod* lista = NULL;

	Santier s1 = initializareSantier("Global Residence", 80, 3000);
	Santier s2 = initializareSantier("Dristor Project", 100, 2000);
	Santier s3 = initializareSantier("Militari Residence", 40, 1500);
	lista = inserareInceput(s1, lista);
	lista = inserareInceput(s2, lista);
	lista = inserareInceput(s3, lista);

	//lista = inserareInceput(initializareSantier("Gigel House", 10, 500), lista); //acest santier nu mai merge sters la sfarsit
																				//dar facand shallow copy stergem doar elementele listei
	afisareLista(lista);


	int totalMuncitori;
	totalMuncitori = sumaNrMuncitori(lista);
	printf("\nTotalul numarului de muncitori este: %i\n", totalMuncitori);

	stergereLista(&lista);
	//stergereLista2(lista);
	printf("\nNume Proiect: %s", s1.numeProiect);
	printf("\nNumar muncitori: %i", s1.nrMuncitori);
	printf("\nSuprafata: %.2f\n", s1.suprafata);
	if (lista == NULL)
		printf("\nLista este nula");
	else
		printf("\nLista nu este nula");

	/*char* nume = NULL;
	nume =*/

	return 0;
}

