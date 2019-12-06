/*Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Cvor *Position;
struct Cvor {
	int El;
	Position Next;
};
int push(int, Position);
int pop(Position,int*);
int dealociranje(Position);
int citaj_iz_dat(char*);
int ispis(Position);
int fja(char*);

int main(void) {
	int check = 0;
	check = citaj_iz_dat("ovo.txt");
	if (check != 0)
		printf("cant read the file\n");

	return 0;
}
int citaj_iz_dat(char* fn) {
	char *stringic = "";
	int vel = 0;

	FILE *in;
	in = fopen(fn, "r");
	if (in == NULL)
		return 1;

	fseek(in,0, SEEK_END);
	vel = ftell(in);
	rewind(in);

	stringic = (char*)malloc(vel * sizeof(char));
	fgets(stringic, vel, in);

	fja(stringic);

	fclose(in);
	free(stringic);
	return 0;
}
int fja(char* s) {
	struct Cvor head;
	head.Next = NULL;

	int i = 0;
	int a = 0, b = 0;
	int rez = 0;
	int num = 0;
	int brojac = 0;
	char zn = '\0';
	int x = 0;
	int*px = &x;
	
	while (s[i] != '\0') {
		rez = sscanf(s + i, " %d %n", &num, &brojac);
		if (rez==1) {
			printf("Dodajem %d na stog\n", num);
			push(num, &head);
		}
		else{
			rez = sscanf(s + i, " %c %n", &zn, &brojac);
			if (zn == '*') {
				printf("Znak * u postfixu:\n");
				pop(&head, px);
				b = (*px);
				pop(&head, px);
				a = (*px);
				push(a * b, &head);
			}
		
			else if (zn == '+') {
				printf("Znak + u postfixu:\n");
				pop(&head, px);
				b = (*px);
				pop(&head, px);
				a = (*px);
				push(a + b, &head);
			}
			else if (zn == '-') {
				printf("Znak - u postfixu:\n");
				pop(&head, px);
				b = (*px);
				pop(&head, px);
				a = (*px);
				push(a - b, &head);
			}
			else {
				printf("Unexpected sign\n");
				return 1;
			}
		}
		printf("\n-----------------------------------------------------------\n");
		i+=brojac;
	}

	dealociranje(&head);
	return 0;
}
int push(int x, Position P) {
	Position q;
	q = (struct Cvor*)malloc(sizeof(struct Cvor));
	q->El = x;

	q->Next = P->Next;
	P->Next = q;

	ispis(P);
	return 0;
}
int pop(Position P, int *pa) {
	Position temp;
	
	temp = P->Next;
	P->Next = P->Next->Next;

	printf("\nBrise se %d\n", temp->El);
	*pa = temp->El;

	free(temp);

	return 0;
}
int dealociranje(Position P) {
	Position temp;
	while (P->Next != NULL) {
		temp = P->Next;
		P->Next = P->Next->Next;
		free(temp);
	}
	return 0;
}
int ispis(Position P) {
	printf("\nTrenutno na stogu:\n");
	while (P->Next != NULL) {
		printf("%3d\n", P->Next->El);
		P = P->Next;
	}
	return 0;
}
