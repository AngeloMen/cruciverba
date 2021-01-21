#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <mysql.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include "cruciverba.h"
#include "funzioni.h"
MYSQL mysql;
/*-------------------------------------------------
 * Aggiorna livello di difficoltà e flag usare
 -------------------------------------------------*/
void AggiornamentoDatabase() {
	int risp;
	struct definizione *pDef;

	gotoxy(1,40);
	printf("%*.s", 40, "");
	gotoxy(1,40);
	printf("Vuoi aggiornare il database? ");
	risp = get_answer();
	if (risp == 'n') 
		return;

	if (!Db_Aperto) 
		ApriDatabase();

	for (pDef = inizio; pDef != NULL; pDef=pDef->succ){
		AggiornaParola(pDef);
	}

	ChiudiDatabase();
}
/*-------------------------------------------------
 * Aggiorna livello di difficoltà e flag usare
 -------------------------------------------------*/
void AggiornaParola(struct definizione *pDef){
	int difficolta = INT_MAX, usare=INT_MAX;
	char line[80];

	gotoxy(1,40);
	printf("%*.s", 40, "");
	gotoxy(1,40);
	stampasoluzione(pDef);
	printf(", difficoltà e flag usare: ");

	fgets(line, sizeof(line), stdin);
	sscanf(line, "%d %d\n", &difficolta, &usare);

	if ((usare == INT_MAX) 
	&& (difficolta == INT_MAX))
		return;

	gotoxy(1,41);
	printf("%*.s", 50, "");
	gotoxy(1,41);
	printf("Difficoltà=%d, usare=%d", difficolta, usare);


}
