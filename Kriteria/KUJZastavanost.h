#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJZastavanost : public KriteriumUJ <double, UzemnaJednotka*>
{
public:
	KUJZastavanost();

	double ohodnot(UzemnaJednotka* o) override;

	~KUJZastavanost();
};

template<typename T, typename O>
inline KUJZastavanost<T, O>::KUJZastavanost()
{
}

template<typename T, typename O>
inline double KUJZastavanost<T, O>::ohodnot(UzemnaJednotka* o)
{
	return o->getZastavanost();
}

template<typename T, typename O>
inline KUJZastavanost<T, O>::~KUJZastavanost()
{
}