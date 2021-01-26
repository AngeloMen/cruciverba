#include <stdio.h>
#include <stdlib.h>
#include <argz.h>
#include <argp.h>
#include "cruciverba.h"
#include "funzioni.h"

const char *argp_program_bug_address = "angelo.meneghini@gmail.com";
const char *argp_program_version = "version 1.4.0";
struct arguments
{
	char *argz;
	size_t argz_len;
};
struct argp_option options[] = {
		{ "trovaparola",	't',		"NUM",	0,	"Metodo di scelta delle parole da cercare"},
		{ "prossimaparola",	'p',		"NUM",	0,	"Algoritmo per la ricerca della parola successiva"},
		{ "livello",		'l',		"NUM",	0,	"Livello massimo di diffficoltà delle parole"},
		{ "file-input",		'f',	"FILENAME", 0,	"Nome file da cui caricare lo schema"},
		{ "not-random",		'n',			0,  0,	"Ricerca parole in ordine alfabetico"},
		{ "invalide",		'i',			0,  0,	"Includi anche le parole marcate non valide"},
		{ 0 }
};

/*-------------------------------------------------
 * Parsing dei parametri di input
 *-----------------------------------------------*/
static int parse_opt	(int key, char *arg
						,struct argp_state *state)
{
	switch (key)
	{
		case 't':{
				algoritmo = atoi(arg);
				if ((algoritmo < 1) || (algoritmo > 2)){
					printf("l'algoritmo deve essere compreso fra 1 e 2.\n");
					return 1;
				}	
				break;
				}
		case 'p':{
				sceltaprox= atoi(arg);
				if ((sceltaprox < 0) || (sceltaprox > 2)){
					printf("l'algoritmo di ricerca deve esser compreso fra 0 e 2.\n");
					return 1;
				}	
				break;
				}
		case 'l':{
				difficolta = atoi(arg);
				if ((difficolta < 1) || (difficolta > 5)){
					printf("la difficoltà deve essere compresa fra 1 e 5.\n");
					return 1;
				}	
				break;
				}
		case 'f':{
				if (!(LeggiSchema(arg))){
					printf("File dello schema %s non trovato.\n",arg);
					return 1;
				}	
				LettoSchema = TRUE;
				break;
				}	
		case 'n':{
				nonRandom = TRUE;	
				}	
				break;
		case 'i':{
				nonValide = TRUE;	
				}	
				break;
				
	}
	return 0;
}

/*-------------------------------------------------------------------------*/
/*  Legge lo schema da file                                                */
/*-------------------------------------------------------------------------*/
int LeggiSchema(char *NomeFile) {
	FILE *fp;

	if ((fp = fopen(NomeFile, "rb")) == NULL) {
		printf("Impossibile aprire il file.\n");
		return FALSE;
	}

	fread(&maxr, sizeof(int), 1, fp);
	fread(&maxc, sizeof(int), 1, fp);
	fread(schema, sizeof(schema), 1, fp);

	fclose(fp);

	NomeSchema = NomeFile;

	return TRUE;
}
/*
 *
 *
 * */

int AnalisiParametri(int argc, char **argv){

	int		arg_count = 2;
    struct	argp argp = {options, parse_opt,  "WORD [WORD]"};

	return argp_parse (&argp, argc, argv, 0, 0, &arg_count);
}
