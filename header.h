#ifndef HEADER_H
#define HEADER_H

	typedef struct vlak {
		int id;
		char polaziste[30];
		char odrediste[30];
		char vrijemePolaska[6];
		char vrijemeDolaska[6];
	}VLAK;


	void* ucitavanjeVlakova();
	void kreiranjeDatoteke();
	void pretvaranjeUCapsLock(char string[]);
	int provjeraUnosaStringa(char string[]);
	int provjeraUnosaVremena(char string[]);
	void dodavanjeVlaka(VLAK* poljeVlakova);
	void ispisVoznogReda(VLAK* poljeVlakova);
	void* pretrazivanjeVoznogRedaID(VLAK* poljeVlakova);
	void* pretrazivanjeVoznogRedaPolaziste(VLAK* poljeVlakova);
	void* pretrazivanjeVoznogRedaOdrediste(VLAK* poljeVlakova);
	void brisanjeVlaka(VLAK* poljeVlakova);
	int zavrsetakPrograma(VLAK* poljeVlakova);
	int izbornikZaPretrazivanje();
	int izbornik();


#endif // HEADER_H
