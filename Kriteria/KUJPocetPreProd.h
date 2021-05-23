#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJPocetPreProd : public KriteriumUJ <int, UzemnaJednotka*>
{
public:
	KUJPocetPreProd();

	int ohodnot(UzemnaJednotka* o) override;

	~KUJPocetPreProd();
};

template<typename T, typename O>
inline KUJPocetPreProd<T, O>::KUJPocetPreProd()
{
	this->vysledok = -1;
}

template<typename T, typename O>
inline int KUJPocetPreProd<T, O>::ohodnot(UzemnaJednotka* o)
{
	this->vysledok = o->getPocetPreProd();
	return this->vysledok;
}

template<typename T, typename O>
inline KUJPocetPreProd<T, O>::~KUJPocetPreProd()
{
	this->vysledok = nullptr;
}