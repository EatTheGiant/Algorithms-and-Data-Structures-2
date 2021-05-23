#pragma once
#include "structures/heap_monitor.h"
class Obec {
private:
	int predProd;
	int produktivny;
	int poProd;
	double celkovaVymera;
	double zastavanaPlocha;

public:
	Obec(int predProd, int produktivny, int poProd, double celkovaVymera, double zastavanaPlocha) :
		predProd(predProd),
		produktivny(produktivny),
		poProd(poProd),
		celkovaVymera(celkovaVymera),
		zastavanaPlocha(zastavanaPlocha)
	{
	}

	int getPredProd() { return predProd; }
	int getProduktivny() { return produktivny; }
	int getPoProd() { return poProd; }
	double getCelkovaVymera() { return celkovaVymera; }
	double getZastavanaPlocha() { return zastavanaPlocha; }
	//double getZastavanost() { return ( celkovaVymera / zastavanaPlocha) * 100; }
};