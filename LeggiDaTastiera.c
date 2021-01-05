#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cruci.h"
#define	RIGA 45											// Posizione della riga delle richieste
/*-----------------------------------------------------------------*/
/*             Prototipi delle funzioni                            */
/*-----------------------------------------------------------------*/
void	evidenzia(struct definizione*);					//
void	ScriviParola(struct definizione*);				//
void	lettura(struct definizione *p);					//
void	CaricaParola(struct definizione*, char*);		//
int		ControllaParola(char, int, int, int, char*);	//
int		ApriDatabase(void);								// Apertura del database
int		ChiudiDatabase(void);							// Chiusura del database
void	AccodaLista(struct definizione*);				//
struct	definizione* ProssimaParola(void);				//
//
//
/*  Chiede a terminale che parola inserire e controlla che quella
 *  digitata sia corretta per lunghezza e incroci con quelle già
 *  esistenti. Permette la cancellazione delle parole già inserite  */

/*-----------------------------------------------------------------*/
/*             Inizio della funzione                               */
/*-----------------------------------------------------------------*/
void LeggiDaTastiera(void) {
	char scelta;									 /* Scelta                                       */
	struct definizione *p;

	p = inizio;
	evidenzia(p);

	do {
		printf("\033[44;1HDef: %i, riga,%i colonna=%i, lunghezza:%i. S=Successiva, I=Inserisci, F=Fine.\n"
									,p->numero, p->riga, p->colonna, p->lunghezza);
		scelta = getchar();
		switch (scelta) {
		case 's':
			ScriviParola(p);						/* riscrive la parola precedente  */
			p = p->succ;
			if (p == NULL)
				p = inizio;
			evidenzia(p);							/* segnala la parola in oggetto   */
			break;
		case 'c':
			printf("\033[44;1Hcancella \033[K");
			break;
		case 'i': {
			lettura(p);								/* Legge e controlla la parola    */
			break;
			}
		case 'f':
			break;
		}
	} while (scelta != 'f');

	return;
}

/*                                                    */
/* Visualizza la parola che si deve inserire          */
/*                                                    */
void evidenzia(struct definizione *p) {
	int r, c, l, i;

	r = p->riga;
	c = p->colonna;
	l = p->lunghezza;

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
		(schema[r][c] == ' ') ? printf("+") : printf("%c", schema[r][c]);
		if (p->OrVe == 'O') {
			printf("\033[3C");
			++c;
		} else {
			printf("\033[2B");
			printf("\033[1D");
			++r;
		}
	}

	return;
}
/*                                                    */
/* Legge la parola da tastiera                        */
/*                                                    */
void lettura(struct definizione *p) {
	int r, c, l, ParolaOk;
	char parola[Maxl];
	char OV;
	char *pc;

	r = p->riga;
	c = p->colonna;
	l = p->lunghezza;
	OV = p->OrVe;

	ParolaOk = FALSE;
	do {
		printf("\033[46;1HParola? \033[K");
		scanf("%s", parola);
		if (strlen(parola) == 1)
			break;
		if ((strlen(parola) != l)) { /* lunghezza errata  */
			printf("\033[46;1Hlunghezza errata \033[K");
		} else {
			ParolaOk = ControllaParola(OV, r, c, l, parola);
		}
	} while (!ParolaOk);

	printf("\033[46;1H\033[K");

	/*                                         */
	/* Se la parola va bene la inserisce nello */
	/* schema                                  */
	/*                                         */
	if (ParolaOk && (parola[1] != 'q')) {
	    if ((p->parole = (char*) malloc(p->lunghezza)) == NULL) {
		 	printf("Memoria insufficiente\n");
			ChiudiDatabase();
			exit(1);
	}
		CaricaParola(p, parola);
		ScriviParola(p);
		p->trovata = TRUE;
		p->ctr	= 1;
		p->i	= 1;
		pc		= p->parole;
		for (int i = 0; i < p->lunghezza; i++){
			*pc = parola[i];
			++pc;
		}
		ApriDatabase();
		p = ProssimaParola();
		ChiudiDatabase();
	}

	return;

}

int ControllaParola(char OV, int r, int c, int l, char *p) {
	int i;

	for (i = 0; i < l; i++) {
		if (*p != schema[r][c] && schema[r][c] != ' ') {
			printf("\033[23;1HParola errata \033[K");
			return FALSE;
		}
		++p;
		OV == 'O' ? ++c : ++r;
	}

	return TRUE;
}
