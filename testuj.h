#pragma once
#include "structures/heap_monitor.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Obec.h"
#include "UzemnaJednotka.h"
#include "typUzemnejJednotky.h"
#include "Other/Triedenie.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"

#include "Kriteria/KUJNazov.h"
#include "Kriteria/KUJZastavanost.h"
#include "Kriteria/KUJCelkVym.h"
#include "Kriteria/KUJPocetPoProd.h"
#include "Kriteria/KUJPocetObyv.h"
#include "Kriteria/KUJPocetPreProd.h"
#include "Kriteria/KUJPocetProduktivny.h"
#include "Kriteria/KUJPrislusnost.h"
#include "Kriteria/KUJZastavana.h"
#include "Kriteria/KUJZastavanost.h"
#include "Kriteria/KUJTyp.h"

#include "Filtre/FPodHodnoty.h"
#include "Filtre/FPodIntervalu.h"
#include "Filtre/FUJNazov.h"
#include "Filtre/FUJZastavanost.h"
#include "Filtre/FUJPocetObyv.h"
#include "Filtre/FUJTyp.h"
#include "Filtre/FUJPrislusnost.h"

using namespace std;
using namespace structures;
class testuj
{
private:
	SortedSequenceTable<string, UzemnaJednotka*>* tabulkaVsetko;
	SortedSequenceTable<string, UzemnaJednotka*>* krajeTabulka;
	SortedSequenceTable<string, UzemnaJednotka*>* okresyTabulka;
	SortedSequenceTable<string, UzemnaJednotka*>* obceTabulka;
	UnsortedSequenceTable<string, UzemnaJednotka*>* cistaTabulka;
	SortedSequenceTable<string, UzemnaJednotka*>* pomTabulka;
	UzemnaJednotka* slovensko;
public:
	testuj();

	void ziskajVyssiuUJ(UzemnaJednotka* UJ);

	void nacitajObce();

	void dajPrislusnost(string nazov, SortedSequenceTable<string, UzemnaJednotka*>* tabulkaPrisl);

	void vypisFilter(UnsortedSequenceTable<string, UzemnaJednotka*>* tabulka);

	void filtrujPocetObyvUJ(SortedSequenceTable<string, UzemnaJednotka*>* tabulka);

	void filtrujNazovUJ(SortedSequenceTable<string, UzemnaJednotka*>* tabulka);

	void filtrujZastavanost(SortedSequenceTable<string, UzemnaJednotka*>* tabulka);

	void spusti();

	~testuj();
};

