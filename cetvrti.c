#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct Cvor *Position;
struct Cvor {
	int Koef;
	int Pot;
	Position Next;
};
int Unos(Position, int, int);
int produkt(Position, Position, Position);
int ispis(Position);
int suma(Position, Position, Position);
int CitajIzDatoteke(char *, Position);

int main(void) {
	struct Cvor P1;
	P1.Next = NULL;

	struct Cvor P2;
	P2.Next = NULL; 
	
	struct Cvor S;
	S.Next = NULL;
	
	struct Cvor P;
	P.Next = NULL;

	int check = 0;
	check = CitajIzDatoteke("polinomp.txt", &P1);

	if (check != 0)
		return 1;
	printf("Polinom p procitan iz datoteke\n\n");

	check = 0;
	check = CitajIzDatoteke("polinomq.txt", &P2);

	if (check != 0)
		return 1;
	printf("Polinom q procitan iz datoteke\n\n");

	printf("Polinom P: ");
	ispis(P1.Next);
	puts("");
	printf("Polinom Q: ");
	ispis(P2.Next);
	puts("");
	printf("Suma: ");
	suma(P1.Next, P2.Next, &S); 
	ispis(S.Next);
	puts("");
	printf("Produkt: ");
	produkt(P1.Next, P2.Next, &P);
	ispis(P.Next);
	puts("");
	puts("");
	return 0;
}

int Unos(Position P, int koef, int pot) {
	Position q;
	q = (struct Cvor*)malloc(sizeof(struct Cvor));

	while (P->Next != NULL && P->Next->Pot > pot)
		P = P->Next;

	if (P->Next != NULL && P->Next->Pot == pot)
		P->Next->Koef += koef;

	else {
		q->Koef = koef;
		q->Pot = pot;

		q->Next = P->Next;
		P->Next = q;
	}
	return 0;
}
int produkt(Position P1, Position P2, Position P) {
	Position poc = P2;
	while (P1 != NULL) {
		while (P2 != NULL) {
			Unos(P, P1->Koef* P2->Koef, P1->Pot + P2->Pot);
			P2 = P2->Next;

		}
		P1 = P1->Next;
		P2 = poc;
	}
	return 0;
}
int ispis(Position P) {
	while(P!= NULL){
		printf("%dx^%d ", P->Koef, P->Pot);
		if (P->Next != NULL)
			printf("+ ");
		P = P->Next;
	}
	return 0;
}

int suma(Position P1, Position P2, Position S) {
	Position temp = NULL;
	while (P1 != NULL && P2 != NULL) {
		if (P1->Pot == P2->Pot) {
			Unos(S, P1->Koef + P2->Koef, P1->Pot);
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->Pot > P2->Pot) {
			Unos(S, P1->Koef, P1->Pot);
			P1 = P1->Next;
		}
		else {
			Unos(S, P2->Koef, P2->Pot);
			P2 = P2->Next;
		}
	}
	if (P1 == NULL)
		temp = P2;
	else if (P2 == NULL)
		temp = P1;
	while (temp != NULL) {
		Unos(S, temp->Koef, temp->Pot);
		temp = temp->Next;
	}
	return 0;
}
int CitajIzDatoteke(char *FileName, Position P) {
	
	FILE *in = NULL;
	char trash1[50] = { '\0' };
	char trash2[50] = { '\0' };

	in = fopen(FileName, "r");
	if (in == NULL)
		return -1;

	fscanf(in, " %s %s", trash1, trash2);

	while (!feof(in)){
		fscanf(in, " %d %d ", &P->Koef, &P->Pot);
		Unos(P, P->Koef, P->Pot);	
	}
	return 0;
}
