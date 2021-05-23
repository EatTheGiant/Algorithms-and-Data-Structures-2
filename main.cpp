#include "structures/heap_monitor.h"
#include "testuj.h"
#include "structures/structure.h"
#include <stdio.h>
#include <Windows.h>

using namespace structures;
using namespace std;
int main()
{
	initHeapMonitor();
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	testuj* test = new testuj();;
	test->nacitajObce();
	test->spusti();
	delete test;
}