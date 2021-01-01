#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
/*-----------------------------------------------------------*/
/* controlla se le due definizioni ricevute in input         */
/* si incrociano                                             */
/*-----------------------------------------------------------*/
int SiIncrociano(struct definizione *p, struct definizione *pd) {

	int	colonna
	   ,colonna_iniziale
	   ,colonna_finale
	   ,riga
	   ,riga_iniziale
	   ,riga_finale;

	if (pd->trovata)
	   return FALSE;

	if ((p->OrVe == 'V') && (pd->OrVe == 'O')){
		colonna				= p->colonna;
		colonna_iniziale	= pd->colonna;
		colonna_finale		= pd->colonna + pd->lunghezza - 1;
		riga				= pd->riga;
		riga_iniziale		= p->riga;
		riga_finale			= p->riga + p->lunghezza - 1;
	} else
	if ((p->OrVe == 'O') && (pd->OrVe == 'V')){
		colonna				= pd->colonna;
		colonna_iniziale	= p->colonna;
		colonna_finale		= p->colonna + p->lunghezza - 1;
		riga				= p->riga;
		riga_iniziale		= pd->riga;
		riga_finale			= pd->riga + pd->lunghezza - 1;
	} else
	   return FALSE;

	if (schema[riga][colonna] == ' ') 
		return FALSE;

	if (((colonna >= colonna_iniziale) && (colonna <= colonna_finale))
	&& ((riga     >= riga_iniziale)    && (riga    <= riga_finale))){
		return TRUE;
	}
	 return FALSE;
}

/*-----------------------------------------------------------*/
/* stampa la parola attiva della definizione                 */
/*															 */
/*-----------------------------------------------------------*/
void stampaparola(struct definizione *p) {
	int i;
	char *j;
	char parola[Maxl];

	j = p->parole + p->lunghezza * (p->i - 1);
	for (i = 0; i < p->lunghezza; i++){
		parola[i] = *j;
		j++;
	}
	i = p->lunghezza;
	parola[i] = '\0';
  	printf("Parola: %c, riga= %i, colonna=%i: %s             \n", p->OrVe, p->riga+1, p->colonna+1, parola);
	return;
}
/*-----------------------------------------------------------*/
/* stampa la parola attiva della definizione                 */
/*															 */
/*-----------------------------------------------------------*/
void stampaparola_i(struct definizione *p, int i) {
	char *j;
	char parola[Maxl];

	j = p->parole + p->lunghezza * (i - 1);
	for (i = 0; i < p->lunghezza; i++){
		parola[i] = *j;
		j++;
	}
	i = p->lunghezza;
	parola[i] = '\0';
  	printf("Parola: %c, riga= %i, colonna=%i: %s             \n", p->OrVe, p->riga+1, p->colonna+1, parola);
	return;
}
void PremiTasto() {
	char risp;

		printf("\n");
		printf("premi un tasto per proseguire\n");
		scanf("%c", &risp);

}
