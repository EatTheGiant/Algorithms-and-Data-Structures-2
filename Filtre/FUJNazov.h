#pragma once
#include "FPodHodnoty.h"

template<typename K, typename T, typename V>
class FUJNazov : public FPodHodnoty<K, T, V>
{
public:
	~FUJNazov();
	FUJNazov(KriteriumUJ<string, UzemnaJednotka*>* kriterium, string hodnota);
};

template<typename K, typename T, typename V>
inline FUJNazov<K, T, V>::FUJNazov(KriteriumUJ<string, UzemnaJednotka*>* kriterium, string hodnota):
	FPodHodnoty<K, T, V>()
{
	this->kriterium = kriterium;
	this->hodnota = hodnota;
}

template<typename K, typename T, typename V>
inline FUJNazov<K, T, V>::~FUJNazov()
{
}
