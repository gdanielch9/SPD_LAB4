// SPD_LAB2KD.cpp : Defines the entry point for the console application.
//

#include <vector>  //Wektor, kontener
#include <fstream>  //Do obs³ugi plików
#include <iostream> //cin cout
#include <string>
#include <queue>


using namespace std;

class Zadanie {
public:
	int numerZadania;
	int terminDostepnosci;  //r
	int czasObslugiZad;		//p
	int czasDostarczaniaZad;//q
	//int terminZakonczeniaZad;  //C
};


vector<Zadanie> dane;
vector<int> cZadan;
vector<int> kolejnoscWykonywaniaZadan;

struct PorownajQ
{
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2)
	{
		//kolejnoœæ - malejco
		if (zadanie1.czasDostarczaniaZad > zadanie2.czasDostarczaniaZad) return false;

		if (zadanie1.czasDostarczaniaZad < zadanie2.czasDostarczaniaZad) return true;
		return false;
	}
};

struct PorownajR
{
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2)
	{
		//kolejnoœæ - malejco
		if (zadanie1.terminDostepnosci > zadanie2.terminDostepnosci) return true;

		if (zadanie1.terminDostepnosci < zadanie2.terminDostepnosci) return false;
		return false;
	}
};


int Schrage()
{
								 //tworzymy kolejke
	priority_queue < Zadanie, vector < Zadanie >, PorownajQ > kolejkaQ; //Zbior G
	priority_queue < Zadanie, vector < Zadanie >, PorownajR > kolejkaR; //Zbior N

	for (unsigned int i = 0; i < dane.size(); i++)
		kolejkaR.push(dane[i]); //wrzucenie do kolejki

	//Algorytm Schrage
	int t, k, Cmax;
	t = k = Cmax = 0;
	//             N                     G
	while ( !(kolejkaR.empty()) || !(kolejkaQ.empty()) )
	{
		while (!(kolejkaR.empty()) && (kolejkaR.top().terminDostepnosci <= t))
			{
			//	cout << kolejkaR.top().terminDostepnosci << " ";
				kolejkaQ.push(kolejkaR.top()); //wrzucenie do kolejki cale zadanie
				kolejkaR.pop(); //wyrzucamy element ze zbioru N
			}
		if (kolejkaQ.empty()) //pkt 5, jezeli zbior G jest pusty
		{
			t = kolejkaR.top().terminDostepnosci;
			continue;
		}
		k++;
		t = t + kolejkaQ.top().czasObslugiZad;
		//tutaj wezmiemy indekx/numer zadania do wektora
		Cmax = max(Cmax, t + kolejkaQ.top().czasDostarczaniaZad);
		kolejnoscWykonywaniaZadan.push_back(kolejkaQ.top().numerZadania);

		cZadan.push_back(t + kolejkaQ.top().czasDostarczaniaZad);//przypisujemy czas wykonania zadania do carliera

		kolejkaQ.pop();
	}

	cout << "\n" << "Cmax: " << Cmax; 

	return Cmax;
}

void WczytajDane()
{
	fstream file;			 //Plik z danymi.
	string fileName;			//Nazwa pliku do ktorego zostana wczytane dane
	cout << "\nPodaj nazwe pliku: ";
	//std::cin >> fileName;
	fileName = "SCHRAGE2.dat";
	cout << "Nazwa pliku " << fileName << endl;
	file.open(fileName, std::ios::in);

	int liczbaZadan;	//format pliku: n  r p q r p q ...

	if (file.good() == true) {
		Zadanie obiektTmp;		//obiekt tymczasowy do wrzucania danych do wektora

		file >> liczbaZadan;	 //odczytuje z pliki pierwsza linijke - ile zadan

		for (int i = 0; i < liczbaZadan; i++) {
			obiektTmp.numerZadania = i;					//przypisanie numery zadania
			file >> obiektTmp.terminDostepnosci;		//wczytanie r
			file >> obiektTmp.czasObslugiZad;			//wczytanie p
			file >> obiektTmp.czasDostarczaniaZad;		//wcyztanie q   --- drugie zad 
			dane.push_back(obiektTmp);					//wrzucenie calego obiektu na koniec
		}
		//*****WYSWIETLANIE WCZYTANYCH DANYCH*****
		cout << "Liczba zad: " << liczbaZadan << endl;
		//cout << "Wczytane dane: \n";
		//cout << liczbaZadan << endl;
		file.close();		//zamkniecie pliku
	}
	else cout << "Nie mozna wczytac pliku" << std::endl;
}

int main()
{
	int U;	
	//vector<Zadanie> dane; //Tutaj beda sie znajdowac wczytane dane z pliku
	WczytajDane();
	int n = dane.size();
	int C = Schrage();

	




	int b = 0,bi=0, a = 10000000,ai, c=0, ci;
	for(int i = 0; i < n; i++) 
	{
		if (b < cZadan[i])
		{
			b = cZadan[i];
			bi = i;
		}
		//Cmax[i] = C+ dane[i].czasDostarczaniaZad;
	}
	cout << "b: " << b << " bi: " << bi << endl;

	cout << "kolejnoscWykonywaniaZadan.size() : " << kolejnoscWykonywaniaZadan.size() << endl;

	for (int i = 0; i < n; i++)
	{
		int suma = 0;
		for (int j = i; j < bi; j++)
		{
			suma += dane[kolejnoscWykonywaniaZadan[i]].czasObslugiZad;
		}

		if (a > dane[kolejnoscWykonywaniaZadan[i]].terminDostepnosci + suma + dane[kolejnoscWykonywaniaZadan[bi]].czasDostarczaniaZad)
		{
			a = dane[kolejnoscWykonywaniaZadan[i]].terminDostepnosci + suma + dane[kolejnoscWykonywaniaZadan[bi]].czasDostarczaniaZad;
			ai = i;
		}
//		dane[i].terminDostepnosci 
		//cout << kolejnoscWykonywaniaZadan[i] << " ";
	}

	
	//wypisanie kolejnosci wykonywania zadan
	cout << "\nKolejnosc Wy" << endl;
	for (int i = 0; i < dane.size(); i++)
	{
		cout << kolejnoscWykonywaniaZadan[i]<<" ";
	}
	cout << endl;
	//


	for (int i = kolejnoscWykonywaniaZadan[ai]; i <= kolejnoscWykonywaniaZadan[bi]; i++)
	{
		if (c < dane[kolejnoscWykonywaniaZadan[bi]].czasDostarczaniaZad)
		{
			c = dane[kolejnoscWykonywaniaZadan[bi]].czasDostarczaniaZad;
			ci = i;
		}
	}

	cout << "a : " << a << " ai: "<<kolejnoscWykonywaniaZadan[ai]<< endl;
	cout << "c : " << c << " ci: " <<kolejnoscWykonywaniaZadan[ci] << endl;

	U = Schrage();

	getchar();
	return 0;
}