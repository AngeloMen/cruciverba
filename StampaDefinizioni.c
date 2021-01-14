#include <stdio.h>
#include "cruciverba.h"
#include "funzioni.h"
int system(const char *command);

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
/*
 * Stampa le statistiche
 *
*/
void stampastatistiche(void) {

	char risp;

	printf("Stampo le statistiche?(s=si, n=no)?\n");
	scanf("%c", &risp);
	if (risp != 's') 
		return;
	
	printf	("Totale definizioni orizzontali:\t\t\t%6i\n",			totaleOrizzontali);
	printf	("Totale definizioni verticali:\t\t\t%6i\n",			totaleVerticali);
	printf	("Totale definizioni:\t\t\t\t%6i\n\n",					totaleDefinizioni);
	printf	("Totale orizzontali BuildLista:\t\t\t%6i\n",			ctrOri);
	printf	("Totale verticali BuildLista:\t\t\t%6i\n",				ctrVer);
	printf	("Totale definizioni BuildLista:\t\t\t%6i\n\n",			ctrTot);
	printf	("Totale ricerche di parole per inserimento:\t%6i\n",	ctrSearchF);
	printf	("Totale ricerche di parole per blocco:\t\t%6i\n",		ctrSearchV);
	printf	("Totale ricerche di parole :\t\t\t%6i\n\n",			ctrSearchT);
	printf	("Totale cancellazioni di parole:\t\t\t%6i\n",			ctrCan);	

	return;
}
