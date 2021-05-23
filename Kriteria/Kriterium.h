#pragma once
#include <string>

using namespace std;

template<typename T, typename O>
class Kriterium
{
public:
	Kriterium();

	virtual T ohodnot(O o);

	~Kriterium();
};

template<typename T, typename O>
inline Kriterium<T, O>::Kriterium()
{

}

template<typename T, typename O>
inline T Kriterium<T, O>::ohodnot(O o)
{
	return T();
}

template<typename T, typename O>
inline Kriterium<T, O>::~Kriterium()
{
}