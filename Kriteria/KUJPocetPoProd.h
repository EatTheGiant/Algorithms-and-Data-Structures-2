#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJPocetPoProd : public KriteriumUJ <int, UzemnaJednotka*>
{
public:
	KUJPocetPoProd();

	int ohodnot(UzemnaJednotka* o) override;

	~KUJPocetPoProd();
};

template<typename T, typename O>
inline KUJPocetPoProd<T, O>::KUJPocetPoProd()
{
	this->vysledok = -1;
}

template<typename T, typename O>
inline int KUJPocetPoProd<T, O>::ohodnot(UzemnaJednotka* o)
{
	this->vysledok = o->getPocetPoProd();
	return this->vysledok;
}

template<typename T, typename O>
inline KUJPocetPoProd<T, O>::~KUJPocetPoProd()
{
	this->vysledok = nullptr;
}