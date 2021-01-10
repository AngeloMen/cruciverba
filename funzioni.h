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
int LeggiSchema(char *NomeFile);
int		ChiudiDatabase(void);							// Chiusura del database
void	StampaSoluzioni(void);							//
void	PremiTasto(int, int);
int InizioOriz(int, int);
int InizioVert(int, int);
int CalcolaLungVert(int, int);
int CalcolaLungOriz(int, int);
void AggiungiDefinizione(char, int, int);       // BColonna di inizio
int	ControllaParola(char, int, int, int, char*);	//
int		ApriDatabase(void);								// Apertura del database
int		ChiudiDatabase(void);							// Chiusura del database
void ScriviCasella(int, int);
