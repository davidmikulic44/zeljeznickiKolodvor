#ifndef HEADER_H
#define HEADER_H

typedef struct vlak {
	int id;
	char polaziste[30];
	char odrediste[30];
	char vrijemePolaska[6];
	char vrijemeDolaska[6];
}VLAK;

	int izbornik();
	void kreiranjeDatoteke();
	void dodavanjeVlaka();
	void ispisVoznogReda(const VLAK* const poljeVlakova);
	void brisanjeVlaka(VLAK* poljeVlakova);
	int zavrsetakPrograma(VLAK* poljeVlakova);
	void pretvaranjeUCapsLock(char string[]);
	int provjeraUnosa(char string[]);

#endif // HEADER_H
