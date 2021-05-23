#pragma once
#include "../structures/table/sorted_sequence_table.h"
#include "../Kriterium/Kriterium.h"

template<typename K, typename T, typename V>
class Triedenie
{
public:
	Triedenie(structures::Table<K,T>*, Kriterium<V, T> k, bool vzostupne);
	~Triedenie();

	void quickSort(int min, int max);



private:
	structures::Table<K, T>* table_;
	Kriterium<V, T> k_;
	bool vzostupne_;
};

template<typename K, typename T, typename V>
inline Triedenie<K, T, V>::Triedenie(structures::Table<K, T>* table, Kriterium<V, T> k, bool vzostupne)
{
	table_ = table;
	k_ = k;
	vzostupne_ = vzostupne;
	quickSort(0, table_->size() - 1);
	
}

template<typename K, typename T, typename V>
inline Triedenie<K, T, V>::~Triedenie()
{
}

template<typename K, typename T,typename V>
inline void Triedenie<K, T, V>::quickSort(int min, int max)
{
	K pivot = table_->getItemAtIndex((min + max) / 2).getKey();
	int left = min;
	int right = max;
	do
	{
		while (table_->getItemAtIndex(left).getKey() < pivot)
		{
			left++;
		}
		while (table_->getItemAtIndex(right).getKey() > pivot)
		{
			right--;
		}
		if (left <= right)
		{
			table_->swap(left, right);
			notify();
			left++;
			right--;
		}
	} while (left <= right);
	if (min < right)
	{
		quickSort(min, right);
	}
	if (left < max)
	{
		quickSort(left, max);
	}
}

