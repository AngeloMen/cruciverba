#include <stdio.h>
#include "cruci.h"
/*
 * legge da tastiera le coordinate di una casella e se c'è una "X"
 * la sostituisce con uno spazio, viceversa se c'è uno spazio lo
 * sostituisce con una 'X' (che tristemente sta per casella nera)   */

void ScriviCasella(int, int);

void MettiCaselleNere() {
	int x = 1, y = 1;
	do {
		printf(
		"\033[40;1Hinserisci le coodinate per la casella nera (0,0=fine)");
		scanf("%d%*c%d", &x, &y);
		if (x == 0)
			break;
		if (x > maxr)											/* Che non superi le righe ammesse */
			printf("Fuori schema\n");
		else if (y > maxc)										/* Che non superi le colonne ammesse */
			printf("Fuori colonna\n");
		else
			schema[x - 1][y - 1] = schema[x - 1][y - 1] == ' ' ? NERA : ' ';

		ScriviCasella(x, y);

	} while (x != 0);
	return;
}

void ScriviCasella(int x, int y) {
	int r, c;
	printf("\033[1;1H");
	for (r = 0; r < x; r++)
		printf("\033[2B");
	for (c = 0; c < y; c++)
		printf("\033[4C");

	printf("%c", schema[x - 1][y - 1]);

	return;

}
