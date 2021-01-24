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
MYSQL mysql;
MYSQL_ROW riga;
MYSQL_RES *result;

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

	mysql_commit(&mysql);
	ChiudiDatabase();
}
/*-------------------------------------------------
 * Aggiorna livello di difficoltà e flag usare
 -------------------------------------------------*/
void AggiornaParola(struct definizione *pDef){
	int difficolta = INT_MAX, usare=INT_MAX;
	int Sql_Return;
	int CtrRighe, CtrCampi;
	char line[80];
	char where_part[100];
	char select[200] = "SELECT difficolta FROM vocabolo ";
	char update[200];
	char* parola;

	gotoxy(1,40);
	printf("%*.s", 40, "");

	parola = estraiparola(pDef);
	sprintf(where_part, "WHERE lung = %i AND parola  = '%s' ", pDef->lunghezza,  parola);

	strcat(select, where_part);
	Sql_Return	= mysql_query(&mysql, select);
	result		= mysql_store_result(&mysql);
	if ((riga	= mysql_fetch_row(result)) == 0) 
		printf("Riga non trovata\n");

	CtrRighe = mysql_num_rows(result);
	if (CtrRighe > 1) {
		printf("Più di una riga trovata");
		exit(1);
	}
	CtrCampi = mysql_field_count(&mysql);

	gotoxy(1,40);
	printf("%2d. %c: %s, difficoltà: %s", pDef->numero, pDef->OrVe, parola, riga[0]);

	gotoxy(1,41);
	printf("Inserisci i nuovi valori per  difficolta e uso: ");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%d\n%d\n", &difficolta, &usare);
	gotoxy(1,41);

	if ((usare		== INT_MAX) 
	&& (difficolta	== INT_MAX))
		return;

	if (difficolta != INT_MAX) {
		sprintf(update,"UPDATE vocabolo SET difficolta = %i ", difficolta);
		strcat(update, where_part);
		if ((Sql_Return = mysql_query(&mysql, update))){
			printf("errore update difficolta: %d", Sql_Return);;
		exit(1);
		}	
	}
	if (usare != INT_MAX) {
		strcpy(update,"");
		sprintf(update,"UPDATE vocabolo SET valido = %i ", usare);
		strcat(update, where_part);
		if ((Sql_Return = mysql_query(&mysql, update))) {
			printf("errore update valido: %d", Sql_Return);;
		exit(1);
		}
	}
	return;
}
/*-------------------------------------------------
 * Aggiorna livello di difficoltà e flag usare
 -------------------------------------------------*/
void AggiornaCtrUso(){
	char where_part[100];
	char update[40] = "UPDATE vocabolo set ctruso = ctruso + 1";
	char *parola;
	int	Sql_Return;
	struct definizione *pDef;
	char aggiorna[300];


	if (!Db_Aperto) 
		ApriDatabase();

	for (pDef = inizio; pDef != NULL; pDef=pDef->succ){
		parola = estraiparola(pDef);
		sprintf(where_part, " WHERE lung = %i and parola = '%s'",pDef->lunghezza, parola);
		strcpy(aggiorna,"");
		strcat(aggiorna,update);
		strcat(aggiorna,where_part);
		if ((Sql_Return = mysql_query(&mysql, aggiorna))){
			printf("errore update ctruso: %d", Sql_Return);;
		exit(1);
		}
	}

	mysql_commit(&mysql);
	ChiudiDatabase();
}
