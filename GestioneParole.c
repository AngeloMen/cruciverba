#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cruciverba.h"
#include "funzioni.h"
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
	stamparicerca(p, FALSE);
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
  	printf("Parola: %c, riga= %2i, colonna=%2i: %s             \n", p->OrVe, p->riga+1, p->colonna+1, parola);
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
void PremiTasto(int riga, int colonna) {
	char risp;
		
	gotoxy(colonna, riga);
	printf("\n");
	printf("premi un tasto per proseguire\n");
	scanf("%c", &risp);
	scanf("%c", &risp);

}
/*-----------------------------------------------------------*/
/* stampa la parola attiva della definizione                 */
/*															 */
/*-----------------------------------------------------------*/
void stamparicerca(struct definizione *p, int cancella) {
	int riga, colonna, righe;
	char parola[40];
	char coord[40];

	righe	= maxr * 2;
	riga	= ((ctrdef-1)%(righe))+2;
	colonna	= maxc*4+((ctrdef-1)/(righe))*45+10;

	gotoxy(colonna, riga);
	if (cancella) {
		printf("%45s", " ");
	} else {
		sprintf(coord, "[%i:%i]", p->riga+1, p->colonna+1);	
		sprintf(parola, "(%i/%i)", p->i, p->ctr);	
		char *j = p->parole + p->lunghezza * (p->i - 1);
		printf("%2i %c, %*s, %*s, %.*s",  p->numero, p->OrVe, 8, coord
										,10, parola,  p->lunghezza, j);
	}

//	sleep(1);
	
	return;
}
/*-----------------------------------------------------------*/
/* ordina a caso le parole valide per ervitare di ripetere   */
/* sempre le stesse sequenze di tentativi                    */
/*-----------------------------------------------------------*/
void mescolaparole(char *parole, int lung, int ctr) {
	int  l
		,c
		,i;
	char tempar;

if (ctr <= 1) 
	return;

for (c = 0; c < ctr; c++) {
	i = rand()%(ctr-1);
	for (l = 0; l < lung; l++) {
		tempar				= parole[i*lung + l];
		parole[i*lung + l]	= parole[c*lung + l];
		parole[c*lung + l]	= tempar;
	}
}

return;

}
/*-----------------------------------------------*/
/* Conta le caselle piene della parola           */
/*-----------------------------------------------*/
int piene(struct definizione *p) {
	int incC, incR, ctr = 0;

	int riga	= p->riga;
	int colonna	= p->colonna;

	p->OrVe == 'O' ? (incC = 1, incR = 0) : (incC = 0, incR = 1);

	for (int i = 0; i < p->lunghezza; i++) {
		if (schema[riga][colonna] != ' ')
		   	++ctr;
		riga	+= incR;
		colonna	+= incC;
	}

	return ctr;
}
/*-----------------------------------------------*/
/* Calcola il rapporto tra caselle vuote e piene */
/*-----------------------------------------------*/
float rapporto(struct definizione *p) {
	int vuote = 0, piene = 0, i, r, c;
	int ic, ir;                         // Incrementi per sveltire i cicli

	r = p->riga;
	c = p->colonna;
	p->OrVe == 'O' ? (ic = 1, ir = 0) : (ic = 0, ir = 1);

	for (i = 0; i < p->lunghezza; i++) {
		schema[r][c] == ' ' ? ++vuote : ++piene;
		c = c + ic;
		r = r + ir;
	}

	if (piene == 0)
		return 999;

	return vuote / piene;

}
