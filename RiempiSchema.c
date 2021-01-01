#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cruci.h"
/* -------------------------------------------------------
 * Prototipi delle funzioni 
 -------------------------------------------------------*/
struct	definizione* ParolaPrecedente(void);			//
struct	definizione* ProssimaParola(void);				//
int		TrovaParola(struct definizione*);				//
int		TrovaParola_1(struct definizione*);				//
int		TrovaParola_2(struct definizione*);				//
int		CercaParole(struct definizione*, int);			//
int		piene(struct definizione*);						//
void	AccodaLista(struct definizione*);				//
void	CancellaParola(struct definizione*);			//
void	ScriviParola(struct definizione*);				//

/*-----------------------------------------------------------------*/
/*             Inizio della funzione                               */
/*-----------------------------------------------------------------*/
int RiempiSchema(void) {

    p = inizio;

	while (1) {
		if (TrovaParola(p)) {							// Cerca la parola e se trovata
			p->trovata = TRUE;
			p = ProssimaParola();						// si posiziona alla successiva
			if (p == NULL)								// se finita lista parole
				return 1;								//    schema risolto
		} else {
			p->trovata = FALSE;
			p = ParolaPrecedente();						// Si posiziona sulla parola precedente
			if (p == NULL)								// Va alla precedente e sono finite
				return 0;								//    schema irrisolto
		}
	}

	return 0;

}
/*----------------------------------------------------------------*/
/*           Ritorna l'indirizzo della parola da cercare          */
/*           e costruisce una lista delle parole cercate          */
/*----------------------------------------------------------------*/
struct definizione* ProssimaParola(void) {
	struct	definizione *p, *prossima;
	int		ctrprec = INT_MAX, lunprec = 0, ctrn;

	p			= inizio;
	prossima	= NULL;

	for (p = inizio; p != NULL; p=p->succ) {

		if (p->trovata)
			continue;
		if (piene(p) == 0)
			continue;

		ctrn = CercaParole(p, TRUE);
		if (ctrn < ctrprec){
			prossima	=	p;
			ctrprec 	=	ctrn;
			lunprec		=	p->lunghezza;
		}

	}

	if (prossima != NULL)
		AccodaLista(prossima);

	return prossima;
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
/*-----------------------------------------------*/
/* Prepara la lista delle parole analizzate      */
/*-----------------------------------------------*/
void AccodaLista(struct definizione *pd) {
	struct listaricerca *p;

	if ((p = (struct listaricerca*) malloc(sizeof(struct listaricerca))) == NULL) {
		puts("Memoria esaurita");
		exit(1);
	}

	p->def = pd;
	p->prec = NULL;
	p->succ = NULL;

	if (prima == NULL) {
		ultima = prima = p;
	} else {
		ultima->succ = p;
		p->prec = ultima;
		ultima = p;
	}

	return;

}

/*----------------------------------------------------------------*/
/*       Passa alla parola precedente che ha risolto              */
/*----------------------------------------------------------------*/
struct definizione* ParolaPrecedente(void) {
	struct listaricerca *p;
	struct definizione *pd;

	if (ultima->prec == NULL) {
		free(ultima);
		return NULL;
	}

	p = ultima->prec;
	pd = p->def;

//
// cancello la parola dallo schema 
//
	CancellaParola(pd);

	if (scrivereparola)
		ScriviParola(pd);

	free(ultima);

	ultima = p;
	p->succ = NULL;

	return p->def;

}
/*-----------------------------------------------*/
/* Cancella la parola dallo schema               */
/*-----------------------------------------------*/
void CancellaParola(struct definizione *pd) {
	int r, c, i;
	int ic, ir;                         // Incrementi per sveltire i cicli

	r = pd->riga;
	c = pd->colonna;
	pd->OrVe == 'O' ? (ic = 1, ir = 0) : (ic = 0, ir = 1);
	for (i = 0; i < pd->lunghezza; i++) {
		--(ctrsch[r][c]);
		if (ctrsch[r][c] == 0)
			schema[r][c] = ' ';
		c = c + ic;
		r = r + ir;
	}
}
