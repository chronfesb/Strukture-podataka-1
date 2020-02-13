//1.ISPITNI ROK 13.2.2020.

//kod je zbog visestrukog otvaranja i zatvaranja datoteka spor, memorija nije dealocirana, napisano bez dealokacije da se moze 
//iscitat glavna ideja zadatka
//ostali kojima je radilo nisu radili navedenu funkciju pomocPriUnosuUListu, vec su sa sscanf odmah citali rijec po rijec i stavljali u listu
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_IME 15

typedef struct Cvor *Position;
struct Cvor {
	char rijec[MAX_IME];
	Position Next;
};
typedef struct CvorStablo *Stablo;
typedef struct CvorStablo *pozicija;
struct CvorStablo {
	char ime[MAX_IME];
	char prezime[MAX_IME];
	Stablo L;
	Stablo D;
	Position lista;
};
Stablo citajDat(char*, Stablo);
Stablo dodaj(char*, char*, Stablo);
int inorder(Stablo);
Stablo trazi(char*, char*, Stablo);
Stablo alocirajCvorStabla(Stablo);

int pomocPriUnosuUListu(char*, Position);
int unosUListu(char*, Position);
int ispisListe(Position);
Position alocirajCvorListe(Position);

int main(void) {
	Stablo root = NULL;
	root = citajDat("quotes.txt", root);

	inorder(root);
	puts("");
	return 0;
}
Stablo citajDat(char *fn, Stablo S) {
	FILE *out;
	pozicija pom = NULL;					//pozicija je zapravo isto sta i Stablo, samo eno (Pokazivac na Cvor od stabla!!)
	out = fopen(fn, "r");
	if (out == NULL) {
		printf("Cant read from file\n");
		return NULL;
	}
	char buff1[MAX_IME], buff2[MAX_IME];
	char ostalo[1024];
	while (!feof(out)) {
		fscanf(out, "%s %s", buff1, buff2);  //fscanf skupi do razmaka
		fgets(ostalo, sizeof(ostalo), out);  //fgets skupi do \n
		S = dodaj(buff1, buff2, S);
		pom = trazi(buff1, buff2, S);
		pomocPriUnosuUListu(ostalo, pom->lista);
	}
	fclose(out);
	return S;
}
Stablo dodaj(char *name, char *surn, Stablo S) {
	if (S != NULL) {
		if (_stricmp(surn, S->prezime) < 0 || (_stricmp(surn, S->prezime) == 0 && (_stricmp(name, S->ime) < 0))) //stricmp -> isto sto i strcmp samo sto ne razlikuje mala i velika slova,
			S->L = dodaj(name, surn, S->L);																		// dakle RiJec i rijec su mu jednaki. Zahvale kolegi M.V. na toj spoznaji
		else if (_stricmp(surn, S->prezime) > 0 || (_stricmp(surn, S->prezime) == 0 && (_stricmp(name, S->ime) > 0)))
			S->D = dodaj(name, surn, S->D);
	}
	else {
		S = alocirajCvorStabla(S);
		strcpy(S->ime, name);
		strcpy(S->prezime, surn);
	}
	return S;
}
int inorder(Stablo S) {
	if (S != NULL) {
		inorder(S->L);
		printf("\n%s %s: ", S->ime, S->prezime);
		ispisListe(S->lista);
		inorder(S->D);
	}
	return 0;
}
Stablo trazi(char *name, char *surn, Stablo S) {
	if (S != NULL) {
		if (_stricmp(surn, S->prezime) < 0 || (_stricmp(surn, S->prezime) == 0 && (_stricmp(name, S->ime) < 0)))
			return trazi(name, surn, S->L);
		else if (_stricmp(surn, S->prezime) > 0 || (_stricmp(surn, S->prezime) == 0 && (_stricmp(name, S->ime) > 0)))
			return trazi(name, surn, S->D);
		else
			return S;
	}
	else return NULL;
}
int pomocPriUnosuUListu(char *s, Position P) {  //umjesto koristenja sscanfa, ja sam odlucia da stavljam svaku rijec 
	FILE *in;									//u novu datoteku i citam iz nje rijec po rijec onda sa fscanf kao i gore
	char buff[MAX_IME];
	in = fopen("novo.txt", "w+");				// w+ -> citat + pisat
	if (in == NULL) {
		printf("Cant r/w\n");
		return 1;
	}
	fprintf(in, "%s", s);
	rewind(in);							//bilo kakav rad sa dat mice pokazivac po datoteci, treba ga vratit nazad za citat ispocetka
	while (1) {							//ovako ne cita zadnju rijec dvaput ka sta bi u slucaju while(!feof(in))
		fscanf(in, " %s", buff);
		if (feof(in))
			break;
		unosUListu(buff, P);
	}
	fclose(in);
	return 0;
}
int unosUListu(char *buff, Position P) {
	Position q = NULL;
	q = alocirajCvorListe(q);
	strcpy(q->rijec, buff);
	
	q->Next = P->Next;			//recenice su napisane unazad, ispravi se tako da se stavlja na stog, umjesto na red, ako bi na red, ostale bi u istom redoslijedu
	P->Next = q;

	return 0;
}
int ispisListe(Position P) {
	P = P->Next;
	while (P != NULL) {
		printf("%s ", P->rijec);
		P = P->Next;
	}
	return 0;
}
Stablo alocirajCvorStabla(Stablo S) {
	S = (struct CvorStablo *)malloc(sizeof(struct CvorStablo));
	S->L = NULL;
	S->D = NULL;
	S->lista = (struct Cvor*)malloc(sizeof(struct Cvor)); //struct Cvor head;
	S->lista->Next = NULL;								  //head.Next = NULL;
	return S;											 //svaki cvor stabla pokazuje na head od liste i onda je lako, slanje head-a je sad slanje S->lista. 
}														//zahvale kolegici M.M. bez koje ovaj kljucni dio zadatka ne bi bia rijesen
Position alocirajCvorListe(Position q) {
	q = (struct Cvor*)malloc(sizeof(struct Cvor));
	q->Next = NULL;
	return q;
}
//sretno na ispitima, D.V.