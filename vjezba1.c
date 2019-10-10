#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
}student;

int main() {
	FILE *in = NULL;
	student *stud = NULL;
	int i=0, brojac = 0;
	int max = 0;

	in = fopen("lista.txt", "r");
	if (in == NULL) {
		printf("Ne moze\n");
	}

	while (!feof(in)) {
		if (fgetc(in) == '\n')
			brojac++;
	}

	rewind(in);

	stud = (student*)malloc(brojac * sizeof(student));

	for (i = 0; i < brojac; i++) {
		fscanf(in, " %s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
			if(stud[i].bodovi>max)
				max = stud[i].bodovi;
	}

	for (i = 0; i < brojac; i++) {
		printf("%s %s Apsolutni bodovi: %d     Relativni bodovi: %f %%\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, ((float)stud[i].bodovi / max) * 100);
	}

	free(stud);
	getchar();
	return 0;
}