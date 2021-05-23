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
		ObojZretLinkedListItem<T>* pom = other.first_;
		if (this != &other || pom != nullptr)
		{
			clear();
			do
			{
				add(pom->accessData()); //takymto sposobom si naplnam zoznam
				pom = pom->getNext(); // idem na dalsieho
			}while (pom != other.first_);
		}
		return *this;
	}

	template<typename T>
	inline T& ObojZretLinkedList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::operator[]: Invalid index. OPERATOR []");
		ObojZretLinkedListItem <T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline const T ObojZretLinkedList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "DoubleLinkedList<T>::operator[]: Invalid index. OPERATOR []");
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
			newItem->setPrevious(last_);
			newItem->setNext(first_);
		}
		else {
			last_->setNext(newItem);
			newItem->setPrevious(last_);
			newItem->setNext(first_);
			last_ = newItem;
		}
		size_++;
	}

	template<typename T>
	inline void ObojZretLinkedList<T>::insert(const T& data, const int index)
	{

		if (index == static_cast<int>(size_)) {
			add(data);
		}
		else {
			DSRoutines::rangeCheckExcept(index, size_, "invalid index in linkedlist");
			ObojZretLinkedListItem<T>* item = new ObojZretLinkedListItem<T>(data);

			size_++;

			if (index == 0) {
				item->setNext(first_);
				first_->setPrevious(item);
				first_ = item;
			}
			else {
				ObojZretLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
				ObojZretLinkedListItem<T>* nextItem = prevItem->getNext();
				prevItem->setNext(item);
				item->setNext(nextItem);
				nextItem->setPrevious(item);
				item->setPrevious(prevItem);
			}

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
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in ObojZretLinkedList! INSERT");

		ObojZretLinkedListItem<T>* item;
		if (index == 0 && size_ == 1) {
			item = first_;
			first_ = nullptr;
			last_ = nullptr;
		}
		else if (index == 0 && size_ > 1) {
			item = first_;
			first_ = first_->getNext();
			first_->setPrevious(last_);
			last_->setNext(first_);

		}
		else if (index == size_ - 1) {
			item = last_;
			first_->setPrevious(last_->getPrevious());
			last_->getPrevious()->setNext(first_);
			last_ = last_->getPrevious();
		}
		else {
			ObojZretLinkedListItem<T>* pred = getItemAtIndex(index - 1);
			item = pred->getNext();
			pred->setNext(item->getNext());
			(item->getNext())->setPrevious(pred);
			if (item == last_)
				last_ = pred;
		}
		T data = item->accessData();
		delete item;
		size_--;
		return data;
	}

	template<typename T>
	inline int ObojZretLinkedList<T>::getIndexOf(const T& data)
	{
		int index = 0;
		ObojZretLinkedListItem<T>* item = first_;
		if (item != nullptr) {
			do {
				if (item->accessData() == data)
					return index;
				index++;
				item = item->getNext();
			} while (item != first_);
		}
		return -1;
	}

	template<typename T>
	inline void ObojZretLinkedList<T>::clear()
	{
		ObojZretLinkedListItem<T>* item = first_;
		if (size_ > 0) {
			last_->setNext(nullptr);
			while (item != nullptr) {
				ObojZretLinkedListItem<T>* delItem = item;
				item = item->getNext();
				delete delItem;
			}
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
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in ObojZretLinkedList! GETITEMATINDEX");



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