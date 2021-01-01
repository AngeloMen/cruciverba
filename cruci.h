#ifndef CRUCI
#define CRUCI
#define FALSE  0
#define TRUE   1
#define MaxR  20    /* Massimo numero di righe ammesso      */
#define MaxC  40    /* Massimo numero di colonne ammesso    */
#define Maxl  40    /* Massimo lubghezza di una parola      */
#define DEBUG FALSE
#define NERA 'X'
// Per accesso al db		
#define DBSERVER "dbserver"
#define DBUSER "guest"
#define DBPWD ""

/*-----------------------------------------------------------------------*/
/*                     Variabili globali                                 */
/*-----------------------------------------------------------------------*/

extern int algoritmo;
extern int difficolta;			// Massimo livello di difficoltà per le parole da usare
extern int nonRandom;		// Mescolare le parole per non averle in ordine alfabetico
extern int nonValide;			// Mescolare le parole per non averle in ordine alfabetico
extern char schema[MaxR][MaxC];	/* Matrice che contiene lo schema       */
extern int ctrsch[MaxR][MaxC];	/* Serve a controllare la cancellazione */
								/* delle singole lettere.               */

extern struct passante{                   // punta alla verticale e orizzontale
	struct definizione *vert;       // che passano per la casella dello
	struct definizione *oriz;       
} passante;
extern struct passante casella[MaxR][MaxC];

extern int maxr, maxc;			// Dimensioni dello schema (righe, colonne)
extern int scrivereparola;      // Se true scrive la parola a video 
extern int LettoSchema;         // Se true ha caricato lo schema d file
extern int minl;                // Lunghezza minima parole da cercare
extern int difficolta;			// Massimo livello di difficoltà per le parole da usare
extern int contatore;			// Contatore delle ricerche
extern int totaleVerticali;     // Totale definizioni verticali
extern int totaleOrizzontali;   // Totale definizioni orizzontali

extern struct definizione {
	char OrVe;                       // "O"=Orizzontale, "V"=Verticale
	int numero;                     // Numero della definizione
	int lunghezza;                  // Lunghezza della parola
	int riga;                       // Coordinate iniziali
	int colonna;                    //   della parola
	int trovata;                    // Vero se già trovata
	int ctr;                        // Quante ne ha in lista
	int i;                          // A che punto della lista è arrivato
	char *parole;                  // Puntatore alla lista delle parole ok
	struct definizione *prec;        // Puntatore alla precedente definizione
	struct definizione *succ;        // Puntatore alla successiva definizione
} definizione;

extern struct definizione *inizio; // Indirizzo della prima definizione
extern struct definizione *fine;   // Indirizzo dell'ultima definizione
extern struct definizione *p;      // 

extern struct listaricerca {
	struct definizione *def;        // puntatore alla definizione
	struct listaricerca *prec;       // precedente elemento della lista
	struct listaricerca *succ;       // elemento successivo della lista
} dacercare;

extern struct listaricerca *prima;
extern struct listaricerca *ultima;
#endif
