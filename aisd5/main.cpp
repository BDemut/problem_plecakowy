#include <iostream>
#include <string>
#include <fstream>
#include "Przedmiot.h"
#include "aw.h"
#include "az.h"
#include "apd.h"
#include "input.h"

void Clear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#endif
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
	int liczbaP{ 0 };
	int pojemnosc{ 0 };
	Przedmiot* listaP = nullptr;
	std::ifstream plik;

	bool kontynuuj{ true };
	while (kontynuuj)
	{
		std::cout << "Sposob wczytania danych:\n1 - z klawiatury\n2 - z pliku\n";
		char w{ Getchar("12") };
		switch (w)
		{
		case '1':
			std::cout << "Podaj liczbe przedmiotow: ";
			liczbaP = Getint();
			listaP = new Przedmiot[liczbaP];
			std::cout << "Podaj pojemnosc plecaka: ";
			pojemnosc = Getint();
			for (int i{ 0 }; i < liczbaP; i++)
			{
				std::cout << "Rozmiar przedmiotu " << i + 1 << " : ";
				listaP[i].rozmiar = Getint();
				std::cout << "Wartosc przedmiotu " << i + 1 << " : ";
				listaP[i].wartosc = Getint();
			}
			break;
		case '2':
			plik.open("dane.txt");
			if (plik)
			{
				plik >> liczbaP >> pojemnosc;
				if (plik.fail())
				{
					std::cout << "Bledne dane w pliku!\n";
					continue;
				}
				listaP = new Przedmiot[liczbaP];
				for (int i{ 0 }; i < liczbaP; i++)
				{
					plik >> listaP[i].rozmiar >> listaP[i].wartosc;
					if (plik.fail())
					{
						std::cout << "Bledne dane w pliku!\n";
						continue;
					}
				}
			}
			else
				std::cout << "Brak pliku \"dane.txt\"!\n";
			plik.close();
			break;
		default:
			throw "getchar nie dziala ;(";
		}
		bool kontynuuj2{ true };
		while (kontynuuj2)
		{
			std::cout << "Wybierz algorytm:\n1 - algorytm programowania dynamicznego\n";
			std::cout << "2 - algorytm zachlanny\n3 - algorytm wyczerpujacy\n4 - wprowadzenie nowych danych\n5 - wyjscie z programu\n";
			w = Getchar("12345");
			switch (w)
			{
			case '1':
				Czytaj(AProgDynamicznego(listaP, liczbaP, pojemnosc), listaP);
				break;
			case '2':
				Czytaj(AZachlanny(listaP, liczbaP, pojemnosc), listaP);
				break;
			case '3':
				Czytaj(AWyczerpujacy(listaP, liczbaP, pojemnosc), listaP);
				break;
			case '4':
				kontynuuj2 = false;
				
				Clear();
				delete[] listaP;
				listaP = nullptr;
				break;
			case '5':
				kontynuuj2 = false;
				kontynuuj = false;

				delete[] listaP;
				listaP = nullptr;
				break;
			default:
				throw "getchar nie dziala ;(";
			}
		}
	}
}