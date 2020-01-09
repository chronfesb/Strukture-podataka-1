#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct CvorStablo *Stablo;
typedef struct CvorStablo *Position;

struct CvorStablo {
	int El;
	Stablo L;
	Stablo D;
};
Stablo dodaj(int, Stablo);
void preorder_ispis(Stablo);
void postorder_ispis(Stablo);
void inorder_ispis(Stablo);
Position brisi(int, Stablo);
Position trazi(int, Stablo);
Position traziMin(Stablo);
Position traziMax(Stablo);
Stablo brisiSve(Stablo);

void myflush() {
	char c = 0;
	printf("Please, press any key to continue!\n");
	while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
	Stablo root = NULL;
	Position pom = NULL;

	int odabir = 0;
	int check = 0;
	int num = 0;
	int brojac = 0;
	int odabir_ispisa = 0;
	char arr;
	int a = 0;

	printf("\t9.zadatak\n");
	printf("Unosenje novog elementa u stablo (1)\n");
	printf("Ispis elemenata stabla (2)\n");
	printf("Brisanje elementa stabla (3)\n");
	printf("Pronalazenje elementa stabla (4)\n");
	printf("Pronalazenje najmanjeg elementa stabla(5)\n");
	printf("Pronalazenje najveceg elementa stabla(6)\n");
	printf("Brisanje cijelog stabla(7)\n");
	printf("Izlaz (0)\n");


	do {
		printf("\tODABIR:");
		scanf(" %d", &odabir);

		if (odabir == 1) {

			while (1) {
				myflush();
				char buffer[11] = { 0 };

				puts("Koji element zelite dodati: ");

				fgets(buffer, 10, stdin);

				int numOfNumbersFilled = 0;
				numOfNumbersFilled = sscanf(buffer, " %d", &num);
				myflush();

				if (numOfNumbersFilled == 1) break;
				puts("Not a num");
			}
			root = dodaj(num, root);
		}
		else if (odabir == 2) {
			if (root == NULL) {
				printf("Stablo je prazno\n");
				continue;
			}
			else {
				printf("\tPreorder ispis(1)\n");
				printf("\tPostorder ispis(2)\n");
				printf("\tInorder ispis(3)\n");
				printf("\t\tIzbor ispisa: ");
				scanf(" %d", &odabir_ispisa);

				if (odabir_ispisa == 1)
					preorder_ispis(root);
				else if (odabir_ispisa == 2)
					postorder_ispis(root);
				else if (odabir_ispisa == 3)
					inorder_ispis(root);
				else {
					puts("Wrong input..\n");
					continue;
				}
				puts("");
			}
		}
		else if (odabir == 3) {
			puts("Koji element zelite obrisati: ");
			scanf(" %d", &num);
			root = brisi(num, root);
			printf("Gotov sam sa brisanjem\n");
		}
		else if (odabir == 4) {
			puts("Koji element zelite pronaci: ");
			scanf(" %d", &num);
			trazi(num, root);
		}
		else if (odabir == 5)
			traziMin(root);
		else if (odabir == 6)
			traziMax(root);
		else if (odabir == 7) {
			root = brisiSve(root);
			puts("Stablo je izbrisano");
		}
		else if (odabir == 0) {
			puts("The end");
			return 0;
		}
		else {
			puts("Wrong input");
			return 0;
		}
	} while (odabir != 0);


	free(pom);
	root = brisiSve(root);
	return 0;
}
Stablo dodaj(int x, Stablo S) {
	Position temp = NULL;

	if (S == NULL) {
		S = (struct CvorStablo *)malloc(sizeof(struct CvorStablo));
		S->El = x;
		S->D = NULL;
		S->L = NULL;
		printf("Root element: %d\n", S->El);
	}
	else {
		if (x < S->El) {
			if (S->L != NULL) {
				S->L = dodaj(x, S->L);
			}
			else {
				temp = (struct CvorStablo*)malloc(sizeof(struct CvorStablo));
				temp->L = NULL;
				temp->D = NULL;
				S->L = temp;
				S->L->El = x;
				printf("%d je manji od %d,dodajem ga lijevo\n", S->L->El, S->El);
			}
		}
		else if (x > S->El) {
			if (S->D != NULL)
				S->D = dodaj(x, S->D);
			else {
				temp = (struct CvorStablo*)malloc(sizeof(struct CvorStablo));
				temp->L = NULL;
				temp->D = NULL;
				S->D = temp;
				temp->El = x;
				printf("%d je veci od %d, dodajem ga desno\n", S->D->El, S->El);
			}
		}
	}
	return S;
}
void preorder_ispis(Stablo S) { //trenutni cvor,lijevo podstablo,desno podstablo
	if (S == NULL)
		return;
	printf("%d ", S->El);

	preorder_ispis(S->L);

	preorder_ispis(S->D);
}
void postorder_ispis(Stablo S) { //lijevo podstablo,desno podstablo,trenutni cvor
	if (S == NULL)
		return;

	preorder_ispis(S->L);

	preorder_ispis(S->D);

	printf("%d ", S->El);
}
void inorder_ispis(Stablo S) {
	if (S == NULL)
		return;

	preorder_ispis(S->L);

	printf("%d ", S->El);

	preorder_ispis(S->D);
}
Position brisi(int x, Stablo S) {
	Position temp = NULL;
	if (S == NULL)
		printf("Nema ga\n");
	else {
		if (x < S->El)
			S->L = brisi(x, S->L);
		else if (x > S->El)
			S->D = brisi(x, S->D);
		else {
			if (!(S->L != NULL && S->D != NULL)) { // ima 0 ili 1 djece
				temp = S;
				if (S->L == NULL)
					S = S->D;
				else
					S = S->L;
				free(temp);
			}
			else {  //ima 2 djece
				temp = traziMin(S->D);
				S->El = temp->El;

				S->D = brisi(S->El, S->D);
			}
		}
	}
	return S;
}
Position trazi(int x, Stablo S) {
	if (S == NULL) {
		puts("Nema trazenog elementa");
		return NULL;
	}
	else {
		if (x < S->El) {
			return trazi(x, S->L);
		}
		else if (x > S->El) {
			return trazi(x, S->D);
		}
		printf("Nasao sam trazeni element i to je %d\n", S->El);
		return S;
	}
}
Position traziMin(Stablo S) {
	if (S == NULL) {
		puts("Stablo je prazno");
		return NULL;
	}
	else {
		if (S->L != NULL)
			return traziMin(S->L);
		printf("Najmanji element je %d\n", S->El);
		return S;
	}
}
Position traziMax(Stablo S) {
	if (S == NULL) {
		puts("Stablo je prazno\n");
		return NULL;
	}
	else {
		if (S->D != NULL)
			return traziMax(S->D);
		printf("Najveci je %d\n", S->El);
		return S;
	}
}
Stablo brisiSve(Stablo S) {
	if (S != NULL) {
		brisiSve(S->L);
		brisiSve(S->D);
		free(S);
	}
	return NULL;
}