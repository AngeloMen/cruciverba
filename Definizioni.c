#include <stdio.h>
#include <stdlib.h>
#include "cruciverba.h"
#include "funzioni.h"

/*-----------------------------------------------------------------*/
/*             Inizio della funzione                               */
/*-----------------------------------------------------------------*/
void Definizioni(void) {
	int r, c;

	for (r = 0; r < maxr; r++) {
		for (c = 0; c < maxc; c++) {
			casella[r][c].vert = NULL; 
			casella[r][c].oriz = NULL; 
		}
	}		
	for (r = 0; r < maxr; r++) {
		for (c = 0; c < maxc; c++) {
													// Eseguo la ricerca solo se mi
			if (schema[r][c] != NERA){				// trovo su una casella bianca
				/*-----------------*/
				/*   Orizzontale   */
				/*-----------------*/
				if (InizioOriz(r, c)) {				// se è l'inizio di una parola orizzontale
					AggiungiDefinizione('O', r, c);	//    l'aggiungo alla lista
				}
				/*-----------------*/
				/*    Verticale    */
				/*-----------------*/
				if (InizioVert(r, c)) {				// se è l'inizio di una parola veritcale
					AggiungiDefinizione('V', r, c);	//    l'aggiungo alla lista
				}
			}                                     // fine if casella bianca
		}                                      // fine ciclo colonne
	}                                        // fine ciclo righe
	return;
}
/*  Riceve in input riga e colonna di una casella bianca e
 *  determina se sono le coordinate iniziali di una parola
 *  orizzontale.
 *  Ritorna TRUE se è l'inizio, FALSE se non lo è.           */
int InizioOriz(int r, int c) {

	if ((c == 0 || schema[r][c - 1] == NERA) && ((c + 1) < maxc)
			&& (schema[r][c + 1] != NERA))
		return 1; /* E' l'inizio di una parola */

	return 0; /* Non è l'inizio di una parola */
}


/*  Riceve in input riga e colonna di una casella bianca e
 *  determina se sono le coordinate iniziali di una parola
 *  verticale.
 *  Ritorna TRUE se è l'inizio, FALSE se non lo è.           */
int InizioVert(int r, int c) {

	if ((r == 0 || schema[r - 1][c] == NERA) && ((r + 1) < maxr)
//			&& (schema[r + 1][c] == ' '))
			&& (schema[r + 1][c] != NERA))
		return 1;

	return 0;
}

/*--------------------------------------------------*/
/* Crea la lista dinamica delle definizioni         */
/*--------------------------------------------------*/
void AggiungiDefinizione(char OrVe     // 'O'=Orizzontale, 'V'=Verticale
						, int r        // Riga di inizio
						, int c)       // Colonna di inizio
{
	static int	sr=-1
			   ,sc=-1 
			   ,def = 0;

	struct definizione *p;
	int incC, incR
		,riga, colonna, l;

	if ((p = (struct definizione*) malloc(sizeof(struct definizione))) == NULL) {
		puts("Memoria esaurita");
		exit(1);
	}

	(OrVe == 'O') ? (incC = 1, incR = 0)		: (incC = 0, incR = 1);
	(OrVe == 'O') ? (l = CalcolaLungOriz(r, c))	: (totaleVerticali += 1);
	(OrVe == 'O') ? (totaleOrizzontali +=1)		: (l = CalcolaLungVert(r, c));


	if ((sr != r) || (sc != c)) {
		sr = r;
	  	sc = c;
	   	def+=1;
	}

	p->OrVe = OrVe;
	p->numero = def;
	p->lunghezza = l;
	p->riga = r;
	p->colonna = c;
	p->trovata = FALSE;
	p->ctr = 0;
	p->i = 0;
	p->prec = NULL;
	p->succ = NULL;

	if (inizio == NULL) {
		fine = inizio = p;
	} else {
		fine->succ = p;
		p->prec = fine;
		fine = p;
	}

	riga	= r;
	colonna	= c;

	for (int i = 0; i < l; i++){
	    (OrVe == 'O') ? (casella[riga][colonna].oriz = p) : (casella[riga][colonna].vert = p);
		riga	+= incR;
		colonna += incC;
	}
}
/*
 *
 */
int CalcolaLungOriz(int r, int c) {
	int l;

	l = 0;

	//while ((c < maxc) && schema[r][c] == ' ')
	while ((c < maxc) && schema[r][c] != NERA)
		++l, ++c;

	return l;

}
/*
 *
 */
int CalcolaLungVert(int r, int c) {
	int l;

	l = 0;

	while ((r < maxr) && schema[r][c] != NERA)
		++l, ++r;

	return l;

}
/*                                                              */
/* stampa a video lo schema con le coordinate di riga e colonna */
/*                                                              */
//extern char schema[MaxR][MaxC]; /* Array dello schema       */
//extern int maxr, maxc; /* dimensioni dello schema  */

void DisegnaSchema() {
	int r, c;
	void DisegnaRiga(void);

	printf("\033[2J");									/* Pulisce lo schermo      */
	printf("\033[1;1H");								/* Riga 1 colonna 1        */
	printf("  ");										/* Stampa gli indici       */
	for (c = 0; c < maxc; c++)
		printf(" %2d ", c + 1);							/* di colonna              */
	printf("\n");

	DisegnaRiga();										/* prima riga              */

	for (r = 0; r < maxr; r++) {

		printf("%2d", r + 1);							/* Stampa l'indice di riga */

		for (c = 0; c < maxc; c++)
//			printf("| %c ", schema[r][c]);				/* Stampa la casella       */
//			printf("| %c ", schema[r][c]);				/* Stampa la casella       */
			(schema[r][c] == NERA) ? printf("| X ") : printf("| %c ",schema[r][c]);

		printf("|\n");

		DisegnaRiga();									/* riga di separazione     */
	}
	gotoxy(1, maxr*2+4);
	printf("%s", argp_program_version);
	printf("\n\n\n");
	return;
}

/*             
 *             Disegna una riga di separazione
 *                                                    */

void DisegnaRiga() {
	int c;

	printf("  ");
	for (c = 0; c < maxc; ++c)
		printf("|---");

	printf("|\n");
	return;
}
