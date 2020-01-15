//nesto nece - treba dorada

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stablo *PosStablo;
typedef struct Stog *PosStog;

struct Stablo {
	char op[10];
	PosStablo livo;
	PosStablo desno;
};
struct Stog {
	PosStablo el;
	PosStog Next;
};

int pushStog(PosStog, PosStablo);
int popStog(PosStog);
int citajDat(char*, PosStablo);
int pisiDat(char*, PosStablo);

int main(void) {
	int rez = 0;
	struct Stog head;
	head.Next = NULL;

	rez = citajDat("tu.txt", &head);
	if (rez)
		return rez;
	FILE *out = fopen("inf.txt", "w");
	
	pisiDat("inf.txt", head.Next->el);
	
	fclose(out);
	return 0;
}
int pushStog(PosStog S, PosStablo x) {
	PosStog q;
	q = (struct Stog *)malloc(sizeof(struct Stog));
	q->Next = q->el = NULL;

	q->el = x;

	q->Next = S->Next;
	S->Next = q;

	return 0;
}
int popStog(PosStog P) {
	PosStog temp = P->Next;
	P->Next = P->Next->Next;
	free(temp);

	return 0;
}
int citajDat(char *fn, PosStablo head) {
	int result = 0;
	FILE *in = fopen(fn, "r");
	if (in == NULL)
		return 1;
	while (!feof(in)) {
		PosStablo q;
		q = (struct Stablo*)malloc(sizeof(struct Stablo));
		q->livo = q->desno = NULL;

		fscanf(in, " %s", q->op);
		if (!strcmp(q->op, "+") || !strcmp(q->op, "-") ||
			!strcmp(q->op, "*") || !strcmp(q->op, "%"))
		{
			result = popStog(head, &(q->desno));
			result = popStog(head, &(q->livo));
			
			pushStog(head, q);
		}
		else {
			pushStog(head, q);
		}
	}

	fclose(in);
}
int pisiDat(char *fn, PosStablo head) {
	pisiDat(fn, head->livo);
	FILE *in = fopen(fn, "a");	
	if (in == NULL)
		return 1;
	fprintf(in, "%s ", head->op);

	fclose(in);
	pisiDat(fn, head->desno);

	return 0;
}
