#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

FILE* datoteka = NULL;

void uvodniEkran() {
	printf("\n\n\n\t************************");
	printf("\n\n\n\t\tBANK\n\n\t\tMANAGMENT\n\n\t\tSYSTEM");
	printf("\n\n\n\t************************");
	printf("\n\n\n\t: SRDJAN LAZIC :");
	printf("\n\n\n\t FERIT, Sveuciliste J. J. Strossmayera Osijek");
}

void mainMenu() {
	system("cls");

	printf("\n\n\n\tMAIN MENU");
	printf("\n\n\t01. STVORI LISTU RACUNA");
	printf("\n\n\t02. OTVORI NOVI RACUN");
	printf("\n\n\t03. LISTA SVIH RACUNA");
	printf("\n\n\t04. MODIFICIRAJ RACUN");
	printf("\n\n\t05. PROVJERI STANJE RACUNA");
	printf("\n\n\t06. ZATVORI RACUN");
	printf("\n\n\t07. IZLAZ");
	printf("\n\n\tOdaberi opciju (1-7)\n\t");

}

void columnNames() {
	printf("\n\t********************************************************************************************");
	printf("\n\tID:\tIme i Prezime:\t\tBroj racuna:\tStanje:");
	printf("\n\t********************************************************************************************\n");
}

void miniMenu() {
	printf("\n\n\t01. UPLATA NOVCA");
	printf("\n\n\t02. ISPLATA NOVCA");
	printf("\n\n\t03. IZLAZ");
	printf("\n\n\tOdaberi opciju (1-3)\n\t");
}

void izradaBaze() {
	printf("\n\n\t***********************************************************\n");
	printf("\n\tBAZA PODATAKA RACUNA NIJE POSTOJALA NA DISKU!\n");
	datoteka = fopen("bazaRacuna.bin", "wb");
	fclose(datoteka);
	printf("\n\tBAZA PODATAKA SADA JE KREIRANA, POKRENITE PROGRAM PONOVNO!\n");
	printf("\n\t***********************************************************\n");
}

void upitIzrade() {
	printf("\n\n\t***********************************************************\n");
	printf("\n\tLISTA RACUNA VEC POSTOJI!\n");
	printf("\n\tDA LI STE SIGURNI DA ZELITE IZRADITI NOVU LISTU? STARA LISTA CE SE OBRISATI! da/ne\n");
	printf("\n\t***********************************************************\n\t");
}

void unosNoveListe(RACUN* glavaRacuna) {
	printf("\n\tKREIRANJE NOVE LISTE:\n");
	printf("\n\tUnesite id korisnika racuna:\n\t");
	scanf("%d", &glavaRacuna->id);
	printf("\n\tUnesite ime korisnika racuna:\n\t");
	scanf("%s", glavaRacuna->ime);
	printf("\n\tUnesite prezime korisnika racuna:\n\t");
	scanf("%s", glavaRacuna->prezime);
	glavaRacuna->broj_racuna = 1000 + (float)rand() / RAND_MAX * (9999 - 1000); // IBAN ili broj racuna je nasumisno generiran broj :D
	glavaRacuna->stanje = 0;
	glavaRacuna->nextRacun = NULL;
}

void unosNovogClana(RACUN* novaGlavaRacuna, RACUN* glavaRacuna) {
	printf("\n\tUNOS NOVOG CLANA:\n");
	printf("\n\tUnesite id korisnika racuna:\n\t");
	scanf("%d", &novaGlavaRacuna->id);
	printf("\n\tUnesite ime korisnika racuna:\n\t");
	scanf("%s", novaGlavaRacuna->ime);
	printf("\n\tUnesite prezime korisnika racuna:\n\t");
	scanf("%s", novaGlavaRacuna->prezime);
	novaGlavaRacuna->broj_racuna = 1000 + (float)rand() / RAND_MAX * (9999 - 1000); // IBAN ili broj racuna je nasumisno generiran broj
	novaGlavaRacuna->stanje = 0; //pocetno stanje na racunu je 0
	novaGlavaRacuna->nextRacun = glavaRacuna;
}




//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int brojanjeRacuna(RACUN* prijelaznaGlava) {
	int brojac = 0;
	while (prijelaznaGlava) {
		brojac++;
		prijelaznaGlava = prijelaznaGlava->nextRacun;
	}

	return brojac;
}


RACUN* ucitavanjeListe(RACUN* glavaRacuna) { // funkcija radi, ali ucitava pocetnu 0

	fseek(datoteka, 0, SEEK_END);
	int size = ftell(datoteka);
	rewind(datoteka);

	if (size == 0) {
		return NULL;
	}
	else {
		while (!feof(datoteka)) {

			RACUN* ucitanaGlava = (RACUN*)calloc(1, sizeof(RACUN));
			fread(ucitanaGlava, sizeof(RACUN), 1, datoteka);
			
			if (ucitanaGlava == NULL) {
				break;
			}

			else {

				ucitanaGlava->nextRacun = glavaRacuna;
				glavaRacuna = ucitanaGlava;
			}

		}

		return glavaRacuna;

	}
}

RACUN* upitZaIzradu(RACUN* glavaRacuna) {

	system("cls");
	upitIzrade();

	char zavrsniOdabir[10] = "";

	do {
		scanf("%s", zavrsniOdabir);


		if (strcmp(zavrsniOdabir, "da") == 0) {

			glavaRacuna = NULL;
			glavaRacuna = izradaListe();
			return glavaRacuna;
		}
		else if (strcmp(zavrsniOdabir, "ne") == 0) {

			printf("\n\tVRACANJE U MENI\n");
			return glavaRacuna;

		}
		else if (strcmp(zavrsniOdabir,"da") !=0 || strcmp(zavrsniOdabir, "ne") !=0) {
			system("cls");
			printf("\n\tPOGRESAN UNOS! UNESITE ODGOVOR PONOVNO!\n");
			printf("\n\tDA LI STE SIGURNI DA ZELITE IZRADITI NOVU LISTU? da/ne\n\t");
		}
	} while (strcmp(zavrsniOdabir, "da") !=0 || strcmp(zavrsniOdabir, "ne") !=0);
	return glavaRacuna;
}

RACUN* izradaListe(void) {

	system("cls");
	RACUN* glavaRacuna = (RACUN*)calloc(1, sizeof(RACUN));
	if (glavaRacuna == 0) {
		perror("Kreiranje");
		return NULL;
	}
	else {

		unosNoveListe(glavaRacuna);

	}
	return glavaRacuna;
}

RACUN* ubacivanjeNovogRacuna(RACUN* glavaRacuna) {

	system("cls");
	RACUN* novaGlavaRacuna = (RACUN*)calloc(1, sizeof(RACUN));
	if (novaGlavaRacuna == NULL) {
		perror("Ubacivanje");
		return glavaRacuna;
	}
	else {

		unosNovogClana(novaGlavaRacuna, glavaRacuna);

	}
	return novaGlavaRacuna;
}

void bubbleSort(RACUN* glavaRacuna)
{
	RACUN* pGlava = NULL;
	RACUN* tempGlava = NULL;

	pGlava = glavaRacuna; //temp node to hold node data and next link
	while (pGlava != NULL)
	{
		tempGlava = pGlava;
		while (tempGlava->nextRacun != NULL)//travel till the second last element 
		{
			if (tempGlava->ime[0] > tempGlava->nextRacun->ime[0])// compare the data of the nodes 
			{
				swap(tempGlava, tempGlava->nextRacun);
			}
			tempGlava = tempGlava->nextRacun;    // move to the next element 
		}
		pGlava = pGlava->nextRacun;    // move to the next node
	}
}

/* function to swap data of two nodes a and b*/
void swap(RACUN* a, RACUN* b)
{

	int tempId = 0;
	char tempIme[20] = "";
	char tempprezime[30] = "";
	int tempbroj_racuna = 0;
	float tempstanje = 0;

	tempId = a->id;
	strcpy(tempIme, a->ime);
	strcpy(tempprezime, a->prezime);
	tempbroj_racuna = a->broj_racuna;
	tempstanje = a->stanje;

	a->id = b->id;
	strcpy(a->ime, b->ime);
	strcpy(a->prezime, b->prezime);
	a->broj_racuna = b->broj_racuna;
	a->stanje = b->stanje;

	b->id = tempId;
	strcpy(b->ime, tempIme);
	strcpy(b->prezime, tempprezime);
	b->broj_racuna = tempbroj_racuna;
	b->stanje = tempstanje;

}

void ispisivanjeListe(RACUN* prijelaznaGlava) {

	system("cls");

	bubbleSort(prijelaznaGlava);

	if (prijelaznaGlava == NULL) {
		printf("\n\tLISTA RACUNA JE PRAZNA!\n\t");
		getchar();
	}

	else {

		columnNames(); // funkcija za ispis zaglavlja
		while (prijelaznaGlava) {

			printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", prijelaznaGlava->id, prijelaznaGlava->ime, prijelaznaGlava->prezime, prijelaznaGlava->broj_racuna, prijelaznaGlava->stanje);
			prijelaznaGlava = prijelaznaGlava->nextRacun;

		}
		getchar();
	}
	getchar();

}

RACUN* pretrazivanjeListe(RACUN* prijelaznaGlava, int kriterij) {
	while (prijelaznaGlava) {
		if (prijelaznaGlava->broj_racuna == kriterij) {
			return prijelaznaGlava;
		}
		else {
			prijelaznaGlava = prijelaznaGlava->nextRacun;

		}

	}
	return NULL;
}

RACUN* modificiranjeOdredjenogRacuna(RACUN** glavaRacuna, RACUN* trazenaGlava) {
	system("cls");
	int pV = 1;
	float uplata;
	float isplata;

	if (trazenaGlava == NULL) {
		printf("\n\tTRAZENI RACUN NIJE PRONADJEN!\n\t");
		getchar();
		getchar();
		return *glavaRacuna;
	}
	else if (*glavaRacuna == trazenaGlava) {

		columnNames();
		printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
		printf("\n\tTRAZENI RACUN JE PRONADJEN!\n\t");

		while (pV) {
			miniMenu(); // funkcija za printanje mini menua za modifikacije racuna
			scanf("%d", &pV);

			switch (pV) {
			case 1:
				system("cls");
				columnNames();
				printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
				printf("\n\tUNESITE KOLICINU NOVCA KOJU ZELITE UPLATITI NA RACUN\n\t");

				scanf("%f", &uplata);
				trazenaGlava->stanje += uplata;

				break;
			case 2:
				system("cls");
				columnNames();
				printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
				printf("\n\tUNESITE KOLICINU NOVCA KOJU ZELITE ISPLATITI S RACUNA\n\t");

				scanf("%f", &isplata);

				if (trazenaGlava->stanje > 0)
					trazenaGlava->stanje -= isplata;
				else
					printf("\n\tPOGRESAN UNOS ILI NEDOVOLJNO STANJE NA RACUNU!\n\t");


				break;
			case 3:
				pV = 0;
				break;
			}

		}

		return *glavaRacuna;

	}
	else {
		RACUN* prijelaznaGlava = *glavaRacuna;
		while (prijelaznaGlava->nextRacun) {
			prijelaznaGlava = prijelaznaGlava->nextRacun;

			if (prijelaznaGlava == trazenaGlava) {

				columnNames();
				printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
				printf("\n\tTRAZENI RACUN JE PRONADJEN!\n\t");

				while (pV) {
					miniMenu(); // funkcija za printanje mimi menua iz modifikacije racuna
					scanf("%d", &pV);

					switch (pV) {
					case 1:
						system("cls");
						columnNames();
						printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
						printf("\n\tUNESITE KOLICINU NOVCA KOJU ZELITE UPLATITI NA RACUN\n\t");
						scanf("%f", &uplata);
						trazenaGlava->stanje += uplata;

						break;
					case 2:
						system("cls");
						columnNames();
						printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
						printf("\n\tUNESITE KOLICINU NOVCA KOJU ZELITE ISPLATITI S RACUNA\n\t");

						scanf("%f", &isplata);
						if (trazenaGlava->stanje > 0)
							trazenaGlava->stanje -= isplata;
						else
							printf("\n\tPOGRESAN UNOS ILI NEDOVOLJNO STANJE NA RACUNU!\n\t");

						break;
					case 3:
						pV = 0;
						break;
					}

				}
				getchar();
				return *glavaRacuna;

			}

		}



	}
	getchar();
	return *glavaRacuna;


}

void brisanjeOdredjenogRacuna(RACUN** glavaRacuna, RACUN* trazenaGlava) {
	system("cls");
	if (trazenaGlava == NULL) {
		printf("\n\tTRAZENI RACUN NIJE PRONADJEN!\n\t");
		getchar();
	}
	else if (*glavaRacuna == trazenaGlava) {
		*glavaRacuna = (*glavaRacuna)->nextRacun;
		free(trazenaGlava);
		printf("\n\tTRAZENI RACUN JE ZATVOREN!\n\t");
		getchar();
	}
	else {
		RACUN* prijelaznaGlava = *glavaRacuna;
		while (prijelaznaGlava->nextRacun) {
			prijelaznaGlava->nextRacun = trazenaGlava->nextRacun;
			free(trazenaGlava);
			printf("\n\tTRAZENI RACUN JE ZATVOREN!\n\t");
			break;
		}
		getchar();
		prijelaznaGlava = prijelaznaGlava->nextRacun;

	}
	getchar();
}

void printanjeOdredjenogRacuna(RACUN** glavaRacuna, RACUN* trazenaGlava) {
	system("cls");
	if (trazenaGlava == NULL) {
		printf("\n\tTRAZENI RACUN NIJE PRONADJEN!\n\t");
		getchar();
		return;

	}
	else if (*glavaRacuna == trazenaGlava) {

		columnNames();
		printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
		printf("\n\tTRAZENI RACUN JE PRONADJEN!\n");

		getchar();
	}
	else {
		RACUN* prijelaznaGlava = *glavaRacuna;
		while (prijelaznaGlava->nextRacun) {

			prijelaznaGlava = prijelaznaGlava->nextRacun;

			if (prijelaznaGlava == trazenaGlava) {


				columnNames();
				printf("\t%d\t%s\t%s\t\t%d\t\t%.2f\n\n", trazenaGlava->id, trazenaGlava->ime, trazenaGlava->prezime, trazenaGlava->broj_racuna, trazenaGlava->stanje);
				printf("\n\tTRAZENI RACUN JE PRONADJEN!\n");

				break;
			}


		}
		getchar();


	}
	getchar();
}

RACUN* oslobadjanjeCijeleListe(RACUN* prijelaznaGlava) {

	RACUN* glavaKojaSeBrise = NULL;

	while (prijelaznaGlava) {
		glavaKojaSeBrise = prijelaznaGlava;
		prijelaznaGlava = prijelaznaGlava->nextRacun;
		free(glavaKojaSeBrise);
		// printf("Oslobodjen cvor : %p\n", glavaKojaSeBrise);
	}
	return NULL;
}

void spremanjeListe(RACUN* prijelaznaGlava) {

	fclose(datoteka); //prvo zatvaram datoteku za citanje

	datoteka = fopen("bazaRacuna.bin", "wb"); //otvaram ju kao zapisivanje da bih prepisao prethodan sadrzaj
	if (datoteka == NULL) {
		system("cls");
		izradaBaze();
		exit(EXIT_FAILURE);

	}

	while (prijelaznaGlava) {

		fwrite(prijelaznaGlava, sizeof(RACUN), 1, datoteka);
		prijelaznaGlava = prijelaznaGlava->nextRacun;

	}
}

int krajPrograma(RACUN* glavaRacuna) {

	system("cls");
	printf("\n\n\n\tDA LI STE SIGURNI DA ZELITE ZAVRSITI PROGRAM? da/ne\n\t");

	char zavrsniOdabir[10] = { '\0' };

	do {
		scanf("%s", zavrsniOdabir);


		if (strcmp(zavrsniOdabir, "da") == 0) {

			spremanjeListe(glavaRacuna); //funkcija za spremanje liste u datoteku
			glavaRacuna = oslobadjanjeCijeleListe(glavaRacuna);
			fclose(datoteka);
			return 0;

		}
		else if (strcmp(zavrsniOdabir, "ne") == 0) {

			spremanjeListe(glavaRacuna);
			printf("\n\tVRACANJE U MENI\n");

			return 1;

		}
		else if (strcmp(zavrsniOdabir, "da") != 0 || strcmp(zavrsniOdabir, "ne") != 0) {
			system("cls");
			printf("\n\tPOGRESAN UNOS! UNESITE ODGOVOR PONOVNO!\n");
			printf("\n\tDA LI STE SIGURNI DA ZELITE ZAVRSITI PROGRAM? da/ne\n\t");
		}
	} while (strcmp(zavrsniOdabir, "da") != 0 || strcmp(zavrsniOdabir, "ne") != 0);
	return 0;
}
