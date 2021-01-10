/* Questa funzione riempie di spazi lo schema           */
/* lo schema e le sue dimensioni sono variabili globali */

#include <stdio.h>
#include "cruciverba.h"
#include "funzioni.h"
//extern char	schema[MaxR][MaxC];	/* Schema     */
//extern int	ctrsch[MaxR][MaxC];	/* Schema     */
//extern int	maxr, maxc;			/* dimensioni */

void PulisciSchema() {

	int r, c;

	for (r = 0; r < maxr; r++)
		for (c = 0; c < maxc; c++) {
			schema[r][c] = ' ';
			ctrsch[r][c] = 0;
			casella[r][c].vert = NULL;
			casella[r][c].oriz = NULL;
		}

	return;
}
