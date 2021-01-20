#include <stdio.h>
#include <stdlib.h>
#include "cruciverba.h"
#include "funzioni.h"
/*-------------------------------------------------------------------------*/
/*  Legge le dimenzioni dello schema                                       */
/*-------------------------------------------------------------------------*/
void LeggiDimensioni(void) {
	printf("Immettere le dimensioni dello schema (righe, colonne): ");
	scanf("%d%*c%d", &maxr, &maxc);
	printf("\n");

	/* Verifica che non superino le massime dimensioni ammesse */
	if (maxr > MaxR) {
		printf("Superato il limite di righe (%d)\n", MaxR);
		exit(1);
	}
	if (maxc > MaxC) {
		printf("Superato il limite di colonne (%d)\n", MaxC);
		exit(1);
	}
}
/*-------------------------------------------------------------------------*/
/*  Chiede se salvare lo schema                                            */
/*-------------------------------------------------------------------------*/
void SalvaSchema(void) {
	FILE *fp;
	char NomeFile[80];
	char risp;

	printf("Salvo lo schema?(s=si, n=no)?\n");
	scanf("%c", &risp);
	if (risp != 's')
		return;

	printf("Che nome dare al file?\n");
	scanf("%s", NomeFile);

	if ((fp = fopen(NomeFile, "wb")) == NULL) {
		printf("Impossibile aprire il file.\n");
		exit(1);
	}

	fwrite(&maxr, sizeof(int), 1, fp);
	fwrite(&maxc, sizeof(int), 1, fp);
	fwrite(schema, sizeof(schema), 1, fp);

	fclose(fp);

	return;
}
