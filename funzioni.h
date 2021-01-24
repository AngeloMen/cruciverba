#ifndef FUNZIONI
#define FUNZIONI
#include "cruciverba.h"
int		AnalisiParametri(int, char*[]);					// Analizza i parametri di lancio
int		ApriDatabase(void);								// Apertura del database
int		CalcolaLungOriz(int, int);
int		CalcolaLungVert(int, int);
int		ChiudiDatabase(void);							// Chiusura del database
int		ControllaParola(char, int, int, int, char*);	//
int		InizioOriz(int, int);
int		InizioVert(int, int);
int		LeggiSchema(char *NomeFile);
int		RiempiSchema(void);								// Riempie lo schema
void	AggiungiDefinizione(char, int, int);       // BColonna di inizio
void	Definizioni(void);								// Ricerca le coordinate di inizio
void	DisegnaSchema(void);							//
void	LeggiDaTastiera(void);							// Legge le prime parole da tastiera
void	LeggiDimensioni(void);							// Legge le dimensioni
void	MettiCaselleNere(void);							// mette le caselle nere
void	PremiTasto(void);        
void	PulisciSchema(void);							// Inizializza lo schema a spazi
void	SalvaSchema(void);								// salva lo schema se richiesto
void	ScriviCasella(int, int);
void	StampaDefinizioni(void);						// Stampa le definizioni trovate
void	StampaSoluzioni(void);							//
void	stamparicerca(struct definizione *definizione, int);
struct	definizione* ParolaPrecedente(void);			//
struct	definizione* ProssimaParola(struct definizione*);				//
struct	definizione* ProssimaParola0(struct definizione*);				//
struct	definizione* ProssimaParola1(struct definizione*);				//
int		TrovaParola(struct definizione*);				//
int		TrovaParola_1(struct definizione*);				//
int		TrovaParola_2(struct definizione*);				//
void	AccodaLista(struct definizione*);
void	CancellaParola(struct definizione*);
int		piene(struct definizione*);
void	ScriviParola(struct definizione*);
int		SiIncrociano(struct definizione*, struct definizione*);
int		SiIncrociano(struct definizione*, struct definizione*);
int		CercaParole(struct definizione*, int);
int		CercaParole(struct definizione*, int);			//
void	evidenzia(struct definizione*);					//
void	lettura(struct definizione *p);					//
void	CaricaParola(struct definizione*, char*);		//
int		usata(struct definizione*);
int		bloccante(struct definizione*);
void	cancella_bloccanti(struct definizione*, struct definizione *pd);
void	cancella_da_stringa(struct definizione*, char, int);
void	elimina_parola(char*, int);
void	comprimi_stringa(char*);
void	BuildSearchList(void);
void	stampaparola(struct definizione*);
void	stampaparola_i(struct definizione*, int i);
void	stampastatistiche(void);
int		get_answer(void);
int		get_scelta(void);
void	stampasoluzione(struct definizione*);
void	AggiornaParola(struct definizione*);
void	AggiornamentoDatabase(void);
int		IncrociCompleti(struct definizione*);
char*	estraiparola(struct definizione*);
void	AggiornaCtrUso(void);
#endif
