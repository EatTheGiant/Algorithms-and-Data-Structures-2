#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJPocetProduktivny : public KriteriumUJ <int, UzemnaJednotka*>
{
public:
	KUJPocetProduktivny();

	int ohodnot(UzemnaJednotka* o) override;

	~KUJPocetProduktivny();
};

template<typename T, typename O>
inline KUJPocetProduktivny<T, O>::KUJPocetProduktivny()
{
	this->vysledok = -1;
}

template<typename T, typename O>
inline int KUJPocetProduktivny<T, O>::ohodnot(UzemnaJednotka* o)
{
	this->vysledok = o->getPocetProduktivny();
	return this->vysledok;
}

template<typename T, typename O>
inline KUJPocetProduktivny<T, O>::~KUJPocetProduktivny()
{
	this->vysledok = nullptr;
}