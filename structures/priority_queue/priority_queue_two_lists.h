#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include "../heap_monitor.h"

#include <cmath>
namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);

		~PriorityQueueTwoLists();

		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany dvojzoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		void push(const int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		int peekPriority() const override;
	
	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete shortList_;
		shortList_ = nullptr;
		delete longList_;
		longList_ = nullptr;
	}

	template<typename T>
	Structure * PriorityQueueTwoLists<T>::clone() const
	{
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other)
	{

		for (PriorityQueueItem<T>* pomItem: *other.longList_) //longList je LinkedList cize mozem pouzit iteratory
		{
			longList_->add(new PriorityQueueItem<T>(*pomItem));
		}
		*longList_ = *other.longList_;
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const
	{
		return longList_->size() + shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		
		shortList_->clear(); // priority queue list sa o to postara
		for (PriorityQueueItem<T>* item : *longList_)
		{
			delete item;
		}
		longList_->clear();
		
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T & data)
	{
		if (shortList_->minPriority() <= priority && longList_->size() != 0)// ak je priorita noveho prvku vacsia alebo rovna nez min priorita v Arrayi
																		   //A zaroven LinkedList nie je prazdny dam nov prvok do Linked Listu
		{
			longList_->add(new PriorityQueueItem<T>(priority, data));
		}
		else // Ak je min priorita nizsia tak ho dam do Arraya
		{
			PriorityQueueItem<T>* pomItem = shortList_->pushAndRemove(priority, data); // Vloz novyPrvok a vyber ten horsi
			if (pomItem != nullptr)//ak som vybral nullptr array nebol plny
			{
				longList_->add(pomItem); //ak je plny ArrayList zapisem horsi prvok do LinkedListu
			}
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T pom = shortList_->pop(); //PriorityQueueList, da mi pristup k datam, vyberiem prvok z Arraya
		if (longList_->size() > 0 && shortList_->size() == 0) //Ak sa array vyprazdni a v LinkedListe stale nieco je
		{
			//size_t dlzkaArrayu = sqrt(static_cast<int>(longList_->size()));
			//size_t dlzkaArrayu = static_cast<double>(size())/2;
			size_t dlzkaArrayu = static_cast<double>(50000 / 1000);
			if (dlzkaArrayu < 4)
			{
				dlzkaArrayu = 4;
			}
			shortList_->trySetCapacity(dlzkaArrayu); // nastav velkost Arrayu na odmocninu velkosti LinkedListu (efektivita)
			LinkedList<PriorityQueueItem<T>*>* pomZoznam = new LinkedList<PriorityQueueItem<T>*>();
			while (longList_->size() > 0) // Zistujem ci mpzem daj z LinkedListu prvok do ArrayListu
			{
				PriorityQueueItem<T>* delItem = longList_->removeAt(0);// Vyberiem nulty prvok 
				PriorityQueueItem<T>* novyItem = shortList_->pushAndRemove(delItem->getPriority(), delItem->accessData()); 
				//snazim sa vlozit prvok do ArrayListu, pozri pushAndRemove
				// musim to spravit takto inak mi vznika leak
				delete delItem;
				if (novyItem != nullptr) // null pointer vrati vtedy ak ArrayList nie je plny
				{
					pomZoznam->add(novyItem); // Vratib bud delItem alebo prvok s horsou prioritou (vacsou), zapisem do zoznamu
				}
			}
			delete longList_; // pom zoznam mam naplneny, tentoo mozem vycistit a naplnit novymi hodnotami
			longList_ = pomZoznam;
		}
		return pom; // returnujem data s najnizsou prioritou v arrayListe
	}

	template<typename T>
	T & PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek(); // peek() je z PriorityQueueList vyberame vzdy len z arrayListu
	}

	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const
	{
		return shortList_->peek(); // peek() je z PriorityQueueList vyberame vzdy len z arrayListu
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const
	{
		
		return shortList_->peekPriority(); //peekPriority() je z PriorityQueueList 
	}
}