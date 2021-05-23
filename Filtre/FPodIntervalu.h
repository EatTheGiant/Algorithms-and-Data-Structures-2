#pragma once
#include "Filter.h"

template<typename K, typename T, typename V>
class FPodIntervalu : public Filter<K, T, V>
{
public:
	FPodIntervalu();
	~FPodIntervalu();
	bool splnaFilter(T o);

protected:
	V min;
	V max;
};

template<typename K, typename T, typename V>
inline FPodIntervalu<K, T, V>::FPodIntervalu():
	Filter<K, T, V>()
{
	V min{};
	V max{};
}

template<typename K, typename T, typename V>
inline FPodIntervalu<K, T, V>::~FPodIntervalu()
{
}

template<typename K, typename T, typename V>
inline bool FPodIntervalu<K, T, V>::splnaFilter(T o)
{
	V vysledok = this->kriterium->ohodnot(o);
	return vysledok >= min && vysledok <= max;
}
