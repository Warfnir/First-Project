#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <string>

//ZMIENNE GLOBALNE

const int size = 16;
int history[size][size][10];
int map[size][size];
int nowa[size][size];

int countCells(int tab[size][size], int x, int y)	//FUNCKJA ZLICZAJACE ZYWE KOMORKI
{													//WOKOL DANEJ W TABLICY
	int left_limit;					
	int right_limit;	
	int up_limit;					
	int	down_limit;		

	//OGRANICZA ZAKRES SPRAWDZANIA

	(x == 0 ? up_limit = x, down_limit = x + 1 : up_limit = x - 1, down_limit = x + 1);

	(x == size ? up_limit = x - 1, down_limit = x : up_limit = x - 1, down_limit = x + 1);

	(y == 0 ? left_limit = y, right_limit = y + 1 : left_limit = y - 1, right_limit = y + 1);

	(y == size ? left_limit = y - 1, right_limit = y : left_limit = y - 1, right_limit = y + 1);
	
	//ZLICZA ZYWE KOMORKI W TABLICY 3x3

	int cells = 0;
	for (int i = up_limit; i <= down_limit; i++)
	{
		for (int j = left_limit; j <= right_limit; j++)
		{
			if (map[i][j] == 1)
			{
				cells++;
			}
		}
	}
	return cells; //ZWRACA LICZBE ZYWYCH KOMOREK
}

int rules(int tab[size][size], int x, int y, int cells)		//SPRAWDZA ZYWOTNOSC KOMORKI NA MAPIE
{															//ZGODNIE Z ZASADAMI GRY
	(tab[x][y] == 1 ? cells = cells - 1 : cells=cells );	//I ZWRCACA JEJ NOWY STAN

	if (tab[x][y] && cells >3 || cells<2)
	{
		return 0;
	}
	if (tab[x][y] == 1 && (cells == 2 || cells == 3))
	{
		return 1;
	}
	if (tab[x][y]==0 && cells == 3)
	{
		return 1;
	}
	else { return 0; }	
}

void new_map(int tab[size][size])		//GENERUJE KOLEJNY STAN
{
	int cells=0;
	int x = 0;							//WIERSZ
	int y = 0;							//KOLUMNA

	for (x = 0; x < size; x++)			//PETLA SPRAWDZAJACA KAZDY ELEMENT TABLICY
	{
		for (y = 0; y < size; y++)
		{
			cells = countCells(map, x, y);			//NADAJE WARTOSC ZLICZONYCH ZYWYCH KOMOREK
			nowa[x][y] = rules(map, x, y, cells);	//PRZYPISUJE NOWEJ TABLICY ODP. STANT KOMOREK
		}
	}
}

void write_out(int tab[size][size])			//FUNKCJA WYPISUJACA WPROWADZONA TABLICE
{
	for (int wiersz = 0; wiersz < size; wiersz++)
	{
		for (int kolumna = 0; kolumna < size; kolumna++)
		{
			std::cout << tab[wiersz][kolumna];
		}
		std::cout << "\n";
	}
}

void replace(int tab[size][size], int nowa[size][size]) //NADAJE WARTOSCI KOMOREK JEDNEJ TABLICY
														//ODP. WARTOSCIOM DRUGIEJ TABLICY
{
	for (int wiersz = 0; wiersz < size; wiersz++)
	{
		for (int kolumna = 0; kolumna < size; kolumna++)
		{
			tab[wiersz][kolumna] = nowa[wiersz][kolumna];
		}
	}
}

void new_game(int tab[size][size])			//GENERUJE LOSOWA MAPE DO NOWEJ GRY
{
	std::srand(std::time(0));
							
	for (int wiersz = 0; wiersz < size; wiersz++)
	{
		for (int kolumna = 0; kolumna < size; kolumna++)
		{
			int losowa = std::rand();
			if (losowa % 2) 
			{
				map[wiersz][kolumna] = 1;
			}
			else
			{
				map[wiersz][kolumna] = 0;
			}
		}
	}
}

void write_out_3D()		//WYPISUJE HISTORIE STANOW
{
	for (int x = 0; x < size; x++)			//WYPISUJE HISTORIE 0-2
	{
		for (int i = 0; i < 3; i++)
		{
			for (int y = 0; y < size; y++)
			{
				std::cout << history[x][y][i];
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	for (int x = 0; x < size; x++)			//WYPISUJE HISTORIE 3-5
	{
		for (int i = 3; i < 6; i++)
		{
			for (int y = 0; y < size; y++)
			{
				std::cout << history[x][y][i];
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	for (int x = 0; x < size; x++)			//WYPISUJE HISTORIE 6-8
	{
		for (int i = 6; i < 9; i++)
		{
			for (int y = 0; y < size; y++)
			{
				std::cout << history[x][y][i];
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	for (int x = 0; x < size; x++)			//WYPISUJE HISTORIE 9
	{
		for (int y = 0; y < size; y++)
		{
			std::cout << history[x][y][9];
		}
		std::cout << "\n";
	}
}

int compare(int i, int next)		//POROWNUJE TABLICE 3 WYMIAROWA
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (history[x][y][i] != history[x][y][next])
			{
				return 0;
			}
		}
	}
	return 1;
}

void hist()			//ZAPIS 10 OSTATNICH STANOW
{
	for (int i = 9; i >= 0; i--)
	{ 
		for (int x = 0; x < size; x++)
		{ 
			for (int y = 0; y < size; y++)
			{
				(i != 0 ? history[x][y][i] = history[x][y][i - 1] : history[x][y][i] = map[x][y]);
			}
		}
	}
}

void save()		//FUNKCJA ZAPISUJACA AKTUALNA MAPE DO PLIKU
{
	std::ofstream last_game("save.txt");	//TYP OFSTREAM WCZYTYWANIE Z PLIKU
	if (last_game.good() == true)			//SPRAWDZENIE CZY PLIK ZOSTAL OTWARTY
	{
		for (int x=0; x < size; x++)
		{
			for (int y=0; y < size; y++)
			{
				last_game << map[x][y];		//WRZUCANIE DO PLIKU N-TEGO ELEMENTU MAPY
			}
			
		}
		last_game.close();
	}
	else
	{
		std::cout << "Couldn't open file";
	}
}

void load()		//FUNKCJA WCZYTUJACA MAPE Z PLIKU
{
	std::ifstream last_game("save.txt");	//TYP IFSTREAM WCZYTYWANIE Z PLIKU
											//LAST_GAME NAZWA ZMIENNEJ TYPU IFSTREAM
											//"SAVE.TXT" NAZWA PLIKU EW. JEGO SCIEZKA
	if (last_game.good() == true)			//SPRAWDZENIE CZY PLIK ZOSTAL OTWARTY
	{
		std::string line;
		last_game >> line;					//NADANIE ZMIENNEJ LINE CIAGU ZNAKOW Z PLIKU
		int n = 0;
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				std::string shadow;					//UTWORZENIE NOWEJ ZMIENNEJ TYPU STRING
				shadow = line[n];					//PRZYPISANIE SHADOW N-TEGO ZNAKU LINE
				map[x][y] = atoi(shadow.c_str());	//RZUTOWANIE/KONWERSJA SHADOW Z TYPU STRING NA INT
				n++;
			}
		}
		
	}
	else
	{
		std::cout << "Couldn't open file";
	}
}

int check_cycle()			//SPRAWDZA CZY NASTAPIL CYKL
{
	for (int i = 0; i < 10; i++)
	{
		for (int next = (i + 1); next < 10; next++)
		{
			if (compare(i, next) == 1)
			{
				std::cout << "NEW CYCLE!\n";
				write_out_3D();
				return 0;
			}
		}
	}
	return 0;
}

void esential(int counter)		//DZIALANIE SAMEJ GRY
{
	counter++;
	char a;
	std::cin.get(a);
	switch (a)
	{
	case '1':
		break;
	case '2':
		save();
		std::cin.ignore();
	case ('\n'):
		system("cls");
		new_map(map);
		replace(map, nowa);
		write_out(map);
		hist();
		if (counter > 10)
		{
			check_cycle();
		}
	}
	esential(counter);
}
	
int main()
{
	int counter = 0;
	char a;
	std::cout << "1-NEW GAME\n" << "2-LOAD PREVIOUS GAME\n" << "3-QUIT\n";
	std::cin.get(a);
	switch (a)
	{
	case '1':
		new_game(map);
		write_out(map);
		std::cin.ignore();
		esential(counter);
		break;
	case '2':
		load();
		write_out(map);
		std::cin.ignore();
		esential(counter);
		break;
	case '3':
		return 0;
		break;
	}
}