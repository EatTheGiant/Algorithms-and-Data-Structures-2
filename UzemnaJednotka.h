#pragma once
#include <string>
#include <iostream>
#include "Obec.h"
#include "typUzemnejJednotky.h"
#include "structures/heap_monitor.h"
#include "structures/table/sorted_sequence_table.h"

using namespace std;
using namespace structures;
class UzemnaJednotka {
private:
	string nazov;
	typUzemnejJednotky typUJ;
	UzemnaJednotka* vyssiaUJ;
	SortedSequenceTable<string,UzemnaJednotka*>* nizsiaUJ;
	Obec* obec;
	int celkovyPocet = 0;

	double zastavanaPlocha = 0;
	double celkovaVymera = 0;
public:
	UzemnaJednotka(string nazov, typUzemnejJednotky typUJ, UzemnaJednotka* vyssiaUJ, SortedSequenceTable<string, UzemnaJednotka*>* nizsiaUJ, Obec* obec);

	SortedSequenceTable<string, UzemnaJednotka*>* getNizsia() { return nizsiaUJ; }

	string getNazov() {	return nazov; }

	typUzemnejJednotky getTypUJ() { return typUJ; }

	bool getPrislusnost(string nazov);

	UzemnaJednotka* getVyssiaUJ();

	Obec* getObec() { return obec; };

	void vytvorTabulku();

	bool pridajKraj(UzemnaJednotka* uj);

	void pridajObec(UzemnaJednotka* uj, string nazovOkresu, string nazovKraja);

	bool pridajOkres(UzemnaJednotka* uj, string nazovKraja, string nazovOkresu);

	int getPocetObyvatelov();

	int getPocetPreProd();

	int getPocetPoProd();

	int getPocetProduktivny();

	double getCelkovaVymera();

	double getZastavanaPlocha();

	double getZastavanost();

	void cisti();

	~UzemnaJednotka();
};