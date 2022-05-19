#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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



void dodavanjeVlaka() {
	FILE* fp = NULL;
	fp = fopen("vlakovi.bin", "rb+");

	if (fp == NULL) {
		perror("Dodavanje");
		exit(EXIT_FAILURE);
	}
	fread(&brojVlakova, sizeof(int), 1, fp);
	printf("Trenutni broj vlakova u voznom redu: %d", brojVlakova);

	VLAK temp;
	temp.id = brojVlakova + 1;
	brojac++;
	getchar();
	printf("\nUnesite polaziste vlaka: ");
	scanf(" %30[^\n]", temp.polaziste);
	getchar();
	printf("Unesite odrediste vlaka: ");
	scanf(" %30[^\n]", temp.odrediste);
	printf("Unesite vrijeme polaska vlaka: ");
	scanf(" %6[^\n]", temp.vrijemePolaska);
	printf("Unesite vrijeme dolaska vlaka: ");
	scanf(" %6[^\n]", temp.vrijemeDolaska);
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
		printf("  ID\tPolazak\t\tPolaziste\tOdrediste\tDolazak\n");
		printf("-----------------------------------------------------------------");
		for (int i = 0; i < brojVlakova; i++) {
			printf("\n  %d\t%s\t\t%s\t\t%s\t\t%s",
				(poljeVlakova + i)->id, (poljeVlakova + i)->vrijemePolaska,
				(poljeVlakova + i)->polaziste, (poljeVlakova + i)->odrediste,
				(poljeVlakova + i)->vrijemeDolaska);
		}
	}
}

void azuriranjeVlaka() {

}


void pretrazivanjeVoznogReda() {

}

void sortiranjeVoznogReda() {

}

void brisanjeVlaka(VLAK* poljeVlakova) {
	int brojac1 = 0;
	int trazeniVlak;
	printf("\n-----------------------------------------------------------------\n");
	printf("\nUnesite ID vlaka koji zelite obrisati [upisite 0 za izlazak]\n");
	scanf("%d", &trazeniVlak);
	if (trazeniVlak != 0) {
	FILE* fp = NULL;
	fp = fopen("vlakovi.bin", "wb");
	if (fp == NULL) {
		perror("Brisanje");
	}

	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);
		for (int i = 0; i < brojVlakova; i++) {
			if (trazeniVlak != (poljeVlakova + i)->id) {
				fwrite((poljeVlakova + i), sizeof(VLAK), 1, fp);
				brojac1++;
			}
		}
		system("cls");
		printf("Vlak s ID-om %d uspjesno izbrisan.", trazeniVlak);
		rewind(fp);
		fwrite(&brojac1, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		system("cls");
		printf("Nijedan vlak nije izbrisan, unos: %d", trazeniVlak);
	}
	

}

int zavrsetakPrograma(VLAK* poljeVlakova) {
	free(poljeVlakova);
	return 0;
}

int izbornik() {
	int odabir;
	printf("\n-----------------------------------------------------------------\n");
	printf("\t\t   Odaberite zeljenu opciju: \n\n");
	printf("\t\t   1 : Dodajavanje vlaka u vozni red\n");
	printf("\t\t   2 : Ispisivanje voznog reda\n");
	printf("\t\t   3 : Azuriranje postojeceg vlaka\n");
	printf("\t\t   4 : Pretrazivanje voznog reda\n");
	printf("\t\t   5 : Sortiranje voznog reda\n");
	printf("\t\t   6 : Brisanje vlaka iz voznog reda\n\n");
	printf("\t\t   0 : Izlaz iz programa\n");
	printf("-----------------------------------------------------------------\n");

	static VLAK* poljeVlakova = NULL;

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
		dodavanjeVlaka();
		break;
	case 2:
		if (poljeVlakova != NULL) {
			free(poljeVlakova);
			poljeVlakova = NULL;
		}
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		ispisVoznogReda(poljeVlakova);
		break;

	case 6:
		if (poljeVlakova != NULL) {
			free(poljeVlakova);
			poljeVlakova = NULL;
		}
		poljeVlakova = (VLAK*)ucitavanjeVlakova();
		ispisVoznogReda(poljeVlakova);
		

		if (poljeVlakova == NULL) {
			printf("Nema unesenih vlakova u vozni red");
			break;
		}
		brisanjeVlaka(poljeVlakova);
		break;
	}

	return odabir;

}