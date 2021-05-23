#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../structures/table/sorted_sequence_table.h"
#include "Obec.h"
#include "UzemnaJednotka.h"
#include "../structures/table/sequence_table.h"
#include "typUzemnejJednotky.h"
using namespace std;

class VyberTestu {
private:
	structures::SortedSequenceTable<std::string, Obec*>* obceDataTabulka;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* SKTabulka;
	UzemnaJednotka* slovensko;
public:
	void vytvorTabulky() {
		obceDataTabulka = new structures::SortedSequenceTable<std::string, Obec*>();
		SKTabulka = new structures::SortedSequenceTable<std::string, UzemnaJednotka*>;
		slovensko = new UzemnaJednotka("Slovensko",typUzemnejJednotky::Slovensko,nullptr,nullptr,nullptr);
		SKTabulka->insert("Slovensko",slovensko);
	
	}


	void nacitajObce() {
		std::ifstream data;
		data.open("CSV/1 Obce SR.csv");
		std::ifstream data2;
		data2.open("CSV/2 Uzemne Clenenie SR.csv");
		int predprod, produktivny, poprod, celkovavymera, zastavana;
		string line, line2,pomocna, nazov, nazovObce,nazovOkresu, nazovKraja;
		std::ofstream tester;
		tester.open("CSV/TestObce.csv");
		if (data.is_open()) {
			while (getline(data, line)) {
				stringstream textStream(line);
				getline(data2, line2);
				stringstream textStream2(line2);
				getline(textStream, nazov, ';');
				getline(textStream, pomocna, ';');
				predprod = stoi(pomocna);
				getline(textStream, pomocna, ';');
				produktivny = stoi(pomocna);
				getline(textStream, pomocna, ';');
				poprod = stoi(pomocna);
				getline(textStream, pomocna, ';');
				celkovavymera = stoi(pomocna);
				getline(textStream, pomocna, ';');
				zastavana = stoi(pomocna);

				getline(textStream2, nazovObce, ';');
				getline(textStream2, nazovOkresu, ';');
				getline(textStream2, nazovKraja, ';');

				tester << nazov << ";" << predprod << ";" << produktivny << ";" << poprod << ";" << celkovavymera << ";" << zastavana << ";" << nazovObce << ";" << nazovOkresu << ";" << nazovKraja << endl;
				Obec* o = new Obec(nazov, predprod, produktivny, poprod, celkovavymera, zastavana);
				obceDataTabulka->insert(nazov, o);
				
				UzemnaJednotka* kraj = new UzemnaJednotka(nazovKraja, typUzemnejJednotky::Kraj, nullptr, nullptr, nullptr);


				UzemnaJednotka* okres = new UzemnaJednotka(nazovOkresu, typUzemnejJednotky::Okres, kraj , nullptr, nullptr);


				UzemnaJednotka* obec = new UzemnaJednotka(nazovObce, typUzemnejJednotky::Obec, okres, nullptr, o);
				//
				//if (!slovensko->pridajUJKraj(kraj)) {
				//	delete kraj;
				//}
				//if (!slovensko->pridajUJOkres(okres, kraj->getNazov(), okres->getNazov())) {
				//	delete okres;
				//}

				slovensko->pridajUJKraj(kraj);
				slovensko->pridajUJOkres(okres, kraj->getNazov(), okres->getNazov());
				slovensko->pridajUJObec(obec, okres->getNazov(), kraj->getNazov());
				
				
			}

			tester.close();
			data.close();
			data2.close();
			
		}
	}

	void odstranMemoryLeaky() {
		
		
		int finalne = 0;
		for (structures::TableItem<string, Obec*>* item : *obceDataTabulka)
		{
			finalne = finalne + item->accessData()->celkovy();
		}
		for (structures::TableItem<string, Obec*>* item : *obceDataTabulka)
		{
			delete item->accessData();
		}
		for (structures::TableItem<string, UzemnaJednotka*>* item : *SKTabulka)
		{
			delete item->accessData();
		}

		std::cout << finalne;
		delete obceDataTabulka;
		delete SKTabulka;

	}

};



