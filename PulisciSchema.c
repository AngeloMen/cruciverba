#include <stdio.h>
#include "cruciverba.h"
#include "funzioni.h"
extern struct passante casella[MaxR][MaxC];

void PulisciSchema() {

	int riga, colonna;

	for (riga = 0; riga < maxr; riga++)
		for (colonna = 0; colonna < maxc; colonna++) {
			schema[riga][colonna] = ' ';
			ctrsch[riga][colonna] = 0;
			casella[riga][colonna].vert = NULL;
			casella[riga][colonna].oriz = NULL;
		}

	return;
}
