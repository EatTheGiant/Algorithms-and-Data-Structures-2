#pragma once
#include "FPodHodnoty.h"
template<typename K, typename T, typename V>
class FUJPrislusnost : public FPodHodnoty<K, T, V>
{
public:
	~FUJPrislusnost();

	bool splnaFilter(T o) override;

	bool hahah(SortedSequenceTable<string, T>* t, UnsortedSequenceTable<string, T>* cistaTab);

	FUJPrislusnost(KUJPrislusnost<bool, UzemnaJednotka*>* kriterium, string nazov);
private:
	string nazov;
	KUJPrislusnost<bool, UzemnaJednotka*>* kriterium;
};

template<typename K, typename T, typename V>
inline FUJPrislusnost<K, T, V>::FUJPrislusnost(KUJPrislusnost<bool, UzemnaJednotka*>* kriterium, string nazov):
	FPodHodnoty<K, T, V>()
{
	this->kriterium = kriterium;
	this->hodnota = false;
	this->nazov = nazov;
}

template<typename K, typename T, typename V>
inline FUJPrislusnost<K, T, V>::~FUJPrislusnost()
{
}

template<typename K, typename T, typename V>
inline bool FUJPrislusnost<K, T, V>::splnaFilter(T o)
{
	return this->kriterium->ohodnot(o, nazov);
}

template<typename K, typename T, typename V>
inline bool FUJPrislusnost<K, T, V>::hahah(SortedSequenceTable<string, T>* t, UnsortedSequenceTable<string, T>* cistaTab)
{
	cistaTab->clear();

	for (auto ti : *t)
	{
		if (splnaFilter(ti->accessData()))
		{
			cistaTab->insert(ti->getKey(), ti->accessData());
		}
	}

	if (cistaTab->size() > 0) {
		return true;
	}
	else {
		return false;
	}
}


