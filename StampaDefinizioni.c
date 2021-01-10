#include <stdio.h>
#include "cruciverba.h"
int system(const char *command);

/*------------------------------------------
 *  Prototipi
 * ----------------------------------------*/
void stampaparola(struct definizione *p);
/*-----------------------------------------------------------------*/
/*             Inizio della funzione                               */
/*-----------------------------------------------------------------*/
void StampaDefinizioni(void) {
	char risp;
	struct definizione *p;

	printf("Stampo le definizioni?(s=si, n=no)?\n");
	scanf("%c", &risp);
	scanf("%c", &risp);
	if (risp != 's')
		return;

	system("clear");
	printf("Orizzontali\n");

	p = inizio;

	while (1) {
		if (p->OrVe == 'O') {
			printf("Def: %2d, lung: %2d, riga: %2d, col:%2d\n", p->numero,
					p->lunghezza, (p->riga) + 1, (p->colonna) + 1);
			if (p->succ == NULL)
				break;
		}
		if (p->succ == NULL)
			break;
		p = p->succ;
	}

	p = inizio;
	printf("Verticali\n");
	while (1) {
		if (p->OrVe == 'V') {
			printf("Def: %2d, lung: %2d, riga: %2d, col:%2d\n", p->numero,
					p->lunghezza, (p->riga) + 1, (p->colonna) + 1);
			if (p->succ == NULL)
				break;
		}
		if (p->succ == NULL)
			break;
		p = p->succ;
	}
	printf("premi un tasto per proseguire?\n");
	scanf("%c", &risp);
	scanf("%c", &risp);
	system("clear");
	return;
}
void StampaSoluzioni(void) {
	char risp;
	struct definizione *p;
  	int r;
  	int c;


	printf("Stampo le soluzioni?(s=si, n=no)?\n");
	scanf("%c", &risp);
	scanf("%c", &risp);
	if (risp != 's')
		return;

	system("clear");
	printf("Orizzontali\n");

	p = inizio;

	while (1) {
		if (p->OrVe == 'O') {
			r = p->riga;
			c = p->colonna;
		    printf("Def: %2d. ", p->numero);
			stampaparola(p);
			if (p->succ == NULL)
				break;
		}
		   if (p->succ == NULL)
						break;
			p = p->succ;
	}

	p = inizio;
	printf("Verticali\n");
	while (1) {
		if (p->OrVe == 'V') {
			r = p->riga;
			c = p->colonna;
			printf("Def: %2d. ", p->numero);
			stampaparola(p);
			if (p->succ == NULL)
				break;
		}
		if (p->succ == NULL)
		   break;
        p = p->succ;
	}

	printf("premi un tasto per proseguire\n");
	scanf("%c", &risp);
	scanf("%c", &risp);
	system("clear");
	return;
}
