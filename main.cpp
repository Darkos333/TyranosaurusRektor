#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>

using namespace std;

const int tyranosaurusRektor = 1;
const int magicznyMagister = 2;
const int dobryDoktor = 3;
const int wariackiWrzesien = 4;


void ekranStartowy(int& rozmiarMapy, int& poziomTrudnosci);
void rysujMape(int* mapa, int rozmiar, int gracz1, int gracz2);
void odswiezMape(int* mapa, int rozmiar, int gracz1, int gracz2, char aktualnyGracz, int rzutKostka);
int* generujMape(int rozmiarMapy, int poziomTrudnosci);
int rzutKostka();
string int2str(int liczba);

int main()
{
	int n = 0;
	int* mapa = NULL;
	int trudnosc = 1;
	int aktualnyGracz; //0-gracz A, 1-gracz B
	int pozycjeGraczy[2] = {0, 0};
	char znak;
	int tmp;

	srand(time(NULL));
	ekranStartowy(n, trudnosc);
	mapa = generujMape(n, trudnosc);

	system("cls");
	if(rand() % 2 == 0)
	{
		aktualnyGracz = 0;
		cout << "Zaczyna gracz A." << endl;
	}
	else
	{
		aktualnyGracz = 1;
		cout << "Zaczyna gracz B." << endl;
	}
	znak = _getch();
	if(znak == 'P' || znak == 'p') exit(0);

	system("cls");
	for(;; aktualnyGracz = !aktualnyGracz)
	{
		rysujMape(mapa, n, pozycjeGraczy[0], pozycjeGraczy[1]);
		cout << endl;

		char nazwaGracza = (char)(aktualnyGracz + 65);
		string komunikat = "";

		cout << "Gracz " << nazwaGracza << " rzuca kostka: ";
		znak = _getch();
		if(znak == 'P' || znak == 'p') exit(0);
		int rzut = rzutKostka();
		cout << rzut << endl;

		if(pozycjeGraczy[aktualnyGracz] + rzut >= n)
		{
			znak = _getch();
			if(znak == 'P' || znak == 'p') exit(0);
			system("cls");
			cout << "Gracz " << nazwaGracza << " ukonczyl studia!" << endl;
			cout << "GRATULACJE!!!" << endl;
			_getch();
			exit(0);
		}
		else pozycjeGraczy[aktualnyGracz] += rzut;

		switch(mapa[pozycjeGraczy[aktualnyGracz]])
		{
		case 0:
			komunikat = "";
			break;
		case tyranosaurusRektor:
			odswiezMape(mapa, n, pozycjeGraczy[0], pozycjeGraczy[1], nazwaGracza, rzut);
			pozycjeGraczy[aktualnyGracz] = 0;
			komunikat = "Trafiles na Rektora w zlym humorze. \nTyranosaurus Rektor jednym ruchem niszczy twoje marzenia. Wracasz na start.";
			break;
		case magicznyMagister:
			odswiezMape(mapa, n, pozycjeGraczy[0], pozycjeGraczy[1], nazwaGracza, rzut);
			tmp = 1 + rand() % 4;
			if(rand() % 2 == 0) tmp *= -1;
			pozycjeGraczy[aktualnyGracz] += tmp;
			if(pozycjeGraczy[aktualnyGracz] < 0) pozycjeGraczy[aktualnyGracz] = 0;
			komunikat = "Trafiles na Magicznego Magistra. \"Prosze chwileczke poczekac\"\nChyba rzuca jakies zaklecie... ";
			if(tmp < 0) komunikat += int2str(abs(tmp)) + " do tylu.";
			else  komunikat += to_string(tmp) + " do przodu.";
			break;
		case dobryDoktor:
			odswiezMape(mapa, n, pozycjeGraczy[0], pozycjeGraczy[1], nazwaGracza, rzut);
			tmp = 1 + rand() % 3;
			pozycjeGraczy[aktualnyGracz] += tmp;
			komunikat = "Trafiles na Dobrego Doktora. Powiedz Dziekuje Pan Doktor a zdrowie i dobrobyt beda Ci dane.\n";
			komunikat += int2str(tmp) + " do przodu.";
			break;
		case wariackiWrzesien:
			odswiezMape(mapa, n, pozycjeGraczy[0], pozycjeGraczy[1], nazwaGracza, rzut);
			tmp = -1 * (1 + rand() % 3);
			pozycjeGraczy[aktualnyGracz] += tmp;
			if(pozycjeGraczy[aktualnyGracz] < 0) pozycjeGraczy[aktualnyGracz] = 0;
			komunikat = "Wyglada na to ze masz nowe plany na wrzesien.\n";
			komunikat += int2str(abs(tmp)) + " do tylu.";
			break;
		}

		cout << komunikat << endl;
		znak = _getch();
		if(znak == 'P' || znak == 'p') exit(0);
		system("cls");
	}
}

void ekranStartowy(int& rozmiarMapy, int& poziomTrudnosci)
{
	system("cls");
	cout << "Witajcie w grze Tyranosaurus Rektor." << endl;
	cout << "Jest to gra na 2 graczy: A i B." << endl;
	cout << "Wybierzcie swoje pionki przed rozpoczeciem rozgrywki." << endl;
	cout << "Celem gry jest ukonczenie studiow, czyli dotarcie na drugi koniec planszy." << endl;
	cout << "Jak to w zyciu bywa wiele zalezy tu od szczescia :)" << endl;
	cout << endl;

	cout << "Podaj ilosc semestrow - ilosc pol na planszy (minimum 7)" << endl;
	for(;;)
	{
		cout << "semestry = ";
		cin >> rozmiarMapy;
		cout << endl;
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else break;
	}
	if(rozmiarMapy < 7) rozmiarMapy = 7;
	cout << endl;

	cout << "Wybierz poziom trudnosci:" << endl;
	cout << "1 - studia dzienne" << endl;
	cout << "2 - studia zaoczne" << endl;
	for(;;)
	{
		cout << "trudnosc = ";
		cin >> poziomTrudnosci;
		cout << endl;
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else break;
	}
	if(poziomTrudnosci != 1 && poziomTrudnosci != 2) poziomTrudnosci = 1;

	cout << "Gotowy do gry!" << endl;
	cout << rozmiarMapy << " semetrow na poziomie trudnosci " << poziomTrudnosci << endl;
	cout << "Aby przerwac gre wcisnij klawisz P. Aby grac wciskaj dowolny inny klawisz." << endl;
	char znak;
	znak = _getch();
	if(znak == 'P' || znak == 'p') exit(0);
}

void rysujMape(int* mapa, int rozmiar, int gracz1, int gracz2)
{
	if(gracz1 != gracz2)
	{
		cout << endl;
		for(int i = 0; i < rozmiar; i++)
		{
			if(i == gracz1) cout << 'A';
			else if(i == gracz2) cout << 'B';
			else cout << '_';
		}
	}
	else
	{
		for(int i = 0; i < rozmiar; i++)
		{
			if(i == gracz1) cout << 'A';
			else cout << ' ';
		}
		cout << endl;
		for(int i = 0; i < rozmiar; i++)
		{
			if(i == gracz2) cout << 'B';
			else cout << '_';
		}
	}
	cout << endl;

	for(int i = 0; i < rozmiar; i++)
	{
		if(mapa[i] == 0) cout << '#';
		else if(mapa[i] == tyranosaurusRektor) cout << '!';
		else cout << '?';
	}
	cout << endl;
}

int* generujMape(int rozmiarMapy, int poziomTrudnosci)
{
	int ileRektorow;
	int ileBonusow;
	int ilePoprawek;
	int* mapa = new int[rozmiarMapy];
	for(int i = 0; i < rozmiarMapy; i++) mapa[i] = 0;

	//Ustawienia trudnosci
	if(poziomTrudnosci == 1)
	{
		ileRektorow = rozmiarMapy / 21;
		if(ileRektorow < 1) ileRektorow = 1;
		ileBonusow = rand() % 7;
		ileBonusow *= sqrt(rozmiarMapy)/2;
		if(ileBonusow > rozmiarMapy / 5) ileBonusow = rozmiarMapy / 5;
		if(ileBonusow < 2) ileBonusow = 2;
		ilePoprawek = 0;
	}
	else
	{
		ileRektorow = rozmiarMapy / 11;
		if(ileRektorow < 1) ileRektorow = 1;
		ileBonusow = rand() % 5;
		ileBonusow *= sqrt(rozmiarMapy)/2;
		if(ileBonusow > rozmiarMapy / 5) ileBonusow = rozmiarMapy / 5;
		if(ileBonusow < 2) ileBonusow = 2;
		ilePoprawek = ileBonusow / 2;
		if(ilePoprawek < 1) ilePoprawek = 1;
	}

	//Wypelnianie mapy
	int x;
	for(int i = 0; i < ileRektorow; i++)
	{
		do
		{
			x = 1 + rand() % (rozmiarMapy - 1);
		} while(mapa[x] != 0);
		mapa[x] = tyranosaurusRektor;
	}
	for(int i = 0; i < ileBonusow; i++)
	{
		do
		{
			x = 1 + rand() % (rozmiarMapy - 1);
		} while(mapa[x] != 0);
		if(rand() % 2 == 0) mapa[x] = magicznyMagister;
		else mapa[x] = dobryDoktor;
	}
	for(int i = 0; i < ilePoprawek; i++)
	{
		do
		{
			x = 1 + rand() % (rozmiarMapy - 1);
		} while(mapa[x] != 0);
		mapa[x] = wariackiWrzesien;
	}
	
	return mapa;
}

int rzutKostka()
{
	return 1 + rand() % 6;
}

void odswiezMape(int* mapa, int rozmiar, int gracz1, int gracz2, char aktualnyGracz, int rzutKostka)
{
	system("cls");
	rysujMape(mapa, rozmiar, gracz1, gracz2);
	cout << endl;
	cout << "Gracz " << aktualnyGracz << " rzuca kostka: " << rzutKostka << endl;
}

string int2str(int liczba)
{
	char* tmp = new char[32];
	string result = string(_itoa(liczba, tmp, 10));
	delete tmp;
	return result;
}
