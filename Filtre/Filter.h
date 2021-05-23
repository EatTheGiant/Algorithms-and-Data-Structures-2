#pragma once
#include "../Kriteria/Kriterium.h"
#include "../Kriteria/KriteriumUJ.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../UzemnaJednotka.h"
template <typename K, typename T, typename V>
class Filter
{
public:
	Filter();
	
	virtual bool splnaFilter(T o) = 0;

	bool vyfiltrujTabulku(SortedSequenceTable<string, T>* t, UnsortedSequenceTable<string, T>* cistaTab);

	~Filter();

protected:
	Kriterium<V, T>* kriterium;
};

template<typename K, typename T, typename V>
inline Filter<K, T, V>::Filter()
{
	Kriterium<V, T>* kriterium{};
}

template<typename K, typename T, typename V>
inline bool Filter<K, T, V>::vyfiltrujTabulku(SortedSequenceTable<string, T>* t, UnsortedSequenceTable<string, T>* cistaTab)
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

template<typename K, typename T, typename V>
inline Filter<K, T, V>::~Filter()
{
}