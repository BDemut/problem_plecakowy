#include <iostream>
#include <string>

int Getint(int min = 1, int max = INT_MAX)
{
	int n;
	std::string smieci;
	bool petla;
	do
	{
		std::cin >> n;
		std::cin.putback('0');
		std::cin >> smieci;
		if (std::cin.fail() || n < min || n > max || smieci != "0")
		{
			std::cout << "Podaj liczbe calkowita pomiedzy " << min << " a " << max << ": ";
			std::cin.clear();
			petla = true;
		}
		else
			petla = false;
		std::cin.ignore(32767, '\n');
	} while (petla);
	return n;
}

char Getchar(std::string dozwoloneZnaki = "")
{
	char c;
	std::string smieci;
	bool jest = true;
	do
	{
		std::cin.clear();
		std::cin >> c;
		std::cin.putback('0');
		std::cin >> smieci;
		if (std::cin.fail() || smieci != "0")
			std::cout << "Podano nieprawidlowy znak / ciag znakow!\n";
		else if (dozwoloneZnaki != "")
			if (dozwoloneZnaki.find(c) == std::string::npos)
			{
				std::cout << "Podano nieprawidlowy znak!\n";
				jest = false;
			}
			else
				jest = true;
		std::cin.ignore(32767, '\n');
	} while (std::cin.fail() || smieci != "0" || !jest);
	return c;
}