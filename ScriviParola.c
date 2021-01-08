#include <stdio.h>
#include "cruci.h"
//#include "crucifun.h"  
/*  Chiede a terminale che parola inserire e controlla che quella
 *  digitata sia corretta per lunghezza e incroci con quelle già
 *  esistenti. Permette la cancellazione delle parole già inserite  */

/*-----------------------------------------------------------------*/
/*         Scrive la parola richiesta prendendola dallo schema     */
/*-----------------------------------------------------------------*/
void ScriviParola(struct definizione *p) {
	int r, c, l, i;
	char OV;

	r = p->riga;
	c = p->colonna;
	l = p->lunghezza;
	OV = p->OrVe;

	/*                                               */
	/*   Si posiziona sull'angolo superiore sinistro */
	/*                                               */
	printf("\033[3;5H");
	/*                                               */
	/*   Si porta alla prima casella della parola    */
	/*                                               */
	for (i = 0; i < r; i++)
		printf("\033[2B");
	for (i = 0; i < c; i++)
		printf("\033[4C");

	for (i = 0; i < l; i++) {
		printf("%c", schema[r][c]);
		if (OV == 'O') {
			printf("\033[3C");
			++c;
		}
		if (OV == 'V') {
			printf("\033[2B");
			printf("\033[1D");
			++r;
		}
	}

	puts("\033[24;1H");
	return;
}
/*-----------------------------------------------------------------*/
/* Carica la parola nello schema e la segna come trovata nella ta- */
/* bella delle verticali o orizzontali.                            */
/*-----------------------------------------------------------------*/
void CaricaParola(struct definizione *d, char *p) {
	int i, r, c, l;
	char OV;

	r = d->riga;
	c = d->colonna;
	l = d->lunghezza;
	OV = d->OrVe;

	for (i = 0; i < l; i++) {
		schema[r][c] = *p;
		++ctrsch[r][c];
		++p;
		OV == 'O' ? ++c : ++r;
	}

	return;
}
