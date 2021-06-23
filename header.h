#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

typedef struct racun {

	int id;
	char ime[20];
	char prezime[30];
	int broj_racuna;
	float stanje;
	struct  racun* nextRacun;

}RACUN;

void uvodniEkran();
void mainMenu();
void columnNames();
void miniMenu();
void izradaBaze();
void upitIzrade();
void unosNoveListe(RACUN*);
void unosNovogClana(RACUN*, RACUN*);

//-----------------------------------------------------------------------------

int brojanjeRacuna(RACUN*);
RACUN* ucitavanjeListe(RACUN*);
RACUN* upitZaIzradu(RACUN*);
RACUN* izradaListe(void);
RACUN* ubacivanjeNovogRacuna(RACUN*);
void bubbleSort(RACUN*);
void swap(RACUN*, RACUN*);
void ispisivanjeListe(RACUN*);
RACUN* pretrazivanjeListe(RACUN*, int);
RACUN* modificiranjeOdredjenogRacuna(RACUN**, RACUN*);
void brisanjeOdredjenogRacuna(RACUN**, RACUN*);
void printanjeOdredjenogRacuna(RACUN**, RACUN*);
RACUN* oslobadjanjeCijeleListe(RACUN*);
void spremanjeListe(RACUN*);
int krajPrograma(RACUN*);
#endif
