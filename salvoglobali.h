
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
