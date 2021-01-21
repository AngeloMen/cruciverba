#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <cups/cups.h>
#include "cruciverba.h"
#include "funzioni.h"

/*-----------------------------------------------------------------------*/
/*                     variabili globali                                 */
/*-----------------------------------------------------------------------*/
char	schema[MaxR][MaxC];
int		ctrsch[MaxR][MaxC];
int		maxr, maxc;
struct	definizione definizione;
struct	definizione *p;             // 
struct	listaricerca dacercare;
struct	listaricerca *prima;
struct	listaricerca *ultima;
struct	passante casella[MaxR][MaxC];
int		Db_Aperto = FALSE;

MYSQL mysql;

int	contatore			= 0;
int	ctrdef				= 1;

int	totaleVerticali		= 0;
int	totaleOrizzontali	= 0;
int	totaleDefinizioni	= 0;
int ctrOri			    = 0; 
int ctrVer			    = 0; 
int ctrCan			    = 0; 
int ctrTot			    = 0; 
int ctrSearchF		    = 0; 
int ctrSearchV		    = 0; 
int ctrSearchT		    = 0; 

struct definizione *inizio	= NULL;			// Indirizzo della prima definizione
struct definizione *fine	= NULL;			// Indirizzo dell'ultima definizione
/*-----------------------------------------------------------------------*/
/*                parametri ricevuti da linea comando                    */
/*-----------------------------------------------------------------------*/
int scrivereparola = TRUE;  // Scrivo o meno le parole a video?
int algoritmo = 1;			// Metodo di ricerca della prossima parola da trovare
int difficolta = 5;			// Massimo livello di difficoltà per le parole da usare
int LettoSchema;            // Lo schema è stato letto da file?
int minl;                   // La lunghezza minima della parola da cercare
int nonRandom = FALSE;		// Ricerca in ordine alfabetico o casuale
int nonValide;				// Includi anche le parole marcate nel db come non valide

/*-----------------------------------------------------------------------*/
/*                     Programma principale                              */
/*-----------------------------------------------------------------------*/
int main(int argc, char *argv[]) {

    AnalisiParametri(argc, argv);

	if (!(LettoSchema)) {						// Se non caricato uno schema precedente
		LeggiDimensioni();						//   legge le dimensioni da tastiera
		PulisciSchema();						//   e inizializza lo schema a spazi 
	}

	DisegnaSchema();							// disegna lo schema a video

	MettiCaselleNere();							// mette le caselle nere

	DisegnaSchema();							// disegna lo schema finale a video

												// Calcola indici di riga e colonna
	Definizioni();								// delle parole e la loro lunghezza

												// Legge (opzionale) le prime defi-
	LeggiDaTastiera();							// nizioni da tastiera

	DisegnaSchema();							// disegna lo schema finale a video

	SalvaSchema();								// Chiede se salvare lo schema su file

	DisegnaSchema();							// disegna lo schema finale a video

	StampaDefinizioni();						// Chiede se stampare le  definizioni

	BuildSearchList();

	if (!(ApriDatabase())) {					// Apre il database contenente il dizionario
		puts("Errata apertura del database\n");
		return 1;
	}

	if (RiempiSchema()) {						// Ciclo di riempimento dello schema;
		DisegnaSchema();
	} else {
		puts("\033[24;1HSchema irrisolto\033[K");
	}

	ChiudiDatabase();							// Chiudi database

	StampaSoluzioni();

	stampastatistiche();

	AggiornamentoDatabase();

	return 0;

}
