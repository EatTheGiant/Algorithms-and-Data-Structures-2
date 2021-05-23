#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJZastavana : public KriteriumUJ <double, UzemnaJednotka*>
{
public:
	KUJZastavana();

	double ohodnot(UzemnaJednotka* o) override;

	~KUJZastavana();
};

template<typename T, typename O>
inline KUJZastavana<T, O>::KUJZastavana()
{
	this->vysledok = -1;
}

template<typename T, typename O>
inline double KUJZastavana<T, O>::ohodnot(UzemnaJednotka* o)
{
	this->vysledok = o->getZastavanaPlocha();
	return this->vysledok;
}

template<typename T, typename O>
inline KUJZastavana<T, O>::~KUJZastavana()
{
	this->vysledok = nullptr;
}