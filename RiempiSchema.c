#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cruciverba.h"
#include "funzioni.h"
/*-----------------------------------------------------------------*/
/*             Inizio della funzione                               */
/*-----------------------------------------------------------------*/
int RiempiSchema(void) {

    p = inizio;
	AccodaLista(p);	
	while (1) {
		if (TrovaParola(p)) {							// Cerca la parola e se trovata
			p->trovata = TRUE;
			curdef++;
			p = ProssimaParola(p);						// si posiziona alla successiva
			if (p == NULL)								// se finita lista parole
				return 1;								//    schema risolto
		} else {
			p->trovata = FALSE;
			curdef--;
			p = ParolaPrecedente();						// Si posiziona sulla parola precedente
			if (p == NULL)								// Va alla precedente e sono finite
				return 0;								//    schema irrisolto
		}
	}

	return 0;

}
