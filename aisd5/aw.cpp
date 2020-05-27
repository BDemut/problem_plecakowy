#include "Przedmiot.h"
#include <vector>
#include <cmath>

std::vector<bool> AWyczerpujacy(const Przedmiot* const listaP, const int liczbaP, const int pojemnosc)
{
	if (liczbaP > sizeof(unsigned long long) * 8)
		throw "Wykonanie algorytmu niemozliwe - zbyt duza liczba przedmiotow";
	
	int max = 0;
	unsigned long long lWynik = 0;
	unsigned long long maxI = 1;
	for (int i{ 0 }; i < liczbaP; i++)
		maxI *= 2;

	for (unsigned long long i{ 0 }; i < maxI; i++)
	{
		unsigned long long bity = i;
		int rozmiar = 0;
		int wartosc = 0;
		for (int j{ 0 }; j < liczbaP; j++)
		{
			if (bity & 1)
			{
				rozmiar += listaP[j].rozmiar;
				wartosc += listaP[j].wartosc;
			}
			bity >>= 1;
		}
		if (rozmiar <= pojemnosc)
			if (wartosc > max)
			{
				max = wartosc;
				lWynik = i;
			}
	}
	
	std::vector<bool> wynik(liczbaP);
	for (int i{ 0 }; i < liczbaP; i++)
	{
		if (lWynik & 1)
			wynik[i] = true;
		else
			wynik[i] = false;
		lWynik >>= 1;
	}

	return wynik;
}