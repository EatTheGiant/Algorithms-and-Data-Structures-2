#pragma once
#include "FPodIntervalu.h"

template<typename K, typename T, typename V>
class FUJZastavanost : public FPodIntervalu<K, T, V>
{
public:
	~FUJZastavanost();
	FUJZastavanost(KriteriumUJ<double, UzemnaJednotka*>* kriterium, double min, double max);
};

template<typename K, typename T, typename V>
inline FUJZastavanost<K, T, V>::FUJZastavanost(KriteriumUJ<double, UzemnaJednotka*>* kriterium, double min, double max):
	FPodIntervalu<K, T, V>()
{
	this->kriterium = kriterium;
	this->min = min;
	this->max = max;
}

template<typename K, typename T, typename V>
inline FUJZastavanost<K, T, V>::~FUJZastavanost()
{
}
