#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cruciverba.h"
#include "funzioni.h"
/* -------------------------------------------------------
 * Prototipi delle funzioni 
 -------------------------------------------------------*/
struct	definizione* ParolaPrecedente(void);			//
struct	definizione* ProssimaParola(struct definizione*);				//
int		TrovaParola(struct definizione*);				//
int		TrovaParola_1(struct definizione*);				//
int		TrovaParola_2(struct definizione*);				//
int		CercaParole(struct definizione*, int);			//
int		piene(struct definizione*);						//
void	AccodaLista(struct definizione*);				//
void	CancellaParola(struct definizione*);			//
void	ScriviParola(struct definizione*);				//
int		SiIncrociano(struct definizione*, struct definizione*);
void	stamparicerca(struct definizione *p, int cancella);

/*-----------------------------------------------------------------*/
/*             Inizio della funzione                               */
/*-----------------------------------------------------------------*/
int RiempiSchema(void) {

    p = inizio;

	while (1) {
		if (TrovaParola(p)) {							// Cerca la parola e se trovata
			p->trovata = TRUE;
			p = ProssimaParola(p);						// si posiziona alla successiva
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
