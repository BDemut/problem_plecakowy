#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include "Przedmiot.h"
#include "aw.h"
#include "az.h"
#include "apd.h"

void Clear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#endif
}

int Getint(int min = 1, int max = INT_MAX)
{
	int n;
	std::string smieci;
	do
	{
		std::cin >> n;
		std::cin.putback('0');
		std::cin >> smieci;
		if (std::cin.fail() || n < min || n > max || smieci != "0")
		{
			std::cin.clear();
			std::cout << "Podaj liczbe calkowita pomiedzy " << min << " a " << max << ": ";
		}
		std::cin.ignore(32767, '\n');
	} while (std::cin.fail() || n < min || n > max || smieci != "0");
	return n;
}

void Czytaj(std::vector<bool> wynik, const Przedmiot* const listaP)
{
	std::cout << "Uzyte przedmioty: ";
	int wartosc = 0;
	int rozmiar = 0;
	for (unsigned int i{ 0 }; i < wynik.size(); i++)
	{
		if (wynik[i])
		{
			std::cout << i + 1 << ' ';
			wartosc += listaP[i].wartosc;
			rozmiar += listaP[i].rozmiar;
		}
	}
	std::cout << "\nWartosc przedmiotow: " << wartosc << "\nRozmiar przedmiotow: " << rozmiar << '\n';
}

int main()
{
	srand(time(0));

	const int liczbyP[] = { 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25 };
	const int liczbyP_size = 11;

	const int pojemnosci[] = { 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25 };
	const int pojemnosci_size = 11;
	const int b = 5;

	const int liczba_pomiarow = 5;
	const int ZAKRESROZMIAR = 30;
	const int ZAKRESWARTOSC = 30;
	std::ofstream wynik("wynik.txt");

	double pomiaryAW[liczba_pomiarow][pojemnosci_size][liczbyP_size];
	double pomiaryAZ[liczba_pomiarow][pojemnosci_size][liczbyP_size];
	bool optymalneAZ[liczba_pomiarow][pojemnosci_size][liczbyP_size];
	double pomiaryAPD[liczba_pomiarow][pojemnosci_size][liczbyP_size];

	Przedmiot* listaP = nullptr;
	for (int x{ 0 }; x < liczba_pomiarow; x++)
	{
		for (int xx{ 0 }; xx < pojemnosci_size; xx++)
		{
			int pojemnosc = pojemnosci[xx];
			for (int xxx{ 0 }; xxx < liczbyP_size; xxx++)
			{
				std::cout << "x:" << x << " xx:" << xx << " xxx:" << xxx << '\n';
				int liczbaP = liczbyP[xxx];
				listaP = new Przedmiot[liczbaP];
				for (int i{ 0 }; i < liczbaP; i++)
				{
					listaP[i].rozmiar = (rand() % pojemnosc) + 1;
					listaP[i].wartosc = (rand() % pojemnosc) + 1;
				}

				auto start = std::chrono::steady_clock::now();
				auto apdwynik = AProgDynamicznego(listaP, liczbaP, pojemnosc);
				auto end = std::chrono::steady_clock::now();

				std::chrono::duration<double> elapsed{ end - start };
				pomiaryAPD[x][xx][xxx] = elapsed.count();

				start = std::chrono::steady_clock::now();
				auto azwynik = AZachlanny(listaP, liczbaP, pojemnosc);
				end = std::chrono::steady_clock::now();

				elapsed = end - start;
				pomiaryAZ[x][xx][xxx] = elapsed.count();

				start = std::chrono::steady_clock::now();
				AWyczerpujacy(listaP, liczbaP, pojemnosc);
				end = std::chrono::steady_clock::now();

				elapsed = end - start;
				pomiaryAW[x][xx][xxx] = elapsed.count();

				optymalneAZ[x][xx][xxx] = apdwynik == azwynik ? true : false;

				delete[] listaP;
				listaP = nullptr;
			}
		}
	}

	double srAPD[pojemnosci_size][liczbyP_size];
	double srAZ[pojemnosci_size][liczbyP_size];
	double srAW[pojemnosci_size][liczbyP_size];

	for (int xx{ 0 }; xx < pojemnosci_size; xx++)
	{
		for (int xxx{ 0 }; xxx < liczbyP_size; xxx++)
		{
			srAPD[xx][xxx] = 0;
			srAZ[xx][xxx] = 0;
			srAW[xx][xxx] = 0;
			int dzielnikAZ = 0;
			for (int x{ 0 }; x < liczba_pomiarow; x++)
			{
				srAPD[xx][xxx] += pomiaryAPD[x][xx][xxx];
				if (optymalneAZ[x][xx][xxx])
				{
					srAZ[xx][xxx] += pomiaryAZ[x][xx][xxx];
					dzielnikAZ += 1;
				}
				srAW[xx][xxx] += pomiaryAW[x][xx][xxx];
			}
			srAPD[xx][xxx] /= liczba_pomiarow;
			srAZ[xx][xxx] /= dzielnikAZ;
			srAW[xx][xxx] /= liczba_pomiarow;
		}
	}

	wynik << "\n\tAPD:\n";
	for (int xx{ 0 }; xx < pojemnosci_size; xx++)
	{
		wynik << "Pojemnosc " << pojemnosci[xx] << '\n';
		for (int xxx{ 0 }; xxx < liczbyP_size; xxx++)
			wynik << srAPD[xx][xxx] << '\n';
	}
	wynik << "\n\tAZ:\n";
	for (int xx{ 0 }; xx < pojemnosci_size; xx++)
	{
		wynik << "Pojemnosc " << pojemnosci[xx] << '\n';
		for (int xxx{ 0 }; xxx < liczbyP_size; xxx++)
			wynik << srAZ[xx][xxx] << '\n';
	}
	wynik << "\n\tAW:\n";
	for (int xx{ 0 }; xx < pojemnosci_size; xx++)
	{
		wynik << "Pojemnosc " << pojemnosci[xx] << '\n';
		for (int xxx{ 0 }; xxx < liczbyP_size; xxx++)
			wynik << srAW[xx][xxx] << '\n';
	}
}