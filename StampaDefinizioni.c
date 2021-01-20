#include <stdio.h>
#include <unistd.h>
#include "cruciverba.h"
#include "funzioni.h"
int system(const char *command);

/*-----------------------------------------------------------------*/
/*             Stampa la lista delle definizioni                   */
/*-----------------------------------------------------------------*/
void StampaDefinizioni(void) {
	int risp;
	struct definizione *p;
	int x, y;

	gotoxy(1,40);
	printf("Stampo le definizioni?(s=si, n=no)?");
	risp = get_answer();
	if (risp != 's')
		return;

	x = maxc*4 + 10;
	y = 2;
	gotoxy(x,y);
	printf("ORIZZONTALI");

	for (p = inizio; p != NULL; p=p->succ) {
		if (p->OrVe == 'O') {
			y++;
			gotoxy(x,y);
			printf("%2d. [%d:%d-%d]", p->numero, (p->riga) + 1, (p->colonna) + 1, p->lunghezza);
		}
	}

	x = x + 40;
	y = 2;
	gotoxy(x,y);
	printf("VERTICALI\n");

	for (p = inizio; p != NULL; p=p->succ) {
		if (p->OrVe == 'V') {
			y++;
			gotoxy(x,y);
			printf("%2d. [%d:%d-%d]", p->numero, (p->riga) + 1, (p->colonna) + 1, p->lunghezza);
		}
	}

	gotoxy(1,40);
	printf("Premi INVIO per continuare%*s",40, "");
	PremiTasto();
	return;
}
/*-----------------------------------------------------------------*/
/*             Stampa le soluzioni                                 */
/*-----------------------------------------------------------------*/
void StampaSoluzioni(void) {
	int risp;
	struct definizione *p;
	int x, y;


	gotoxy(1,40);
	printf("Stampo le soluzioni?(s=si, n=no)?");
	risp = get_answer();
	if (risp != 's')
		return;

	x = maxc*4 + 10;
	y = 2;
	gotoxy(x,y);

	printf("ORIZZONTALI\n");
	for (p = inizio; p != NULL; p=p->succ) {
		if (p->OrVe == 'O') {
			y++;
			gotoxy(x,y);
		    stampasoluzione(p);
		}
	}

	x = x +45;
	y = 2;
	gotoxy(x,y);

	printf("VERTICALI\n");
	for (p = inizio; p != NULL; p=p->succ) {
		if (p->OrVe == 'V') {
			y++;
			gotoxy(x,y);
		    stampasoluzione(p);
		}
	}

	return;
}
/*
 * Stampa le statistiche
 *
*/
void stampastatistiche(void) {

	int risp;

	gotoxy(1,40);
	printf("Stampo le statistiche?(s=si, n=no)?");
	risp = get_answer();
	if (risp != 's') 
		return;
	
	putchar('\n');
	for (int i = 0; i < 54; putchar('='), i++);
	putchar('\n');
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
	for (int i = 0; i < 54; putchar('='), i++);
	putchar('\n');
	putchar('\n');

	return;
}
