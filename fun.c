#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojVlakova = 0;
static int brojac = 0;

void* ucitavanjeVlakova() {
	FILE* fp = fopen("vlakovi.bin", "rb");
	if (fp == NULL) {
		printf("Nijedan vlak nije unesen u vozni red\n\n");
		return NULL;
		exit(EXIT_FAILURE);
	}
	fread(&brojVlakova, sizeof(int), 1, fp);
	VLAK* poljeVlakova = NULL;
	poljeVlakova = (VLAK*)calloc(brojVlakova, sizeof(VLAK));
	if (poljeVlakova == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
		exit(EXIT_FAILURE);
	}
	fread(poljeVlakova, sizeof(VLAK), brojVlakova, fp);
	fclose(fp);
	return poljeVlakova;
}

void kreiranjeDatoteke() {
	FILE* fp = NULL;
	fp = fopen("vlakovi.bin", "wb");

	if (fp == NULL) {
		perror("Kreiranje");
	}

	fwrite(&brojVlakova, sizeof(int), 1, fp);
	fclose(fp);
}

void pretvaranjeUCapsLock(char string[]) {
	int i = 0, len = strlen(string);

	for (i = 0; i < len; i++) {
		if (string[i] >= 'a' && string[i] <= 'z') {
			string[i] = string[i] - 32;
		}
	}
}

int provjeraUnosaStringa(char string[]) {
	int i,provjera = 0;

	for (i = 0; i < strlen(string); i++) {
		if ((string[i] < 'A' || string[i]>'Z') && (string[i] < 'a' || string[i]>'z') && (string[i]!='-') && (string[i]!=' '))
			provjera++;
	}

	return provjera;
}

int provjeraUnosaVremena(char string[]) {
	int i, provjera = 0, len=strlen(string);

	if (len < 4 || len>5)
		return -1;

	if (string[0] < '0' || string[0]>'9')
		return -1;

	if (string[1] >= '0' && string[1] <= '9'){
		if (string[0] > '2')
			return -1;

		if (string[0] == '2')
			if (string[1] > '3')
				return -1;
	}
	if (string[len - 1] < '0' || string[len - 1]>'9')
		return -1;

	if (string[len - 2] < '0' || string[len - 2]>'5')
		return -1;

	for (i = 0; i < strlen(string); i++) {
		if (string[i] < '0' || string[i]>'9') {
			if (string[i] != ':')
				return -1;
			if (string[i] == ':')
				provjera++;
		}
	}

	if (provjera == 0 || provjera > 1)
		provjera = -1;

	return provjera;
}

void dodavanjeVlaka(VLAK* poljeVlakova) {
	int provjera = 0,i;
	FILE* fp = NULL;
	fp = fopen("vlakovi.bin", "rb+");

	if (fp == NULL) {
		perror("Dodavanje");
		exit(EXIT_FAILURE);
	}
	fread(&brojVlakova, sizeof(int), 1, fp);
	printf("Trenutni broj vlakova u voznom redu: %d", brojVlakova);

	VLAK temp;
	
	if ((poljeVlakova + 0)->id != 1)
		temp.id = 1;
	else
		temp.id = brojVlakova + 1;
	brojac++;
	do {
		provjera = 0;
		printf("\nUnesite polaziste vlaka: ");
		scanf(" %30[^\n]", temp.polaziste);

		if (strcmp(temp.polaziste,"0")==0){
			system("cls");
			return;
		}
		provjera = provjeraUnosaStringa(temp.polaziste);

		if (provjera != 0)
			printf("Pogresan unos.\n");
	} while (provjera != 0);
	pretvaranjeUCapsLock(temp.polaziste);


	do {
		provjera = 0;
		printf("Unesite odrediste vlaka: ");
		scanf(" %30[^\n]", temp.odrediste);

		if (strcmp(temp.odrediste, "0") == 0) {
			system("cls");
			return;
		}

		provjera = provjeraUnosaStringa(temp.odrediste);

		if (provjera != 0)
			printf("Pogresan unos.\n");
	} while (provjera != 0);
	pretvaranjeUCapsLock(temp.odrediste);

	do {
		provjera = 0;
		printf("Unesite vrijeme polaska vlaka [h:mm]: ");
		scanf(" %6[^\n]", temp.vrijemePolaska);

		if (strcmp(temp.vrijemePolaska, "0") == 0) {
			system("cls");
			return;
		}

		provjera = provjeraUnosaVremena(temp.vrijemePolaska);

		if (provjera == -1)
			printf("Pogresan unos.\n");
	} while (provjera == -1);


	do {
		provjera = 0;
		printf("Unesite vrijeme dolaska vlaka [h:mm]: ");
		scanf(" %6[^\n]", temp.vrijemeDolaska);

		if (strcmp(temp.vrijemeDolaska, "0") == 0) {
			system("cls");
			return;
		}

		provjera = provjeraUnosaVremena(temp.vrijemeDolaska);

		if (provjera == -1)
			printf("Pogresan unos.\n");

	} while (provjera == -1);

	fseek(fp, sizeof(VLAK) * brojVlakova, SEEK_CUR);
	fwrite(&temp, sizeof(VLAK), 1, fp);
	rewind(fp);
	brojVlakova++;
	fwrite(&brojVlakova, sizeof(int), 1, fp);
	fclose(fp);
	system("cls");
	printf("Novi vlak uspjesno dodan u vozni red.");
}

void ispisVoznogReda(const VLAK* const poljeVlakova) {
	if (poljeVlakova == NULL) {
		printf("Polje vlakova je prazno");
		return;
	}

	if (brojVlakova == 0) {
		printf("Nijedan vlak nije unesen u vozni red.");
	}
	else {
		printf("  ID\tPolazak\t\t\t   Polaziste\t\t\t   Odrediste\t\t\tDolazak\n");
		printf("---------------------------------------------------------------------------------------------------------");
		for (int i = 0; i < brojVlakova; i++) {
			printf("\n  %2d\t%5s\t\t%20s\t\t%20s\t\t\t  %5s",
				(poljeVlakova + i)->id, (poljeVlakova + i)->vrijemePolaska,
				(poljeVlakova + i)->polaziste, (poljeVlakova + i)->odrediste,
				(poljeVlakova + i)->vrijemeDolaska);
		}
	}
}

void azuriranjeVlaka() {

}


void* pretrazivanjeVoznogRedaID(VLAK* poljeVlakova) {
	if (poljeVlakova == NULL) {
		printf("Polje vlakova je prazno");
		return NULL;
	}

	int i, trazeniID;

	printf("Unesite ID trazenog vlaka: ");
	scanf("%d", &trazeniID);
	system("cls");
	for (i = 0; i < brojVlakova; i++) {
		if (trazeniID == (poljeVlakova + i)->id) {
			printf("  ID\tPolazak\t\t\t   Polaziste\t\t\t   Odrediste\t\t\tDolazak\n");
			printf("---------------------------------------------------------------------------------------------------------");

			printf("\n  %2d\t%5s\t\t%20s\t\t%20s\t\t\t  %5s",
				(poljeVlakova + i)->id, (poljeVlakova + i)->vrijemePolaska,
				(poljeVlakova + i)->polaziste, (poljeVlakova + i)->odrediste,
				(poljeVlakova + i)->vrijemeDolaska);
			return (poljeVlakova + i);
		}
	}


	return NULL;
}

void* pretrazivanjeVoznogRedaPolaziste(VLAK* poljeVlakova) {
	if (poljeVlakova == NULL) {
		printf("Polje vlakova je prazno");
		return NULL;
	}

	char trazenoPolaziste[30];
	int i, provjera = 0;

	printf("Unesite polaziste trazenog vlaka: ");
	scanf(" %30[^\n]", trazenoPolaziste);

	pretvaranjeUCapsLock(trazenoPolaziste);

	system("cls");
	for (i = 0; i < brojVlakova; i++) {
		if (strcmp(trazenoPolaziste, (poljeVlakova + i)->polaziste) == 0) {
			if (provjera == 0) {
				provjera++;
				printf("  ID\tPolazak\t\t\t   Polaziste\t\t\t   Odrediste\t\t\tDolazak\n");
				printf("---------------------------------------------------------------------------------------------------------");
			}
			printf("\n  %2d\t%5s\t\t%20s\t\t%20s\t\t\t  %5s",
				(poljeVlakova + i)->id, (poljeVlakova + i)->vrijemePolaska,
				(poljeVlakova + i)->polaziste, (poljeVlakova + i)->odrediste,
				(poljeVlakova + i)->vrijemeDolaska);
		}
	}
	if (provjera == 0)
		printf("Nije pronadjen nijedan vlak s polazistem '%s'.", trazenoPolaziste);
	return NULL;
}

void* pretrazivanjeVoznogRedaOdrediste(VLAK* poljeVlakova) {
	if (poljeVlakova == NULL) {
		printf("Polje vlakova je prazno");
		return NULL;
	}

	char trazenoOdrediste[30];
	int i, provjera = 0;

	printf("Unesite odrediste trazenog vlaka: ");
	scanf(" %30[^\n]", trazenoOdrediste);

	pretvaranjeUCapsLock(trazenoOdrediste);

	system("cls");
	for (i = 0; i < brojVlakova; i++) {
		if (strcmp(trazenoOdrediste, (poljeVlakova + i)->odrediste) == 0) {
			if (provjera == 0) {
				provjera++;
				printf("  ID\tPolazak\t\t\t   Polaziste\t\t\t   Odrediste\t\t\tDolazak\n");
				printf("---------------------------------------------------------------------------------------------------------");
			}
			printf("\n  %2d\t%5s\t\t%20s\t\t%20s\t\t\t  %5s",
				(poljeVlakova + i)->id, (poljeVlakova + i)->vrijemePolaska,
				(poljeVlakova + i)->polaziste, (poljeVlakova + i)->odrediste,
				(poljeVlakova + i)->vrijemeDolaska);
		}
	}
	if (provjera == 0)
		printf("Nije pronadjen nijedan vlak s odredistem '%s'.", trazenoOdrediste);
	return NULL;
}

void sortiranjeVoznogReda() {

}

void brisanjeVlaka(VLAK* poljeVlakova) {
	int i, trazeniVlak, brojac1 = 0;

	printf("\n---------------------------------------------------------------------------------------------------------\n");
	printf("\nUnesite ID vlaka koji zelite obrisati [upisite 0 za izlazak, -1 za brisanje svih vlakova]\n");
	scanf("%d", &trazeniVlak);
	if (trazeniVlak != 0) {
		FILE* fp = NULL;
		fp = fopen("vlakovi.bin", "wb");
		if (fp == NULL) {
			perror("Brisanje");
		}

		if (trazeniVlak != -1) {
			rewind(fp);
			fseek(fp, sizeof(int), SEEK_CUR);
			for (i = 0; i < brojVlakova; i++) {
				if (trazeniVlak != (poljeVlakova + i)->id) {
					fwrite((poljeVlakova + i), sizeof(VLAK), 1, fp);
					brojac1++;
				}
			}
			system("cls");
			if (brojac1 != 0)
				printf("Vlak s ID-om %d uspjesno izbrisan.", trazeniVlak);
			else
				printf("Vlak s ID-om %d ne postoji.", trazeniVlak);
		}
		else {
			rewind(fp);
			fseek(fp, sizeof(int), SEEK_CUR);
			for (int i = 0; i < brojVlakova; i++) {
				fwrite((poljeVlakova + i), sizeof(VLAK), 1, fp);
			}
			system("cls");
			printf("Svi vlakovi izbrisani.");
		}
		rewind(fp);
		fwrite(&brojac1, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		system("cls");
		printf("Brisanje otkazano.");
	}


}

int zavrsetakPrograma(VLAK* poljeVlakova) {
	free(poljeVlakova);
	return 0;
}

int izbornikZaPretrazivanje() {
	int odabir;
	printf("\n---------------------------------------------------------------------------------------------------------\n");
	printf("\t\t      Po cemu zelite pretrazivati: \n\n");
	printf("\t\t  1 : Po ID-u\n");
	printf("\t\t  2 : Po polazistu\n");
	printf("\t\t  3 : Po odredistu\n");
	printf("\t\t  0 : Izlaz iz izbornika za pretrazivanje\n");
	printf("---------------------------------------------------------------------------------------------------------\n");

	printf("ODABIR: ");
	scanf("%d", &odabir);
	system("cls");

	static VLAK* pronadjeniVlak;
	static VLAK* poljeVlakova;

	switch (odabir) {
	case 1:
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		pronadjeniVlak = (VLAK*)pretrazivanjeVoznogRedaID(poljeVlakova);
		break;

	case 2:
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		pronadjeniVlak = (VLAK*)pretrazivanjeVoznogRedaPolaziste(poljeVlakova);
		break;

	case 3:
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		pronadjeniVlak = (VLAK*)pretrazivanjeVoznogRedaOdrediste(poljeVlakova);
		break;

	case 0:
		break;

	default:
		printf("Odabrana opcija ne postoji.");
		izbornikZaPretrazivanje();
		break;
	}


	return odabir;
}

int izbornik() {
	int odabir;
	printf("\n---------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t      Odaberite zeljenu opciju: \n\n");
	printf("\t\t\t\t  1 : Dodajavanje vlaka u vozni red\n");
	printf("\t\t\t\t  2 : Ispisivanje voznog reda\n");
	printf("\t\t\t\t  3 : Azuriranje postojeceg vlaka\n");
	printf("\t\t\t\t  4 : Pretrazivanje voznog reda\n");
	printf("\t\t\t\t  5 : Sortiranje voznog reda\n");
	printf("\t\t\t\t  6 : Brisanje vlaka iz voznog reda\n\n");
	printf("\t\t\t\t  0 : Izlaz iz programa\n");
	printf("---------------------------------------------------------------------------------------------------------\n");

	static VLAK* poljeVlakova = NULL;
	static VLAK* pronadjeniVlak = NULL;

	printf("ODABIR: ");
	scanf("%d", &odabir);
	system("cls");
	switch (odabir) {
	case 0:
		zavrsetakPrograma(poljeVlakova);
		break;

	case 1:
		ucitavanjeVlakova();
		if (brojVlakova == 0) {
			kreiranjeDatoteke();
		}
		dodavanjeVlaka(poljeVlakova);
		break;

	case 2:
		if (poljeVlakova != NULL) {
			free(poljeVlakova);
			poljeVlakova = NULL;
		}
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		ispisVoznogReda(poljeVlakova);
		break;

	case 4:
		izbornikZaPretrazivanje();
		break;

	case 6:
		if (poljeVlakova != NULL) {
			free(poljeVlakova);
			poljeVlakova = NULL;
		}
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		ispisVoznogReda(poljeVlakova);


		if (poljeVlakova == NULL) {
			printf("Nema unesenih vlakova u vozni red.");
			break;
		}
		brisanjeVlaka(poljeVlakova);
		break;

	default:
		printf("Odabrana opcija ne postoji.");
		break;
	}

	return odabir;

}
