#pragma once
#include "Kriterium.h"
#include "../UzemnaJednotka.h"

template <typename T, typename O>
class KriteriumUJ : public Kriterium <T, UzemnaJednotka*>
{
public:
	KriteriumUJ();
	~KriteriumUJ();
protected:
	T vysledok;
};

template<typename T, typename O>
inline KriteriumUJ<T, O>::KriteriumUJ()
{
	T vysledok{};
}

template<typename T, typename O>
inline KriteriumUJ<T, O>::~KriteriumUJ()
{
}
