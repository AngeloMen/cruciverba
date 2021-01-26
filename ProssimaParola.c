#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cruciverba.h"
#include "funzioni.h"

/*----------------------------------------------------------------*/
/*           Ritorna l'indirizzo della parola da cercare          */
/*           e costruisce una lista delle parole cercate          */
/*----------------------------------------------------------------*/
struct definizione* ProssimaParola(struct definizione *prec) {

	struct definizione *prossima;

	switch(sceltaprox) {
		case 0: prossima = ProssimaParola0(prec);
				break;
		case 1: prossima = ProssimaParola1(prec);
				break;
		case 2: prossima = ProssimaParola2(prec);
				break;
	}
	return prossima;

}
/*----------------------------------------------------------------*/
/*           Ritorna l'indirizzo della parola da cercare          */
/*           e costruisce una lista delle parole cercate          */
/*----------------------------------------------------------------*/
struct definizione* ProssimaParola0(struct definizione *prec) {
	struct	definizione *p, *prossima;
	int		ctrprec = INT_MAX, lunprec = 0, ctrn;

	if (ultima->succ != NULL){
		ultima		= ultima->succ;
		prossima	= ultima->def;
		ctrdef++;
		return prossima;
	}

	p			= inizio;
	prossima	= NULL;

	for (p = inizio; p != NULL; p=p->succ) {

		if (p->trovata)
			continue;
		if (piene(p) == 0)
			continue;

		if (SiIncrociano(p, prec)) {
			ctrn		=	CercaParole(p, TRUE);
			prossima	=	p;
			ctrprec 	=	ctrn;
			lunprec		=	p->lunghezza;
			break;
		}
			
		ctrn = CercaParole(p, TRUE);
		if (ctrn < ctrprec){
			prossima	=	p;
			ctrprec 	=	ctrn;
			lunprec		=	p->lunghezza;
		}

	}

	if (prossima != NULL)
		AccodaLista(prossima);

	ctrdef++;
	return prossima;
}
/*----------------------------------------------------------------*/
/*           Ritorna l'indirizzo della parola da cercare          */
/*           e costruisce una lista delle parole cercate          */
/*----------------------------------------------------------------*/
struct definizione* ProssimaParola1(struct definizione *prec) {
	struct	definizione *p, *prossima;
	int		ctrprec = INT_MAX, lunprec = 0, ctrn;
	int		rigaprec = INT_MAX, colonnaprec = INT_MAX;


	if (ultima->succ != NULL){
		ultima		= ultima->succ;
		prossima	= ultima->def;
		ctrdef++;
		return prossima;
	}

	p			= inizio;
	prossima	= NULL;

	for (p = inizio; p != NULL; p=p->succ) {

		if (p->trovata)
			continue;
		if (piene(p) == 0)
			continue;

		if (SiIncrociano(p, prec)) {
			switch (p->OrVe) {
				case 'V': 
					if (p->colonna <  colonnaprec) {
						prossima	= p;
						colonnaprec	= prossima->colonna;
						rigaprec	= prossima->riga;
					}else
						if (p->colonna == colonnaprec)
							if (p->riga < rigaprec) {
								prossima	= p;
								colonnaprec	= prossima->colonna;
								rigaprec	= prossima->riga;
							}
					continue;
				case 'O': 
					if (p->riga < rigaprec){
						prossima	= p;
						colonnaprec	= prossima->colonna;
						rigaprec	= prossima->riga;
					}else
						if (p->riga == rigaprec)
							if (p->colonna < colonnaprec) {
								prossima	= p;
								colonnaprec	= prossima->colonna;
								rigaprec	= prossima->riga;
							}
					continue;
			}
			continue;
		}
		ctrn = CercaParole(p, TRUE);
		if (ctrn < ctrprec){
			prossima	=	p;
			ctrprec 	=	ctrn;
			lunprec		=	p->lunghezza;
		}
	}

	if (prossima != NULL)
		AccodaLista(prossima);

	ctrdef++;
	return prossima;
}
/*----------------------------------------------------------------*/
/*           Ritorna l'indirizzo della parola da cercare          */
/*           e costruisce una lista delle parole cercate          */
/*----------------------------------------------------------------*/
struct definizione* ProssimaParola2(struct definizione *prec) {
	struct definizione *prossima;


	if (ultima->succ != NULL){
		ultima		= ultima->succ;
		prossima	= ultima->def;
		ctrdef++;
		return prossima;
	}

	prossima = ProssimaDaIncrocio(prec);
	if (prossima != NULL){
		AccodaLista(prossima);
		ctrdef++;
		CtrProInc++;
		return prossima;
	}

	prossima = ProssimaDaSchema(prec);
	if (prossima != NULL){
		AccodaLista(prossima);
		CtrProSch++;
		ctrdef++;
	}

	return prossima;

}
/*-----------------------------------------------*/
/* Prepara la lista delle parole analizzate      */
/*-----------------------------------------------*/
struct definizione* ProssimaDaIncrocio(struct definizione *prec) {
	struct	definizione *prossima, *p;
	int		ic, ir, riga, colonna;
   	int		rigaprec	=	INT_MAX;
	int		colonnaprec	=	INT_MAX;

	prossima	= NULL;

	(prec->OrVe == 'O') ? (ic = 1, ir = 0) : (ic = 0, ir = 1);
	riga	= prec->riga;
	colonna = prec->colonna;

	for (int i=0; i < prec->lunghezza; i++) {
		if (casella[riga][colonna].vert != NULL){
			p = casella[riga][colonna].vert;
			if (!(casella[riga][colonna].vert->trovata)){
				if (p->colonna <  colonnaprec) {
					prossima	= p;
					colonnaprec	= prossima->colonna;
					rigaprec	= prossima->riga;
				}else
					if (p->colonna == colonnaprec){
						if (p->riga < rigaprec) {
							prossima	= p;
							colonnaprec	= prossima->colonna;
							rigaprec	= prossima->riga;
						}
					}
			}
		}
		if (casella[riga][colonna].oriz != NULL){
			if (!(casella[riga][colonna].oriz->trovata)){
				p = casella[riga][colonna].oriz;
				if (p->riga < rigaprec){
					prossima	= p;
					colonnaprec	= prossima->colonna;
					rigaprec	= prossima->riga;
				}else{
					if (p->riga == rigaprec){
						if (p->colonna < colonnaprec) {
							prossima	= p;
							colonnaprec	= prossima->colonna;
							rigaprec	= prossima->riga;
						}
					}
				}
			}
		}
	riga+=ir;
	colonna+=ic;
	}

	return prossima;
}
/*-----------------------------------------------*/
/* Prepara la lista delle parole analizzate      */
/*-----------------------------------------------*/
struct definizione* ProssimaDaSchema(struct definizione *prec) {
	struct	definizione *p, *prossima;
	int		rigaprec = INT_MAX, colonnaprec = INT_MAX;


	if (ultima->succ != NULL){
		ultima		= ultima->succ;
		prossima	= ultima->def;
		ctrdef++;
		return prossima;
	}

	p			= inizio;
	prossima	= NULL;

	for (p = inizio; p != NULL; p=p->succ) {

		if (p->trovata)
			continue;
		if (piene(p) == 0)
			continue;
		if (IncrociCompleti(p))
			continue;

		switch (p->OrVe) {
			case 'V': 
				if (p->colonna <  colonnaprec) {
					prossima	= p;
					colonnaprec	= prossima->colonna;
					rigaprec	= prossima->riga;
				}else
					if (p->colonna == colonnaprec)
						if (p->riga < rigaprec) {
							prossima	= p;
							colonnaprec	= prossima->colonna;
							rigaprec	= prossima->riga;
						}
				continue;
			case 'O': 
				if (p->riga < rigaprec){
					prossima	= p;
					colonnaprec	= prossima->colonna;
					rigaprec	= prossima->riga;
				}else
					if (p->riga == rigaprec)
						if (p->colonna < colonnaprec) {
							prossima	= p;
							colonnaprec	= prossima->colonna;
							rigaprec	= prossima->riga;
						}
				continue;
			}
			continue;
	}
	return prossima;
}
/*-----------------------------------------------*/
/* Prepara la lista delle parole analizzate      */
/*-----------------------------------------------*/
void AccodaLista(struct definizione *prossima) {
	struct listaricerca *p;

	if ((p = (struct listaricerca*) malloc(sizeof(struct listaricerca))) == NULL) {
		puts("Memoria esaurita");
		exit(1);
	}

	p->def	= prossima;
	p->prec	= NULL;
	p->succ	= NULL;

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

	p		= ultima->prec;
	pd		= p->def;


//
// cancello la parola dallo schema 
//
	CancellaParola(pd);

	if (scrivereparola)
		ScriviParola(pd);

	stamparicerca(pd, TRUE);
	ctrdef--;

//	free(ultima);

	ultima	= ultima->prec;

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
