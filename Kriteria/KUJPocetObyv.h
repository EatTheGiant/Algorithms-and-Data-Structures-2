#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJPocetObyv : public KriteriumUJ <int, UzemnaJednotka*>
{

public:
	KUJPocetObyv();

	int ohodnot(UzemnaJednotka* o) override;

	~KUJPocetObyv();
};

template<typename T, typename O>
inline KUJPocetObyv<T, O>::KUJPocetObyv()
{
}

template<typename T, typename O>
inline int KUJPocetObyv<T, O>::ohodnot(UzemnaJednotka* o)
{
	
	return o->getPocetObyvatelov();
}

template<typename T, typename O>
inline KUJPocetObyv<T, O>::~KUJPocetObyv()
{
}