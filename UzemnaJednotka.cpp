#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(string nazov, typUzemnejJednotky typUJ, UzemnaJednotka* vyssiaUJ, SortedSequenceTable<string, UzemnaJednotka*>* nizsiaUJ, Obec* obec) :
	nazov(nazov),
	typUJ(typUJ),
	vyssiaUJ(vyssiaUJ),
	nizsiaUJ(nizsiaUJ),
	obec(obec)
{
	if (!nizsiaUJ) {
		this->nizsiaUJ = new SortedSequenceTable<string, UzemnaJednotka*>;
	}
}

bool UzemnaJednotka::getPrislusnost(string nazov)
{
	bool pom = false;
	if (nazov == this->getNazov())
	{
		return true;
	}

	if (nazov == "Slovensko") {
		return true;
	}

	if (getVyssiaUJ() != nullptr) {
		pom = getVyssiaUJ()->getPrislusnost(nazov);
	}
	
	return pom;


	/*if (getVyssiaUJ() != nullptr && nazov == getVyssiaUJ()->getNazov())
	{
		return true;
	}
	else if (getVyssiaUJ()->getVyssiaUJ() != nullptr && nazov == getVyssiaUJ()->getVyssiaUJ()->getNazov()) {
		return true;
	}
	else if (nazov == getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ()->getNazov() && getVyssiaUJ())
	{
		return true;
	}
	else if (nazov == getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ()->getVyssiaUJ()->getNazov() && getVyssiaUJ()) {
		return true;
	}

	if (typUzemnejJednotky::Kraj == getTypUJ())
	{
		return true;
	}
	return false;
	*/
}

UzemnaJednotka* UzemnaJednotka::getVyssiaUJ()
{
	if (typUzemnejJednotky::Stat == typUJ)
	{
		return nullptr;
	}
	return vyssiaUJ;
}

void UzemnaJednotka::vytvorTabulku()
{
	if (nizsiaUJ == nullptr){
		nizsiaUJ = new SortedSequenceTable<string, UzemnaJednotka*>;
	}
}

bool UzemnaJednotka::pridajUJKraj(UzemnaJednotka* uj)
{
	UzemnaJednotka* t;
	if (nizsiaUJ == nullptr) {
		nizsiaUJ = new SortedSequenceTable<string, UzemnaJednotka*>;
	}

	if (uj->getTypUJ() == typUzemnejJednotky::Kraj) {
		if (!nizsiaUJ->tryFind(uj->getNazov(), t)) {
			nizsiaUJ->insert(uj->getNazov(), uj);
			return true;
		}
		else {
			delete uj;
			return false;
		}
	}
}

void UzemnaJednotka::pridajUJObec(UzemnaJednotka* uj, string nazovOkresu, string nazovKraja)
{
	UzemnaJednotka* ujKraj;
	UzemnaJednotka* ujOkres;
	if (nizsiaUJ == nullptr) {
		nizsiaUJ = new SortedSequenceTable<string, UzemnaJednotka*>;
	}
	if (uj->getTypUJ() == typUzemnejJednotky::Obec) {
		if (nizsiaUJ->tryFind(nazovKraja, ujKraj)) {
			if (ujKraj->nizsiaUJ->tryFind(nazovOkresu, ujOkres))
			{
				ujOkres->vytvorTabulku();
				ujOkres->nizsiaUJ->insert(uj->getNazov(), uj);

			}
		}
	}
}

bool UzemnaJednotka::pridajUJOkres(UzemnaJednotka* uj, string nazovKraja, string nazovOkresu)
{
	UzemnaJednotka* t;
	UzemnaJednotka* ujKraj;
	if (nizsiaUJ == nullptr) {
		nizsiaUJ = new SortedSequenceTable<string, UzemnaJednotka*>;
	}

	if (uj->getTypUJ() == typUzemnejJednotky::Okres) {
		if (nizsiaUJ->tryFind(nazovKraja, ujKraj)) {
			ujKraj->vytvorTabulku();

			if (!ujKraj->nizsiaUJ->tryFind(nazovOkresu, t)) {
				ujKraj->nizsiaUJ->insert(nazovOkresu, uj);
				return true;
			}
			else {
				delete uj;
				return false;
			}
		}
	}
}

void UzemnaJednotka::vymazLeaky()
{
	for (TableItem<string, UzemnaJednotka*>* item : *nizsiaUJ)
	{
		delete item->accessData();
	}
}

int UzemnaJednotka::getPocetObyvatelov()
{
	this->celkovyPocet = 0;
	if (this->getTypUJ() == typUzemnejJednotky::Obec)
	{
		return (this->getObec()->getPoProd() + this->getObec()->getPredProd() + this->getObec()->getProduktivny());
	}
	else {
		for (TableItem<string, UzemnaJednotka*>* item : *this->getNizsia()) {
			celkovyPocet = celkovyPocet + item->accessData()->getPocetObyvatelov();
		}
	}

	return this->celkovyPocet;
}
int UzemnaJednotka::getPocetPreProd()
{
	this->celkovyPocet = 0;
	if (this->getTypUJ() == typUzemnejJednotky::Obec)
	{
		return this->getObec()->getPredProd();
	}
	else {
		for (TableItem<string, UzemnaJednotka*>* item : *this->getNizsia()) {
			celkovyPocet = celkovyPocet + item->accessData()->getPocetPreProd();
		}
	}

	return this->celkovyPocet;
}
int UzemnaJednotka::getPocetPoProd()
{
	celkovyPocet = 0;
	if (this->getTypUJ() == typUzemnejJednotky::Obec)
	{
		return this->getObec()->getPoProd();
	}
	else {
		for (TableItem<string, UzemnaJednotka*>* item : *this->getNizsia()) {
			celkovyPocet = celkovyPocet + item->accessData()->getPocetPoProd();
		}
	}

	return this->celkovyPocet;
}
int UzemnaJednotka::getPocetProduktivny()
{
	this->celkovyPocet = 0;
	if (this->getTypUJ() == typUzemnejJednotky::Obec)
	{
		return this->getObec()->getProduktivny();
	}
	else {
		for (TableItem<string, UzemnaJednotka*>* item : *this->getNizsia()) {
			celkovyPocet = celkovyPocet + item->accessData()->getPocetProduktivny();
		}
	}

	return this->celkovyPocet;
}
double UzemnaJednotka::getCelkovaVymera()
{
	celkovaVymera = 0;
	if (this->getTypUJ() == typUzemnejJednotky::Obec)
	{
		return this->getObec()->getCelkovaVymera();
	}
	else {
		for (TableItem<string, UzemnaJednotka*>* item : *this->getNizsia()) {
			celkovaVymera = celkovaVymera + item->accessData()->getCelkovaVymera();
		}
	}

	return celkovaVymera;
}
double UzemnaJednotka::getZastavanaPlocha()
{
	zastavanaPlocha = 0;
	if (this->getTypUJ() == typUzemnejJednotky::Obec)
	{
		return this->getObec()->getZastavanaPlocha();
	}
	else {
		for (TableItem<string, UzemnaJednotka*>* item : *this->getNizsia()) {
			zastavanaPlocha = zastavanaPlocha + item->accessData()->getZastavanaPlocha();
		}
	}

	return zastavanaPlocha;
}
double UzemnaJednotka::getZastavanost()
{
	return 100 * (getZastavanaPlocha() / getCelkovaVymera());
}

UzemnaJednotka::~UzemnaJednotka()
{
	for (TableItem<string, UzemnaJednotka*>* item : *nizsiaUJ)
	{
		delete item->accessData();
	}
	delete nizsiaUJ;
}