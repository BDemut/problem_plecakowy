#include "Przedmiot.h"
#include <vector>
#include <algorithm>
#include <iostream>

struct PrzedmiotZ
{
	Przedmiot przedmiot;
	int id;
	double wsp;
};

bool PorownanieWspolczynnikow(PrzedmiotZ wiekszy, PrzedmiotZ mniejszy) {return wiekszy.wsp > mniejszy.wsp;}

std::vector<bool> AZachlanny(const Przedmiot* const listaP, const int liczbaP, int pojemnosc)
{
	std::vector<PrzedmiotZ> listaPZ(liczbaP);
	std::vector<bool> wynik(liczbaP);

	for (int i{ 0 }; i < liczbaP; i++)
	{
		listaPZ[i].przedmiot = listaP[i];
		listaPZ[i].id = i;
		listaPZ[i].wsp = static_cast<double>(listaP[i].wartosc) / static_cast<double>(listaP[i].rozmiar);
		wynik[i] = false;
	}

	std::sort(listaPZ.begin(), listaPZ.end(), PorownanieWspolczynnikow);

	for (int i{ 0 }; i < liczbaP && pojemnosc > 0; i++)
		if (listaPZ[i].przedmiot.rozmiar <= pojemnosc)
		{
			wynik[listaPZ[i].id] = true;
			pojemnosc -= listaPZ[i].przedmiot.rozmiar;
		}

	return wynik;
}