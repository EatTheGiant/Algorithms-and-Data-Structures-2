#pragma once
#include "KriteriumUJ.h"

template <typename T, typename O>
class KUJPrislusnost : public KriteriumUJ <bool, UzemnaJednotka*>
{
public:
	KUJPrislusnost();

	bool ohodnot(UzemnaJednotka* o, string nazov);

	~KUJPrislusnost();
};

template<typename T, typename O>
inline KUJPrislusnost<T, O>::KUJPrislusnost()
{
}

template<typename T, typename O>
inline bool KUJPrislusnost<T, O>::ohodnot(UzemnaJednotka* o, string nazov)
{
	return o->getPrislusnost(nazov);
}

template<typename T, typename O>
inline KUJPrislusnost<T, O>::~KUJPrislusnost()
{
}