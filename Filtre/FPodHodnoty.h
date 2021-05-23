#pragma once
#include "Filter.h"
template<typename K, typename T, typename V>
class FPodHodnoty : public Filter<K, T, V>
{
public:
	FPodHodnoty();

	bool splnaFilter(T o);

	~FPodHodnoty();
protected:
	V hodnota;
};

template<typename K, typename T, typename V>
inline FPodHodnoty<K, T, V>::FPodHodnoty():
	Filter<K, T, V>()
{
	V hodnota{};
}

template<typename K, typename T, typename V>
inline bool FPodHodnoty<K, T, V>::splnaFilter(T o)
{
	return this->kriterium->ohodnot(o) == this->hodnota;
}

template<typename K, typename T, typename V>
inline FPodHodnoty<K, T, V>::~FPodHodnoty()
{
}