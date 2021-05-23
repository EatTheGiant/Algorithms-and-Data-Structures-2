#pragma once
#include "../Filtre/Filter.h"
#include "../Kriteria/Kriterium.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/unsorted_sequence_table.h"

template<typename K, typename T, typename V>
class Triedenie
{
public:
	Triedenie();
	void utried(bool porovnaj);
	void quickSort(int min, int max, bool porovnaj);
	Triedenie(UnsortedSequenceTable<string, UzemnaJednotka*>* pTable, KriteriumUJ<V, T>* pKriterium);
private:
	UnsortedSequenceTable<string, UzemnaJednotka*>* table_;
	Kriterium<V, T>* kriterium_;
};

template<typename K, typename T, typename V>
inline Triedenie<K, T, V>::Triedenie(UnsortedSequenceTable<string, UzemnaJednotka*>* pTable, KriteriumUJ<V, T>* pKriterium)
{
	this->table_ = pTable;
	this->kriterium_ = pKriterium;
}


template<typename K, typename T, typename V>
inline void Triedenie<K, T, V>::utried(bool porovnaj)
{
	quickSort(0, table_->size() - 1, porovnaj);
}



template<typename K, typename T, typename V>
inline void Triedenie<K, T, V>::quickSort(int min, int max, bool porovnaj)
{
	//https://stackoverflow.com/questions/11196571/quick-sort-sorts-descending-not-ascending
	if(porovnaj){
		V pivot = kriterium_->ohodnot(table_->getItemAtIndex((min + max) / 2).accessData());
		int lavy = min;
		int pravy = max;
		do
		{
			while (kriterium_->ohodnot(table_->getItemAtIndex(lavy).accessData()) < pivot)
			{
				lavy++;
			}
			while (kriterium_->ohodnot(table_->getItemAtIndex(pravy).accessData()) > pivot)
			{
				pravy--;
			}
			if (lavy <= pravy)
			{
				table_->swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);
		if (min < pravy)
		{
			quickSort(min, pravy, porovnaj);
		}
		if (lavy < max)
		{
			quickSort(lavy, max, porovnaj);
		}
	}
	else {
		V pivot = kriterium_->ohodnot(table_->getItemAtIndex((min + max) / 2).accessData());
		int lavy = min;
		int pravy = max;
		do
		{
			while (kriterium_->ohodnot(table_->getItemAtIndex(lavy).accessData()) > pivot)
			{
				lavy++;
			}
			while (kriterium_->ohodnot(table_->getItemAtIndex(pravy).accessData()) < pivot)
			{
				pravy--;
			}
			if (lavy <= pravy)
			{
				table_->swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);
		if (min < pravy)
		{
			quickSort(min, pravy, porovnaj);
		}
		if (lavy < max)
		{
			quickSort(lavy, max, porovnaj);

		}
	}
}
