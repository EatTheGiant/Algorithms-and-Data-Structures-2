#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJNazov : public KriteriumUJ <string, UzemnaJednotka*>
{
public:
	KUJNazov();

	string ohodnot(UzemnaJednotka* o) override;

	~KUJNazov();
};

template<typename T, typename O>
inline KUJNazov<T, O>::KUJNazov()
{
}

template<typename T, typename O>
inline string KUJNazov<T, O>::ohodnot(UzemnaJednotka* o)
{

	return o->getNazov();
}

template<typename T, typename O>
inline KUJNazov<T, O>::~KUJNazov()
{
}