#pragma once
#include "FPodHodnoty.h"
#include "../typUzemnejJednotky.h"
template<typename K, typename T, typename V>
class FUJTyp : public FPodHodnoty<K, T, V>
{
public:
	~FUJTyp();
	FUJTyp(KriteriumUJ<typUzemnejJednotky, UzemnaJednotka*>* kriterium, typUzemnejJednotky hodnota);
};

template<typename K, typename T, typename V>
inline FUJTyp<K, T, V>::FUJTyp(KriteriumUJ<typUzemnejJednotky, UzemnaJednotka*>* kriterium, typUzemnejJednotky hodnota):
	FPodHodnoty<K, T, V>()
{
	this->kriterium = kriterium;
	this->hodnota = hodnota;
}

template<typename K, typename T, typename V>
inline FUJTyp<K, T, V>::~FUJTyp()
{
}
