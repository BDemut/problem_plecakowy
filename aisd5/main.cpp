#include <iostream>
#include <string>
#include <fstream>

class Przedmiot
{
public:
	int rozmiar = 0;
	int wartosc = 0;
};

int getint(int min = 1, int max = INT_MAX)
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

int main()
{
	int n{ 0 };
	int c{ 0 };
	Przedmiot* listaP;
	bool kontynuuj{ true };
	std::ifstream plik;

	while (kontynuuj)
	{
		std::cout << "Sposob wczytania danych:\n1 - z klawiatury\n2 - z pliku\n";
		char w;
		std::cin >> w;
		switch (w)
		{
		case '1':
			std::cout << "Podaj liczbe przedmiotow: ";
			n = getint();
			listaP = new Przedmiot[n];
			std::cout << "Podaj pojemnosc plecaka: ";
			c = getint();
			for (int i{ 0 }; i < n; i++)
			{
				std::cout << "Rozmiar przedmiotu " << i << " : ";
				listaP[i].rozmiar = getint();
				std::cout << "Wartosc przedmiotu " << i << " : ";
				listaP[i].wartosc = getint();
			}
		case '2':
			plik.open("dane.txt");
			if (plik)
			{
				plik >> n >> c;
				if (plik.fail())
				{
					std::cout << "Bledne dane w pliku!\n";
					continue;
				}
				listaP = new Przedmiot[n];
				for (int i{ 0 }; i < n; i++)
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
			std::cout << "Podano nieprawidlowy znak!\n";
			continue;
		}
		bool kontynuuj2{ true };
		while (kontynuuj2)
		{
			std::cout << "Wybierz algorytm:\n1 - algorytm programowania dynamicznego\n";
			std::cout << "2 - algorytm zachlanny\n3 - algorytm wyczerpujacy\n4 - wprowadzenie nowych danych\n5 - wyjscie z programu\n";
			char w;
			std::cin >> w;
			switch (w)
			{
			case '1':
			case '2':
			case '3':
			case '4':
				kontynuuj2 = false;
				break;
			case '5':
				kontynuuj2 = false;
				kontynuuj = false;
				break;
			}
		}
	}
}