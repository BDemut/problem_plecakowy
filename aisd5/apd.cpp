#include "Przedmiot.h"
#include <vector>

void OdczytajWynik(const std::vector<std::vector<int>> macierz, int i, int j, const Przedmiot* const listaP, std::vector<bool> &wynik)
{
	if (i == 0)
		return;

	if (macierz[i][j] == macierz[i - 1][j])
	{
		wynik[i - 1] = false;
		OdczytajWynik(macierz, i - 1, j, listaP, wynik);
	}
	else if (macierz[i][j] > macierz[i - 1][j])
	{
		wynik[i - 1] = true;
		OdczytajWynik(macierz, i - 1, j - listaP[i - 1].rozmiar, listaP, wynik);
	}
	else
		throw "nieprawidlowe dane w macierzy!";
}

std::vector<bool> AProgDynamicznego(const Przedmiot* const listaP, const int liczbaP, const int pojemnosc)
{
	std::vector<std::vector<int>> macierz(liczbaP + 1);

	for (int i{ 0 }; i < liczbaP + 1; i++)
	{
		macierz[i].resize(pojemnosc + 1);
		
		for (int j{ 0 }; j < pojemnosc + 1; j++)
		{
			if (i == 0 || j == 0)
				macierz[i][j] = 0;
			else if (listaP[i - 1].rozmiar > j)
				macierz[i][j] = macierz[i - 1][j];
			else
			{
				int a{ macierz[i - 1][j - listaP[i - 1].rozmiar] + listaP[i - 1].wartosc };
				int b{ macierz[i - 1][j] };
				macierz[i][j] = a > b ? a : b;
			}
		}
	}

	std::vector<bool> wynik(liczbaP);
	OdczytajWynik(macierz, liczbaP, pojemnosc, listaP, wynik);
	return wynik;
}