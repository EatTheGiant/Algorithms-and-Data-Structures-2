#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJCelkVym : public KriteriumUJ <double, UzemnaJednotka*>
{
public:
	KUJCelkVym();

	double ohodnot(UzemnaJednotka* o) override;

	~KUJCelkVym();
};

template<typename T, typename O>
inline KUJCelkVym<T, O>::KUJCelkVym()
{
	this->vysledok = -1;
}

template<typename T, typename O>
inline double KUJCelkVym<T, O>::ohodnot(UzemnaJednotka* o)
{
	vysledok = o->getCelkovaVymera();
	return vysledok;
}

template<typename T, typename O>
inline KUJCelkVym<T, O>::~KUJCelkVym()
{
	this->vysledok = nullptr;
}