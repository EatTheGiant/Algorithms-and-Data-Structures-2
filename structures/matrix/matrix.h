#pragma once

#include "../structure.h"
#include "../structure_iterator.h"
#include "../ds_structure_types.h"
//#include "../ds_routines.h"

namespace structures {
	template<typename T>
	class Matrix : public Structure
	{
	public:
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;

		/// <summary> Vrati pocet prvkov v maici. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		virtual size_t size() const = 0;

		virtual size_t getPocetRiadkov() const = 0;
		virtual size_t getPocetStlpcov() const = 0;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (Matica), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je Matica. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Pole, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		virtual Matrix<T>& operator=(const Matrix<T>& other) = 0;

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		virtual T& operator[](const int index) = 0;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		virtual const T operator[](const int index) const = 0;

		/// <summary> Zmeni prvok v matici. </summary>
		/// <param name = "data"> Hodnota noveho prvku. </param>
		
		virtual void nastav(const size_t indexRiadku, const size_t indexStlpca, const T& data) = 0;

		virtual T& spristupni(const size_t indexRiadku, const size_t indexStlpca) = 0;


	protected:
		Matrix();
	};

	template<typename T>
	inline Matrix<T>::Matrix():
		Structure()
	{
	}

	template<typename T>
	inline Structure& Matrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}
}