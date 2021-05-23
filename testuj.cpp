#include "testuj.h"

testuj::testuj()
{
	tabulkaVsetko = new SortedSequenceTable<string, UzemnaJednotka*>;
	krajeTabulka = new SortedSequenceTable<string, UzemnaJednotka*>;
	okresyTabulka = new SortedSequenceTable<string, UzemnaJednotka*>;
	obceTabulka = new SortedSequenceTable<string, UzemnaJednotka*>;
	pomTabulka = new SortedSequenceTable<string, UzemnaJednotka*>;
	slovensko = new UzemnaJednotka("Slovensko", typUzemnejJednotky::Stat, nullptr, nullptr, nullptr);
	cistaTabulka = new UnsortedSequenceTable<string, UzemnaJednotka*>;
	tabulkaVsetko->insert("Slovensko", slovensko);
}

void testuj::nacitajObce()
{
	ifstream subor1;
	subor1.open("CSV/Obce_SR.csv");
	ifstream subor2;
	subor2.open("CSV/Uzemne_clenenie.csv");
	int predProd, produktivny, poProd;
	double celkovaVymera, zastavana;
	string line, line2, pomocna, nazov, nazovObce, nazovOkresu, nazovKraja;
	if (subor1.is_open()) {
		while (getline(subor1, line)) {
			stringstream textStream(line);
			getline(subor2, line2);
			stringstream textStream2(line2);
			getline(textStream, nazov, ';');
			getline(textStream, pomocna, ';');
			predProd = stoi(pomocna);
			getline(textStream, pomocna, ';');
			produktivny = stoi(pomocna);
			getline(textStream, pomocna, ';');
			poProd = stoi(pomocna);
			getline(textStream, pomocna, ';');
			celkovaVymera = stoi(pomocna);
			getline(textStream, pomocna, ';');
			zastavana = stoi(pomocna);

			getline(textStream2, nazovObce, ';');
			getline(textStream2, nazovOkresu, ';');
			getline(textStream2, nazovKraja, ';');

			Obec* o = new Obec(predProd, produktivny, poProd, celkovaVymera, zastavana);

			UzemnaJednotka* kraj = new UzemnaJednotka(nazovKraja, typUzemnejJednotky::Kraj, nullptr, nullptr, nullptr);

			if (!slovensko->pridajUJKraj(kraj))
			{
				slovensko->getNizsia()->tryFind(nazovKraja, kraj);
			}
			if (!krajeTabulka->containsKey(nazovKraja))
			{
				krajeTabulka->insert(nazovKraja, kraj);
			}

			UzemnaJednotka* okres = new UzemnaJednotka(nazovOkresu, typUzemnejJednotky::Okres, kraj, nullptr, nullptr);

			if (!slovensko->pridajUJOkres(okres, kraj->getNazov(), okres->getNazov()))
			{
				kraj->getNizsia()->tryFind(nazovOkresu, okres);
			}
			if (!okresyTabulka->containsKey(nazovOkresu))
			{
				okresyTabulka->insert(nazovOkresu, okres);
			}

			UzemnaJednotka* obec = new UzemnaJednotka(nazovObce, typUzemnejJednotky::Obec, okres, nullptr, o);
			
			slovensko->pridajUJObec(obec, okres->getNazov(), kraj->getNazov());
			if (!obceTabulka->containsKey(nazovObce))
			{
				obceTabulka->insert(nazovObce, obec);
			}
		}
		subor1.close();
		subor2.close();
	}
}

void testuj::vypisFilter(UnsortedSequenceTable<string, UzemnaJednotka*>* tabulka)
{
	KriteriumUJ<int, UzemnaJednotka*>* kUJPocetObyv =
		new KUJPocetObyv<int, UzemnaJednotka*>;
	KriteriumUJ<int, UzemnaJednotka*>* kUJPredProd =
		new KUJPocetPreProd<int, UzemnaJednotka*>;
	KriteriumUJ<int, UzemnaJednotka*>* kUJProd =
		new KUJPocetProduktivny<int, UzemnaJednotka*>;
	KriteriumUJ<int, UzemnaJednotka*>* kUJPoProd =
		new KUJPocetPoProd<int, UzemnaJednotka*>;
	KriteriumUJ<double, UzemnaJednotka*>* kUJZastavanost =
		new KUJZastavanost<double, UzemnaJednotka*>;
	KriteriumUJ<double, UzemnaJednotka*>* kUJCelkovaVymera =
		new KUJCelkVym<double, UzemnaJednotka*>;
	KriteriumUJ<double, UzemnaJednotka*>* kUJZastavanaPlocha =
		new KUJZastavana<double, UzemnaJednotka*>;
	KriteriumUJ<string, UzemnaJednotka*>* kUJNazov =
		new KUJNazov<string, UzemnaJednotka*>;

	for (auto t : *tabulka) {
		ziskajVyssiuUJ(t->accessData());
		cout << kUJNazov->ohodnot(t->accessData()) << " ";
		cout << kUJPocetObyv->ohodnot(t->accessData()) << " ";
		cout << kUJPredProd->ohodnot(t->accessData()) << " ";
		cout << kUJProd->ohodnot(t->accessData()) << " ";
		cout << kUJPoProd->ohodnot(t->accessData()) << " ";
		cout << kUJZastavanost->ohodnot(t->accessData()) << " ";
		cout << kUJCelkovaVymera->ohodnot(t->accessData()) << " ";
		cout << kUJZastavanaPlocha->ohodnot(t->accessData()) << " " << endl;
	}

	delete kUJCelkovaVymera;
	delete kUJNazov;
	delete kUJPocetObyv;
	delete kUJPoProd;
	delete kUJProd;
	delete kUJPredProd;
	delete kUJZastavanaPlocha;
	delete kUJZastavanost;
}

void testuj::ziskajVyssiuUJ(UzemnaJednotka* UJ) { //Na vypisovanie nazvov UJ
	KriteriumUJ<string, UzemnaJednotka*>* kUJNazov =
		new KUJNazov<string, UzemnaJednotka*>;
	if (UJ->getVyssiaUJ() != nullptr) {
		cout << kUJNazov->ohodnot(UJ->getVyssiaUJ()) << " ";
		if (UJ->getVyssiaUJ()->getVyssiaUJ() != nullptr) {
			cout << kUJNazov->ohodnot(UJ->getVyssiaUJ()->getVyssiaUJ()) << " ";
			if (UJ->getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ() != nullptr) {
				cout << kUJNazov->ohodnot(UJ->getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ()) << " ";
				if (UJ->getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ() != nullptr) {
					cout << kUJNazov->ohodnot(UJ->getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ()) << " ";
				}
			}
		}
	}
	delete kUJNazov;
}

void testuj::filtrujPocetObyvUJ(SortedSequenceTable<string, UzemnaJednotka*>* tabulka)
{
	KriteriumUJ<int, UzemnaJednotka*>* kUJPocetObyv =
		new KUJPocetObyv<int, UzemnaJednotka*>;

	int min, max;
	cout << "vyberte si interval" << endl;
	cin >> min;
	cin >> max;

	FPodIntervalu<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* fUJPocetObyv =
		new FUJPocetObyv<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(kUJPocetObyv, min, max);

	if(fUJPocetObyv->vyfiltrujTabulku(tabulka, cistaTabulka)){

		Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
			new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);
		cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
		int pom4;
		cin >> pom4;
		if (pom4 == 1)
		{
			triedenie->utried(true);
			this->vypisFilter(cistaTabulka);
		}
		else if (pom4 == 0) {
			triedenie->utried(false);
			this->vypisFilter(cistaTabulka);
		}
		
		delete triedenie;
	}
	else
	{
		cout << "taka UJ neexistuje" << endl;
	}
	delete kUJPocetObyv;
	delete fUJPocetObyv;
}

void testuj::filtrujNazovUJ(SortedSequenceTable<string, UzemnaJednotka*>* tabulka)
{
	KriteriumUJ<string, UzemnaJednotka*>* kUJNazov =
		new KUJNazov<string, UzemnaJednotka*>;

	string nazovUJ;
	cout << "zadajte nazov UJ" << endl;
	cin.ignore();
	getline(cin, nazovUJ);

	FPodHodnoty<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* fUJNazov =
		new FUJNazov<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(kUJNazov, nazovUJ);

	if (fUJNazov->vyfiltrujTabulku(tabulka, cistaTabulka)) {

		Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
			new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

		cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
		int pom4;
		cin >> pom4;
		if (pom4 == 1)
		{
			triedenie->utried(true);
			this->vypisFilter(cistaTabulka);
		}
		else if (pom4 == 0) {
			triedenie->utried(false);
			this->vypisFilter(cistaTabulka);
		}
		delete triedenie;
	}
	delete kUJNazov;
	delete fUJNazov;
}

void testuj::filtrujZastavanost(SortedSequenceTable<string, UzemnaJednotka*>* tabulka)
{
	KriteriumUJ<double, UzemnaJednotka*>* kUJZastavanost =
		new KUJZastavanost<double, UzemnaJednotka*>;

	double min, max;
	cout << "vyberte si interval" << endl;
	cin >> min;
	cin >> max;

	FPodIntervalu<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* fUJZastavanost =
		new FUJZastavanost<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(kUJZastavanost, min, max);

	if (fUJZastavanost->vyfiltrujTabulku(tabulka, cistaTabulka)) {

		Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
			new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

		cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
		int pom4;
		cin >> pom4;
		if (pom4 == 1)
		{
			triedenie->utried(true);
			this->vypisFilter(cistaTabulka);
		}
		else if (pom4 == 0) {
			triedenie->utried(false);
			this->vypisFilter(cistaTabulka);
		}

		delete triedenie;
	}
	delete kUJZastavanost;
	delete fUJZastavanost;
}

void testuj::dajPrislusnost(string nazov, SortedSequenceTable<string, UzemnaJednotka*>* tabulkaPrisl) {
	KUJPrislusnost<bool, UzemnaJednotka*>* kUJPrislusnost =
		new KUJPrislusnost<bool, UzemnaJednotka*>;

	FUJPrislusnost<KUJPrislusnost<bool, UzemnaJednotka*>, UzemnaJednotka*, bool>* fUJPrislusnost =
		new FUJPrislusnost<KUJPrislusnost<bool, UzemnaJednotka*>, UzemnaJednotka*, bool>(kUJPrislusnost, nazov);

	if (fUJPrislusnost->hahah(tabulkaPrisl, cistaTabulka)) {

		Triedenie<KUJPrislusnost<bool, UzemnaJednotka*>, UzemnaJednotka*, bool>* triedenie =
			new Triedenie<KUJPrislusnost<bool, UzemnaJednotka*>, UzemnaJednotka*, bool>(cistaTabulka, kUJPrislusnost);

		triedenie->utried(false);
	}
	delete kUJPrislusnost;
	delete fUJPrislusnost;
}

void testuj::spusti()
{
	int uloha = 0;
	cout << "Pre ulohu 3 stlacte 3, pre 4 stlacte 4" << endl;
	cin >> uloha;

	string prislusnost;
	cout << "vyberte si prislusnost" << endl;
	cin.ignore();
	getline(cin, prislusnost);

	int typUzemJed = 0;
	cout << "vyberte si typ 1 2 3 4 5(1 Stat, ... 5 nedefinovany)" << endl;
	cin >> typUzemJed;
	
	if (uloha == 3)
	{
			int filter = 0;
			cout << "vyberte si filter 1 2 3 (1 FUJNazov, 2 FUJPocetObyv, 3 FUJZastavanost)" << endl;
			cin >> filter; 

			if (typUzemJed == 1)
			{
				if (filter == 1)
				{
					if (prislusnost !="nedefinovany") {
						dajPrislusnost(prislusnost, tabulkaVsetko);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujNazovUJ(pomTabulka);
					}
					else {
						filtrujNazovUJ(tabulkaVsetko);
					}

					
				}
				else if (filter == 2) {
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, tabulkaVsetko);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujPocetObyvUJ(pomTabulka);
					}
					else {
						filtrujPocetObyvUJ(tabulkaVsetko);
					}
					
				}
				else if (filter == 3) {
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, tabulkaVsetko);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujZastavanost(pomTabulka);
					}
					else
					{
						filtrujZastavanost(tabulkaVsetko);
					}
				}
			}
			else if (typUzemJed == 2) {

				if (filter == 1)
				{
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, krajeTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujNazovUJ(pomTabulka);
					}
					else
					{
						filtrujNazovUJ(krajeTabulka);
					}
				}
				else if (filter == 2){
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, krajeTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujPocetObyvUJ(pomTabulka);
					}
					else
					{
						filtrujPocetObyvUJ(krajeTabulka);
					}
				}
				else if(filter == 3){
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, krajeTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujZastavanost(pomTabulka);
					}
					else
					{
						filtrujZastavanost(krajeTabulka);
					}
				}
			}
			else if (typUzemJed == 3) {
				if (filter == 1)
				{
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, okresyTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujNazovUJ(pomTabulka);
					}
					else
					{
						filtrujNazovUJ(okresyTabulka);
					}
				}
				else if (filter == 2) {
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, okresyTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujPocetObyvUJ(pomTabulka);
					}
					else
					{
						filtrujPocetObyvUJ(okresyTabulka);
					}
				}
				else if (filter == 3) {
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, okresyTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujZastavanost(pomTabulka);
					}
					else {
						filtrujZastavanost(okresyTabulka);
					}
				}
			}
			else if (typUzemJed == 4 || typUzemJed == 5) {
				if (filter == 1)
				{
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, obceTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujNazovUJ(pomTabulka);
					}
					else {
						filtrujNazovUJ(obceTabulka);
					}
				}
				else if (filter == 2) {
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, obceTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujPocetObyvUJ(pomTabulka);
					}
					else {
						filtrujPocetObyvUJ(obceTabulka);
					}
				}
				else if (filter == 3) {
					if (prislusnost != "nedefinovany") {
						dajPrislusnost(prislusnost, obceTabulka);

						for (auto ti : *cistaTabulka)
						{
							pomTabulka->insert(ti->getKey(), ti->accessData());
						}

						filtrujZastavanost(pomTabulka);
					}
					else {
						filtrujZastavanost(obceTabulka);
					}
				}
			}
	}
	else if (uloha == 4) {

		int kriterium = 0;
		cout << "vyberte si kriterium 1 2 3 (1 KUJNazov, 2 KUJPocetObyv, 3 KUJZastavanost)" << endl;
		cin >> kriterium;

		if (typUzemJed == 1)
		{
			if (kriterium == 1)
			{
				KUJNazov<string, UzemnaJednotka*>* kUJNazov =
					new KUJNazov<string, UzemnaJednotka*>;

				UzemnaJednotka* item;
				bool rozh = tabulkaVsetko->tryFind("Slovensko", item);
				if (rozh) {
					cout << kUJNazov->ohodnot(item) << endl;
				}
				else
				{
					cout << "Takhle to nepujde." << endl;
				}
				delete kUJNazov;
			}
			else if (kriterium == 2) { // stat pocet obyv
				KriteriumUJ<int, UzemnaJednotka*>* kUJPocet =
					new KUJPocetObyv<int, UzemnaJednotka*>;
				UzemnaJednotka* item;
				bool rozh = tabulkaVsetko->tryFind("Slovensko", item);
				if (rozh) {
					cout << item->getNazov() << " ";
					cout << kUJPocet->ohodnot(item) << endl;
				}
				else
				{
					cout << item->getNazov() << " ";
					cout << "Takhle to nepujde." << endl;
				}
				delete kUJPocet;
			}
			else if (kriterium == 3) {
				KriteriumUJ<double, UzemnaJednotka*>* kUJZastavanost =
					new KUJZastavanost<double, UzemnaJednotka*>;
				UzemnaJednotka* item;
				bool rozh = tabulkaVsetko->tryFind("Slovensko", item);
				if (rozh) {
					cout << item->getNazov() << " ";
					cout << kUJZastavanost->ohodnot(item) << endl;
				}
				else
				{
					cout << item->getNazov() << " ";
					cout << "Takhle to nepujde." << endl;
				}
				delete kUJZastavanost;
			}
		}
		else if (typUzemJed == 2) {
			if (kriterium == 1)
			{
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, krajeTabulka);

					KUJNazov<string, UzemnaJednotka*>* kUJNazov =
						new KUJNazov<string, UzemnaJednotka*>;

					Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
						new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJNazov;
					delete triedenie;
				}
				else {
					KUJNazov<string, UzemnaJednotka*>* kUJNazov =
						new KUJNazov<string, UzemnaJednotka*>;

					for (auto t : *krajeTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
						new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJNazov;
					delete triedenie;
				}
			}
			else if (kriterium == 2) {
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, krajeTabulka);

					KUJPocetObyv<int, UzemnaJednotka*>* kUJPocetObyv =
						new KUJPocetObyv<int, UzemnaJednotka*>;

					Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
						new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJPocetObyv;
					delete triedenie;
				}
				else {
					KUJPocetObyv<int, UzemnaJednotka*>* kUJPocetObyv =
						new KUJPocetObyv<int, UzemnaJednotka*>;

					for (auto t : *krajeTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
						new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJPocetObyv;
					delete triedenie;
				}
			}
			else if (kriterium == 3) {
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, krajeTabulka);


					KUJZastavanost<double, UzemnaJednotka*>* kUJZastavanost =
						new KUJZastavanost<double, UzemnaJednotka*>;

					Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
						new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJZastavanost;
					delete triedenie;
				}
				else {
					KUJZastavanost<double, UzemnaJednotka*>* kUJZastavanost =
						new KUJZastavanost<double, UzemnaJednotka*>;

					for (auto t : *krajeTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
						new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJZastavanost;
					delete triedenie;
				}
			}
		}
		else if (typUzemJed == 3) {
			if (kriterium == 1)
			{
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, okresyTabulka);

					KUJNazov<string, UzemnaJednotka*>* kUJNazov =
						new KUJNazov<string, UzemnaJednotka*>;

					Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
						new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJNazov;
					delete triedenie;
				}
				else {
					KUJNazov<string, UzemnaJednotka*>* kUJNazov =
						new KUJNazov<string, UzemnaJednotka*>;

					for (auto t : *okresyTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
						new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJNazov;
					delete triedenie;
				}
			}
			else if (kriterium == 2) {
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, okresyTabulka);

					KUJPocetObyv<int, UzemnaJednotka*>* kUJPocetObyv =
						new KUJPocetObyv<int, UzemnaJednotka*>;

					Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
						new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJPocetObyv;
					delete triedenie;
				}
				else {
					KUJPocetObyv<int, UzemnaJednotka*>* kUJPocetObyv =
						new KUJPocetObyv<int, UzemnaJednotka*>;

					for (auto t : *okresyTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
						new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJPocetObyv;
					delete triedenie;
				}
			}
			else if (kriterium == 3) {
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, okresyTabulka);

					KUJZastavanost<double, UzemnaJednotka*>* kUJZastavanost =
						new KUJZastavanost<double, UzemnaJednotka*>;

					Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
						new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJZastavanost;
					delete triedenie;
				}
				else {
					KUJZastavanost<double, UzemnaJednotka*>* kUJZastavanost =
						new KUJZastavanost<double, UzemnaJednotka*>;

					for (auto t : *okresyTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
						new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJZastavanost;
					delete triedenie;
				}
			}
		}
		else if (typUzemJed == 4)
		{
			if (kriterium == 1)
			{
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, obceTabulka);

					KUJNazov<string, UzemnaJednotka*>* kUJNazov =
						new KUJNazov<string, UzemnaJednotka*>;

					Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
						new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJNazov;
					delete triedenie;
				}
				else
				{
					KUJNazov<string, UzemnaJednotka*>* kUJNazov =
						new KUJNazov<string, UzemnaJednotka*>;

					for (auto t : *obceTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>* triedenie =
						new Triedenie<KUJNazov<string, UzemnaJednotka*>, UzemnaJednotka*, string>(cistaTabulka, kUJNazov);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << kUJNazov->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJNazov;
					delete triedenie;
				}
			}
			else if (kriterium == 2) {
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, obceTabulka);

					KUJPocetObyv<int, UzemnaJednotka*>* kUJPocetObyv =
						new KUJPocetObyv<int, UzemnaJednotka*>;

					Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
						new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJPocetObyv;
					delete triedenie;
				}
				else {
					KUJPocetObyv<int, UzemnaJednotka*>* kUJPocetObyv =
						new KUJPocetObyv<int, UzemnaJednotka*>;

					for (auto t : *obceTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>* triedenie =
						new Triedenie<KUJPocetObyv<int, UzemnaJednotka*>, UzemnaJednotka*, int>(cistaTabulka, kUJPocetObyv);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJPocetObyv->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJPocetObyv;
					delete triedenie;
				}
			}
			else if (kriterium == 3) {
				if (prislusnost != "nedefinovany") {
					dajPrislusnost(prislusnost, obceTabulka);

					KUJZastavanost<double, UzemnaJednotka*>* kUJZastavanost =
						new KUJZastavanost<double, UzemnaJednotka*>;

					Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
						new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJZastavanost;
					delete triedenie;
				}
				else {
					KUJZastavanost<double, UzemnaJednotka*>* kUJZastavanost =
						new KUJZastavanost<double, UzemnaJednotka*>;

					for (auto t : *obceTabulka) {
						cistaTabulka->insert(t->getKey(), t->accessData());
					}

					Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>* triedenie =
						new Triedenie<KUJZastavanost<double, UzemnaJednotka*>, UzemnaJednotka*, double>(cistaTabulka, kUJZastavanost);

					cout << "Pre utriedenie vzostupne stlacte 1 pre zostupne 0" << endl;
					int pom4;
					cin >> pom4;
					if (pom4 == 1)
					{
						triedenie->utried(true);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else if (pom4 == 0) {
						triedenie->utried(false);
						for (auto t : *cistaTabulka) {
							cout << t->accessData()->getNazov() << " ";
							cout << kUJZastavanost->ohodnot(t->accessData()) << endl;
						}
					}
					else {
						cout << "neplatnaVolba" << endl;
					}

					delete kUJZastavanost;
					delete triedenie;
				}
			}
		}
	}
}

testuj::~testuj() 
{
	for (structures::TableItem<string, UzemnaJednotka*>* item : *tabulkaVsetko)
	{
		delete item->accessData();
	}

	delete tabulkaVsetko;
	//Su prazdne ale aj tak ich treba vymazat
	delete cistaTabulka;
	delete krajeTabulka;
	delete okresyTabulka;
	delete obceTabulka;
}
