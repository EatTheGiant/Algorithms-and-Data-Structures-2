#include "structure.h"
#include "heap_monitor.h"
#include <tchar.h>

namespace structures {

	Structure::Structure()
	{
	}

	Structure::~Structure()
	{
	}

	bool Structure::isEmpty() const
	{
		return size() == 0;
	}

}