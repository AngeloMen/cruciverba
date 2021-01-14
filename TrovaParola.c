#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <mysql.h>
#include <ctype.h>
#include <time.h>
#include "cruciverba.h"
#include "funzioni.h"
MYSQL mysql;

/*-------------------------------------------------*/
/*  ricerca la parola                              */
/*-------------------------------------------------*/
int TrovaParola(struct definizione *p) {

	switch (algoritmo) {
	case 1:
		return TrovaParola_1(p);
		break;
	default:
		return TrovaParola_2(p);
		break;
	}
}

/*-------------------------------------------------*/
/*  ricerca la parola con il primo algoritmo       */
/*-------------------------------------------------*/
int TrovaParola_1(struct definizione *p) {
	char *parola;

	if (p->ctr == 0) {					// Se non ancora andato in cerca
		CercaParole(p, FALSE);			//   interroga il database e carica i risultati
		if (p->ctr == 0) {				//   e se non ha trovato parole
			return FALSE;				//     ritorna FALSE
		}								//   se trovate parole
		p->i = 0;						//     punta alla prima
	}

	++(p->i);							// passa alla prossima parola in memoria
	if (p->i > p->ctr) {				// se finite le parole in memoria
		free(p->parole);				//    libera la memoria
		p->ctr = 0;						//    azzera il contatore
		return FALSE;					//    ritorna non trovato
	}

	while ((usata(p))					// Verifica che la parola non sia già in uso
       || (bloccante(p))){				// e che non blocchi su quelle che incrocia
		++(p->i);
		if (p->i > p->ctr){
			return FALSE;
		}
	}

	p->trovata = TRUE;
	parola = p->parole + ((p->lunghezza) * ((p->i) - 1));
	CaricaParola(p, parola);
	if (scrivereparola)
		ScriviParola(p);
	return TRUE;

}
/*-------------------------------------------------*/
/*  ricerca la parola con il secondo algoritmo     */
/*-------------------------------------------------*/
int TrovaParola_2(struct definizione *p) {
	char *parola;
//	return FALSE;

	if (p->ctr == 0) {					// Se non ancora andato in cerca
		CercaParole(p, FALSE);			//   interroga il database e carica i risultati
		if (p->ctr == 0) {				//   e se non ha trovato parole
			return FALSE;				//     ritorna FALSE
		}								//   se trovate parole
		p->i = 0;						//     punta alla prima
	}

	++(p->i);							// passa alla prossima parola in memoria
	if (p->i > p->ctr) {				// se finite le parole in memoria
		free(p->parole);				//    libera la memoria
		p->ctr = 0;						//    azzera il contatore
		return FALSE;					//    ritorna non trovato
	}

	while (usata(p)) {
		++(p->i);
		if (p->i > p->ctr)
			return FALSE;
	}

	p->trovata = TRUE;
	parola = p->parole + ((p->lunghezza) * ((p->i) - 1));
	CaricaParola(p, parola);
	if (scrivereparola)
		ScriviParola(p);
	return TRUE;
}

/*------------------------------------------------------*/
/*  Verifica che la parola non sia già nello schema     */
/*------------------------------------------------------*/
int usata(struct definizione *p) {
	struct listaricerca *pl;
	struct definizione *pd;
	char *p1, *p2;

	pl = prima;
	p1 = p->parole + ((p->lunghezza) * ((p->i) - 1));

	while ((pl != NULL) && (pl->def != p)) {
		pd = pl->def;
		if (pd->trovata) {
			p2 = pd->parole + ((pd->lunghezza) * ((pd->i) - 1));
			if ((p->lunghezza) == (pd->lunghezza)) {
				if (!(strncmp(p1, p2, p->lunghezza)))
					return TRUE;
			}
		}
		pl = pl->succ;
	}

	
	return FALSE;

}
/* -----------------------------------  */
/*        Apertura del database         */
/* -----------------------------------  */
int ApriDatabase() {
	/*                                    */
	/* Inizializza MySQL                  */
	/*                                    */
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "memorizza");

	//if (!mysql_real_connect(&mysql, DBSERVER, DBUSER, DBPWD,
	if (!mysql_real_connect(&mysql, DBSERVER, DBUSER, DBPWD,
			"dizionario", 0, NULL, 0)) {
		fprintf(stderr, "errore di connessione al server: %s\n",
				mysql_error(&mysql));
		return 0;
		Db_status = Invalid;
	}
	Db_status = Open;
	return 1;
}
/* -----------------------------------  */
/*        Chiusura del database         */
/* -----------------------------------  */
int ChiudiDatabase() {
	mysql_close(&mysql);     // Chiusura del database
	Db_status = Closed;
	return 1;
}

/*-------------------------------------------------*/
/*  ricerca nel database le parole che vanno bene  */
/*-------------------------------------------------*/
int CercaParole(struct definizione *p, int SoloCtr) {
	char select[200];
	char parola[Maxl];
	unsigned long *lunghezze;
	unsigned int ctr;
	char *pc;
	int i, r, c;
	int ir, ic;

	MYSQL_RES *result;
	MYSQL_ROW riga;

	ctrSearchT++;
	if (SoloCtr)
		ctrSearchV++;
	else 
		ctrSearchF++;

	r = p->riga;
	c = p->colonna;

	(p->OrVe == 'O') ? (ic = 1, ir = 0) : (ic = 0, ir = 1);

	/*--------------------------*/
	/*     Prepara la select    */
	/*--------------------------*/
	for (i = 0; i < p->lunghezza; ++i) {
		(schema[r][c] == ' ') ? (parola[i] = '_') : (parola[i] = schema[r][c]);
		c = c + ic;
		r = r + ir;
	}

	parola[i] = '\0';

	sprintf(select, "SELECT parola "
			"FROM vocabolo "
			"WHERE lung=%i "
			"AND parola     LIKE '%.*s' "
			"AND difficolta <=   %i "
			"AND valido      = TRUE", p->lunghezza, p->lunghezza, parola,
			difficolta);
	if ((SoloCtr)
	||  (nonRandom)) 
		strcat(select, " order by parola");
	else
		strcat(select, " order by RAND()");
		

	/*---------------------------------------------------------*/
	/*  Esegue la select preparata                             */
	/*---------------------------------------------------------*/
	if (mysql_real_query(&mysql, select, strlen(select))) {
		fprintf(stderr, "select errata");
		ChiudiDatabase();
		exit(1);
	}

	/*                                    */
	/* ctr = numero di parole trovate     */
	/*                                    */
	result = mysql_store_result(&mysql);
	ctr = (int) mysql_affected_rows(&mysql);

	// Se richiesto solo il conteggio
	// restituisce il numero di righe trovate
	if (SoloCtr) {
		mysql_free_result(result);
		return ctr;
	}

	p->ctr = ctr;

	/*                                                          */
	/* Alloca lo spazio necessario a contenere tutte le parole  */
	/* più un carattere per lo zero finale di chiusura stringa */
	if ((p->parole = (char*) malloc(p->lunghezza * p->ctr + 1)) == NULL) {
		printf("Memoria insufficiente\n");
		ChiudiDatabase();
		exit(1);
	}

	pc = p->parole;

	while ((riga = mysql_fetch_row(result))) {
		lunghezze = mysql_fetch_lengths(result);

		for (i = 0; i < lunghezze[0]; i++) {
			*pc = riga[0][i];
			++pc;
		}
	}
	*pc = '\0';

	mysql_free_result(result);

/*
	if (mescola)
		if (contatore % 7)
			mescolaparole(p->parole, p->lunghezza, p->ctr);
	contatore++;
*/
	#if DEBUG
	printf("Parole trovate: %s.\n", p->parole);
	#endif
	return 0;
}
/*-----------------------------------------------------------*/
/* Verifica che la parola com'è collocata non blocchi la ri- */
/* cerca di altre parole.                                    */
/*-----------------------------------------------------------*/
int bloccante(struct definizione *p) {
	char *parola;
	int riga, colonna, bloccante = FALSE;

	parola	=	p->parole + ((p->lunghezza) * ((p->i) - 1));
	riga	=	p->riga;
	colonna	=	p->colonna;
	CaricaParola(p, parola);

	switch (p->OrVe) {
		case 'O': {
			for (int l = 0; l < p->lunghezza; l++){
				if ((casella[riga][colonna].vert != NULL)) 
				  if (!(casella[riga][colonna].vert->trovata))
				    if ((CercaParole(casella[riga][colonna].vert, TRUE)) == 0) {
		                cancella_bloccanti(p, casella[riga][colonna].vert);
  	  		      	 	CancellaParola(p);
			    		bloccante = TRUE;
				}
			    colonna++;
			}
			break;
		}
				
		case 'V': {
			for (int l = 0; l < p->lunghezza; l++){
				if ((casella[riga][colonna].oriz != NULL)) 
				  if (!(casella[riga][colonna].oriz->trovata))
			       if ((CercaParole(casella[riga][colonna].oriz, TRUE)) == 0) {
                       cancella_bloccanti(p, casella[riga][colonna].oriz);
  				 	   CancellaParola(p);
					   bloccante = TRUE;
				}
				riga++;
		   }
     		break;
		}

	}
    if (!(bloccante)) 
		CancellaParola(p);
	return bloccante;
}

/*-----------------------------------------------------------*/
/* Elimina le altre parole che  bloccano in base a quella    */
/* che ha già trovato bloccante                              */
/*-----------------------------------------------------------*/
void cancella_bloccanti(struct definizione *p, struct definizione *pd) {

	if ((p->OrVe == 'V') && (pd->OrVe == 'O'))
		cancella_da_stringa(p, schema[pd->riga][p->colonna], pd->riga - p->riga + 1);
	else
		if ((p->OrVe == 'O') && (pd->OrVe == 'V'))
			cancella_da_stringa(p, schema[p->riga][pd->colonna], pd->colonna - p->colonna + 1);

	return;
}

/*-----------------------------------------------------------*/
/* Elimina le altre parole che  bloccano in base a quella    */
/* che ha già trovato bloccante                              */
/*-----------------------------------------------------------*/
void cancella_da_stringa(struct definizione *p, char lettera, int posizione) {
	 int ctr ,i;
 
    ctr	= p->ctr;
	i	= p->i;

	for (i = p->i; i <= p->ctr; i++) {
		if (*(p->parole + p->lunghezza * (i - 1) + (posizione - 1)) == lettera) {
			elimina_parola((p->parole + p->lunghezza * (i - 1)), p->lunghezza);
			ctr--;
		}	
	}	
	comprimi_stringa(p->parole);	
	p->ctr = ctr;

	return;
}
/*-----------------------------------------------------------*/
/* Elimina le altre parole che  bloccano in base a quella    */
/* che ha già trovato bloccante                              */
/*-----------------------------------------------------------*/
void taglia(char *p, int inizio, int lunghezza) {


	int l = strlen(p);
	
		if (lunghezza < 0)				lunghezza = l - inizio;
		if (inizio + lunghezza > l)		lunghezza = l - inizio;

		memmove(p + inizio, p + inizio + lunghezza, l - lunghezza + 1);

}
/*-----------------------------------------------------------*/
/* Abblenca la parola che non va bene.                       */
/*-----------------------------------------------------------*/
void elimina_parola(char *p, int lunghezza) {
	int i;

	for (i = 1; i <= lunghezza; i++){
		*p = ' ';
		p++;
	}		 

	ctrCan++;
	return;

}
void comprimi_stringa(char* s) {
	char *d  = s;
	do {while(isspace(*s)) s++; } while((*d++ = *s++));
}
