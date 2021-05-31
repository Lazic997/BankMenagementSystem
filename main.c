#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

extern FILE* datoteka;

int main(void) {

	//----------------------------------//

	uvodniEkran(); //funkcija za ispis dizajna uvodnog ekrana
	getchar();

	//----------------------------------//

	datoteka = fopen("bazaRacuna.bin", "rb+");
	if (datoteka == NULL) {
		system("cls");
		izradaBaze();
		exit(EXIT_FAILURE);

	}

	int izbornik2;
	RACUN* glavaRacuna = NULL;
	RACUN* trazenaGlava = NULL;
	int kriterij;

	srand((unsigned)time(NULL));
	int izbornik = 1;

	glavaRacuna = ucitavanjeListe(glavaRacuna); //funkcija za ucitavanje stare liste iz datoteke
	if (glavaRacuna == NULL) {
		system("cls");
		printf("\n\tLISTA RACUNA JE PRAZNA! KREIRAJTE NOVU!\n\t");
		getchar();
	}

	int brojRacuna = brojanjeRacuna(glavaRacuna);

	while (izbornik) {

		mainMenu(); //funkcija za ispis dizajna mainmenu-a

		scanf("%d", &izbornik2);

		switch (izbornik2) {


		case 1:  // izrada liste
			if (glavaRacuna == NULL) {
				glavaRacuna = izradaListe();
				break;
			}
			else {
				glavaRacuna = upitZaIzradu(glavaRacuna); //upit za izradu nove liste, jer ce se stara obrisati
				if (glavaRacuna == NULL) {
					return 1;
				}
			}
			break;
		case 2: //otvaranje novog racuna
			glavaRacuna = ubacivanjeNovogRacuna(glavaRacuna);
			break;
		case 3: // ispis svih racuna s liste
			ispisivanjeListe(glavaRacuna, brojRacuna);
			break;
		case 4:// modificiraj racun, kasnije cu napraviti
			system("cls");

			printf("\n\tZA MODIFICIRANJE RACUNA, UNESITE BROJ RACUNA:\n\t");
			scanf("%d", &kriterij);
			trazenaGlava = pretrazivanjeListe(glavaRacuna, kriterij);
			glavaRacuna = modificiranjeOdredjenogRacuna(&glavaRacuna, trazenaGlava);
			break;
		case 5:	// provjeri stanje racuna, ispisivanje odredjenog clana
			system("cls");

			printf("\n\tZA PROVJERU STANJA RACUNA, UNESITE BROJ RACUNA:\n\t");
			scanf("%d", &kriterij);
			trazenaGlava = pretrazivanjeListe(glavaRacuna, kriterij);
			printanjeOdredjenogRacuna(&glavaRacuna, trazenaGlava);
			break;
		case 6: //zatvori racun, brisanje odredjenog racuna
			system("cls");

			printf("\n\tZA ZATVARANJE RACUNA, UNESITE BROJ RACUNA:\n\t");
			scanf("%d", &kriterij);
			trazenaGlava = pretrazivanjeListe(glavaRacuna, kriterij);
			brisanjeOdredjenogRacuna(&glavaRacuna, trazenaGlava);
			break;
		case 7:  // zatvaranje programa
			izbornik = krajPrograma(glavaRacuna);
			break;
		default:
			printf("\n\tPOGRESNO UNESEN ODABIR!\n");
			izbornik = 0;
			break;
		}

	}

	return 0;
}