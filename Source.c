#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define N 130


typedef struct Cvor *Position;

struct Cvor {
	char ime[N];
	char prezime[N];
	int godina_rodenja;
	Position Next;

};

void Dodaj_Na_Pocetak(char[], char[],int, Position);
void Dodaj_Na_Kraj(char[], char[], int, Position);
void Ispis(Position);
Position Trazi_Element_Po_Prezimenu(char[], Position);
Position Trazi_Prethodni(int, Position);
void Brisi(int, Position);
void ispisi_trazeni_element(Position);
void dealociranje(Position);

int main(void) {
	struct Cvor head;
	head.Next = NULL;

	char name[N], surname[N];
	int yob = 0;

	Position t;

	int odabir = 1;
	
	while (odabir != 0) {
		printf("\t\t2.zadatak SP\n");
		printf("Unos na pocetak(press 1): ");
		printf("\nUnos na kraj(press 2): ");
		printf("\nIspis liste (press 3): ");
		printf("\nPronalazak elementa po prezimenu(press 4): ");
		printf("\nBrisanje elementa iz liste (press 5): ");
		printf("\nZavrsetak programa(press 0):\n ");
		printf("\n\tODABIR: ");
		scanf("%d", &odabir);
		if (odabir == 1) {
			printf("Ime, prezime, godina rodenja: ");
			scanf(" %s %s %d", name, surname, &yob);
			Dodaj_Na_Pocetak(name, surname, yob, &head);
		}
		else if (odabir == 2) {
			printf("Ime, prezime, godina rodenja: ");
			scanf(" %s %s %d", name, surname, &yob);
			Dodaj_Na_Kraj(name, surname, yob, &head);
		}
		else if (odabir == 3) {
			Ispis(head.Next);
		}
		else if (odabir == 4) {
			printf("Koje prezime zelite pronaci: ");
			scanf(" %s", surname);
			t = Trazi_Element_Po_Prezimenu(surname, head.Next);
			ispisi_trazeni_element(t);
		}
		else if (odabir == 5) {
			printf("Unesite godinu rodenja osobe koju zelite izbriati: ");
			scanf("%d", &yob);
		    Brisi(yob, &head);
			Ispis(head.Next);
		}
		else {
			if(odabir != 0)
				printf("Pokusajte ponovo: ");
		}
	}


	free(t);

	dealociranje(&head);
	

	return 0;
}

void Dodaj_Na_Pocetak(char x[], char y[], int z, Position P) {
	Position q;
	q = (struct Cvor*) malloc(sizeof(struct Cvor));
	strcpy(q->ime, x);
	strcpy(q->prezime, y);
	q->godina_rodenja = z;

	q->Next = P->Next;
	P->Next = q;
};

void Dodaj_Na_Kraj(char x[], char y[], int z, Position P) {

	Position q;
	q = (struct Cvor*) malloc(sizeof(struct Cvor));
	strcpy(q->ime, x);
	strcpy(q->prezime, y);
	q->godina_rodenja = z;

	while (P->Next != NULL)
		P = P->Next;

	q->Next = P->Next;
	P->Next = q;
};


void Ispis(Position P) {
	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->godina_rodenja);
		P = P->Next;
	}
};
Position Trazi_Element_Po_Prezimenu(char x[], Position P) {
	while (NULL != P && strcmp(P->prezime, x))
		P = P->Next;

	return P;
};
Position Trazi_Prethodni(int x, Position P) {

	while (P->Next != NULL && P->Next->godina_rodenja != x)
		P = P->Next;

	if (P->Next == NULL)
		return NULL;

	else 
		return P;

};
void Brisi(int x, Position P) {
		
	Position temp;
	P = Trazi_Prethodni(x, P);

	if (P == NULL)
		printf("Ne postoji\n");

	else {
		temp = P->Next;
		P->Next = P->Next->Next;
		free(temp);
	}

};
void ispisi_trazeni_element(Position P) {
	printf("\n\n%s %s %d\n", P->ime, P->prezime, P->godina_rodenja);
}
void dealociranje(Position P) {
	Position temp;
	while (P->Next != NULL) {
		temp = P->Next;
		P->Next = P->Next->Next;
		free(temp);
	}
}