#include <stdlib.h>
#include <stdio.h>
#include <cups/cups.h>
#include "cruciverba.h"
/*-----------------------------------------------------------------------*/
/*                     prototipi delle funzioni                          */
/*-----------------------------------------------------------------------*/
int		AnalisiParametri(int, char*[]);					// Analizza i parametri di lancio
void	LeggiDimensioni(void);							// Legge le dimensioni
void	DisegnaSchema(void);							//
void	PulisciSchema(void);							// Inizializza lo schema a spazi
void	MettiCaselleNere(void);							// mette le caselle nere
void	StampaDefinizioni(void);						// Stampa le definizioni trovate
void	Definizioni(void);								// Ricerca le coordinate di inizio
void	LeggiDaTastiera(void);							// Legge le prime parole da tastiera
void	SalvaSchema(void);								// salva lo schema se richiesto
int		ApriDatabase(void);								// Apertura del database
int		RiempiSchema(void);								// Riempie lo schema
int		ChiudiDatabase(void);							// Chiusura del database
void	StampaSoluzioni(void);							//
void	PremiTasto(int, int);

/*-----------------------------------------------------------------------*/
/*                     variabili globali                                 */
/*-----------------------------------------------------------------------*/
char	schema[MaxR][MaxC];	/* Matrice che contiene lo schema           */
int		ctrsch[MaxR][MaxC]; /* Serve a controllare la cancellazione     */
							/* delle singole lettere.                   */
int		maxr, maxc;			/* Dimensioni dello schema (righe, colonne) */
int		contatore = 0;
int		totaleVerticali = 0;
int		totaleOrizzontali = 0;
int		ctrdef = 1;
enum	DATABASE_STATUS{Open, Closed, Invalid};

struct passante passante;
struct passante casella[MaxR][MaxC];

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

struct definizione definizione;
struct definizione *inizio;        // Indirizzo della prima definizione
struct definizione *fine;          // Indirizzo dell'ultima definizione
struct definizione *p;             // 
struct listaricerca dacercare;
struct listaricerca *prima;
struct listaricerca *ultima;

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

	StampaDefinizioni();						// Chiede se stanoarele definizioni

	if (!(ApriDatabase())) {					// Apre il database contenente il dizionario
		puts("Errata apertura del database\n");
		return 1;
	}

	if (RiempiSchema()) {						// Ciclo di riempimento dello schema;
		PremiTasto(50, 1);
		DisegnaSchema();
	} else {
		puts("\033[24;1HSchema irrisolto\033[K");
	}

	ChiudiDatabase();							// Chiudi database

	StampaSoluzioni();

	return 0;

}
