#pragma once
#include "FPodIntervalu.h"
template<typename K, typename T, typename V>
class FUJPocetObyv : public FPodIntervalu<K, T, V>
{
public:
	~FUJPocetObyv();
	FUJPocetObyv(KriteriumUJ<int, UzemnaJednotka*>* kriterium, int min, int max);
};

template<typename K, typename T, typename V>
inline FUJPocetObyv<K, T, V>::FUJPocetObyv(KriteriumUJ<int, UzemnaJednotka*>* kriterium, int min, int max):
	FPodIntervalu<K, T, V>()
{
	this->kriterium = kriterium;
	this->min = min;
	this->max = max;
}

template<typename K, typename T, typename V>
inline FUJPocetObyv<K, T, V>::~FUJPocetObyv()
{
}
