#pragma once
#include "list.h"
#include "../ds_routines.h"
#include "../heap_monitor.h"
namespace structures {

	template<typename T>
	class ObojZretLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		ObojZretLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		ObojZretLinkedListItem(const ObojZretLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~ObojZretLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		ObojZretLinkedListItem<T>* getNext();

		/// <summary> Getter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Predchadzajuci prvok zretazeneho zoznamu. </returns>
		ObojZretLinkedListItem<T>* getPrevious();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(ObojZretLinkedListItem<T>* next);

		/// <summary> Setter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy predchadzajuci prvok zretazeneho zoznamu. </param>
		void setPrevious(ObojZretLinkedListItem<T>* previous);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		ObojZretLinkedListItem<T>* next_;
		/// <summary> Predchadzajuci prvok zretazeneho zoznamu. </summary>
		ObojZretLinkedListItem<T>* previous_;
	};
	
	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ObojZretLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ObojZretLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		ObojZretLinkedList(const ObojZretLinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~ObojZretLinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		ObojZretLinkedList<T>& operator=(const ObojZretLinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		ObojZretLinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		ObojZretLinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		ObojZretLinkedListItem<T>* getItemAtIndex(int index) const;
	};

	template<typename T>
	inline ObojZretLinkedListItem<T>::ObojZretLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline ObojZretLinkedListItem<T>::ObojZretLinkedListItem(const ObojZretLinkedListItem<T>& other):
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline ObojZretLinkedListItem<T>::~ObojZretLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline ObojZretLinkedListItem<T>* ObojZretLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline ObojZretLinkedListItem<T>* ObojZretLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void ObojZretLinkedListItem<T>::setNext(ObojZretLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline void ObojZretLinkedListItem<T>::setPrevious(ObojZretLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}

	

	template<typename T>
	inline ObojZretLinkedList<T>::ObojZretLinkedList():
		List<T>(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline ObojZretLinkedList<T>::ObojZretLinkedList(const ObojZretLinkedList<T>& other)
	{
		*this = other;
	}


	template<typename T>
	inline ObojZretLinkedList<T>::~ObojZretLinkedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* ObojZretLinkedList<T>::clone() const
	{
		return new ObojZretLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t ObojZretLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& ObojZretLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ObojZretLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ObojZretLinkedList<T>& ObojZretLinkedList<T>::operator=(const ObojZretLinkedList<T>& other)
	{
		if (this != &other)
		{
			clear();
			ObojZretLinkedListItem<T>* pom = other.first_;
			bool hasNext = true;
			while (hasNext)
			{
				add(pom->accessData()); //takymto sposobom si naplnam zoznam
				pom = pom->getNext(); // idem na dalsieho
				if (pom == nullptr) {
					//cout << "Presiel som pri kopirovani dobre " << endl;
					hasNext = false;; // ak uz nema dalsieho tak sa prestane vykonavat
				}
			}
		}
		return *this;
	}

	template<typename T>
	inline T& ObojZretLinkedList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::operator[]: Invalid index.");
		ObojZretLinkedListItem <T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline const T ObojZretLinkedList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::operator[]: Invalid index.");
		ObojZretLinkedListItem <T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline void ObojZretLinkedList<T>::add(const T& data)
	{
		ObojZretLinkedListItem <T>* newItem = new ObojZretLinkedListItem<T>(data);
		if (size_ == 0)
		{
			first_ = newItem;
			last_ = newItem;
		}
		else {
			last_->setNext(newItem);
			newItem->setPrevious(last_);
			last_ = newItem;
		}
		size_++;
	}

	template<typename T>
	inline void ObojZretLinkedList<T>::insert(const T& data, const int index)
	{
		
		if (index == static_cast<int>(size_)) //prazdny zoznam
		{
			this->add(data);
		}
		else
		{
			DSRoutines::rangeCheckExcept(index, size_ + 1, "Invalid index in ObojZretLinkedList!");
			ObojZretLinkedListItem<T>* newItem = new ObojZretLinkedListItem<T>(data);
			if (index == 0) //prvy prvok
			{
				newItem->setNext(first_);
				first_->setPrevious(newItem);
				first_ = newItem;
			}
			else//Tu uz mam vylucene ze je to prvy alebo posledny prvok
				//cachrovanie s prvkami, rozpajanie zoznamu, pridanie prvku a zase spojenie ho do kopy
			{
				ObojZretLinkedListItem<T>* nextItem;
				ObojZretLinkedListItem<T>* previousItem;
				if (index < static_cast<int>(size_) / 2)// prva polka zoznamu
				{
					nextItem = this->getItemAtIndex(index - 1);
					previousItem = nextItem->getNext();
				}
				else// druha polka zoznamu
				{
					previousItem = this->getItemAtIndex(index);
					nextItem = previousItem->getPrevious();
				}
				nextItem->setNext(newItem);
				newItem->setNext(previousItem);
				previousItem->setPrevious(newItem);
				newItem->setPrevious(nextItem);
			}
			size_++;
		}
	}

	template<typename T>
	inline bool ObojZretLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index < 0)
		{
			return false;
		}

		removeAt(index);
		return true;
	}

	template<typename T>
	inline T ObojZretLinkedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in ObojZretLinkedList!");

		ObojZretLinkedListItem<T>* delItem;

		if (size_ == 1) { // || size_ == last_
			delItem = first_;
			first_ = nullptr;
			last_ = nullptr;
		}
		else {
			if (index == 0) { // prvy item
				delItem = first_;
				first_ = first_->getNext();
				first_->setPrevious(nullptr);
			}
			else if (index == size_ - 1)//posledny item
			{
				delItem = last_;
				last_ = last_->getPrevious();
				last_->setNext(nullptr);
			}
			else {  //Tu uz mam vylucene ze je to prvy alebo posledny prvok
				ObojZretLinkedListItem<T>* previousItem;
				ObojZretLinkedListItem<T>* nextItem;
				
				if (index < static_cast<int>(size_) / 2) //prva polka zoznamu
				{
					previousItem = this->getItemAtIndex(index - 1);
					delItem = previousItem->getNext();
					nextItem = delItem->getNext();
				}
				else // druha polka zoznamu
				{
					nextItem = this->getItemAtIndex(index + 1);
					delItem = nextItem->getPrevious();
					previousItem = delItem->getPrevious();
				}
				previousItem->setNext(nextItem);
				nextItem->setPrevious(previousItem);
			}
		}
		T result = delItem->accessData();
		delete delItem;
		size_--; // ten item sa v skutocnosti nedeletne ale uz k nemu nemame pristup, potom ho len prepiseme ked bude treba
		return result;
	}

	template<typename T>
	inline int ObojZretLinkedList<T>::getIndexOf(const T& data)
	{
		ObojZretLinkedListItem<T>* result = first_;
		int index = 0;
		while (result != nullptr) {

			if (result->accessData() == data)// just btw accessData sa nachadza v DataItem, cpp nam umoznuje dedit viacero krat
			{
				return index;
			}
			index++;
			result = result->getNext();

			cout << "Tu sa sekam " << endl;
		}
		return -1;
	}

	template<typename T>
	inline void ObojZretLinkedList<T>::clear()
	{
		if (size_ != 0)
		{
			ObojZretLinkedListItem<T>* delItem = first_;
			while (delItem != nullptr) {
				first_ = delItem->getNext();
				delete delItem;
				delItem = first_;
			}

			size_ = 0;
			first_ = nullptr;
			last_ = nullptr;
		}
	}

	template<typename T>
	inline Iterator<T>* ObojZretLinkedList<T>::getBeginIterator() const 
	{
		throw std::exception("ImplicitStack<T>::operator=: Not implemented yet.");
	}

	template<typename T>
	inline Iterator<T>* ObojZretLinkedList<T>::getEndIterator() const 
	{
		throw std::exception("ImplicitStack<T>::operator=: Not implemented yet.");
	}

	template<typename T>
	inline ObojZretLinkedListItem<T>* ObojZretLinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in ObojZretLinkedList!");



		if (index < static_cast<int>(size_) / 2) // prva polka zoznamu
		{
			ObojZretLinkedListItem<T>* item = first_;
			for (int i = 0; i < index; i++)
			{
				item = item->getNext();
			}
			return item;
		}
		else // druha polka zoznamu
		{
			ObojZretLinkedListItem<T>* item = last_;
			for (size_t i = 0; i < size_ - 1 - index; i++)
			{
				item = item->getPrevious();
			}
			return item;
		}
	}
}