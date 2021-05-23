#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJTyp : public KriteriumUJ <typUzemnejJednotky, UzemnaJednotka*>
{
public:
	KUJTyp();

	typUzemnejJednotky ohodnot(UzemnaJednotka* o) override;

	~KUJTyp();
};

template<typename T, typename O>
inline KUJTyp<T, O>::KUJTyp()
{
}

template<typename T, typename O>
inline typUzemnejJednotky KUJTyp<T, O>::ohodnot(UzemnaJednotka* o)
{
	return o->getTypUJ();
}

template<typename T, typename O>
inline KUJTyp<T, O>::~KUJTyp()
{
}