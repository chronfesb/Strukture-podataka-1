#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MIN 10
#define MAX 100

typedef struct Cvor *Position;
struct Cvor{
	int El;
	Position Next;
};

int ispis(Position);
int push_stog(Position,int);
int push_red(Position,int);
int pop(Position);
int dealociranje(Position);
int slucajni_broj();
int postoji_li(Position,int);

int main(void){
	struct Cvor headS;
	struct Cvor headR;
	int odabir = 0;
	int broj =0;

	headS.Next = NULL;
	headR.Next = NULL;

	printf("\t\tSesti zadatak\n");
	printf("Push na stog (1)\n");
	printf("Pop sa stoga (2)\n");
	printf("Push na red (3)\n");
	printf("Pop sa reda (4)\n");
	printf("Izlaz (0)\n");
	do{
		printf("\tODABIR: ");
		scanf(" %d",&odabir);
		if(odabir == 1){
			while(broj == 0 || postoji_li(headS.Next,broj))
				broj = slucajni_broj();	
			push_stog(&headS,broj);
			broj = 0;
			ispis(headS.Next);
		}
		else if(odabir == 2){
			pop(&headS);
			ispis(headS.Next);
		}
		else if(odabir == 3){
			while(broj == 0 || postoji_li(headR.Next,broj))
				broj = slucajni_broj();	
			push_red(&headR,broj);
			broj = 0;
			ispis(headR.Next);
		}
		else if(odabir == 4){
			pop(&headR);
			ispis(headR.Next);
		}
		else{
			if(odabir != 0)
				puts("Wrong input");
		}
	}while(odabir!=0);

	dealociranje(&headS);
	dealociranje(&headR);
	return 0;
}
int slucajni_broj(){
	return rand() % (MAX-MIN) + MIN;
}
int postoji_li(Position P ,int x){
	while(P!=NULL && P->El != x)
		P= P->Next;
	if(P!=NULL)
		return 1;
	else
		return 0;
}
int ispis(Position P){
	Position element = NULL;

	while(P!=NULL){
		printf("%d\n",P->El);
		P = P->Next;
	}
	return 0;
}
int push_stog(Position S,int x){
	Position q;
	q = (struct Cvor *)malloc(sizeof(struct Cvor));

	q->El = x;

	q->Next = S->Next;
	S->Next = q;

	return 0;
}

int push_red(Position R,int x){
	Position q;
	q = (struct Cvor *)malloc(sizeof(struct Cvor));

	while(R->Next != NULL)
		R = R->Next;

	q->El = x;

	q->Next = R->Next;
	R->Next = q;

	return 0;
}
int pop(Position P){
	Position temp;

	if(P->Next != NULL){
		temp = P->Next;
		P->Next = P->Next->Next;

		printf("Brise se: %d\n", temp->El);
		free(temp);
	}
	else
		printf("Lista je prazna\n");

	return 0;
}
int dealociranje(Position P){
	Position temp;
	while(P->Next != NULL){
		temp = P->Next;
		P->Next = P->Next->Next;
		free(temp);
	}
	return 0;
}
