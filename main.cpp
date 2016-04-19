// SPD_LAB2KD.cpp : Defines the entry point for the console application.
//

#include <vector>  //Wektor, kontener
#include <fstream>  //Do obs�ugi plik�w
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
		//kolejno�� - malejco
		if (zadanie1.czasDostarczaniaZad > zadanie2.czasDostarczaniaZad) return false;

		if (zadanie1.czasDostarczaniaZad < zadanie2.czasDostarczaniaZad) return true;
		return false;
	}
};

struct PorownajR
{
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2)
	{
		//kolejno�� - malejco
		if (zadanie1.terminDostepnosci > zadanie2.terminDostepnosci) return true;

		if (zadanie1.terminDostepnosci < zadanie2.terminDostepnosci) return false;
		return false;
	}
};

void WczytajDane(string fileName)
{
	fstream file;			 //Plik z danymi.

	cout << "\nPodaj nazwe pliku: ";
	//std::cin >> fileName;
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

		cZadan.push_back(t);//przypisujemy czas wykonania zadania do carliera

		kolejkaQ.pop();
	}

	cout << "\n" << "Cmax: " << Cmax << endl;;

	return Cmax;
}

int main()
{
	int U;	
	//vector<Zadanie> dane; //Tutaj beda sie znajdowac wczytane dane z pliku
	WczytajDane("SCHRAGE1.dat");
	int n = dane.size();
	int Cmax = Schrage();



	int b=0, a=0, c=0;
	// Wyznaczanie b
	for(int j = 0; j < n; j++) 
	{
		if (Cmax == cZadan[j] + dane[kolejnoscWykonywaniaZadan[j]].czasDostarczaniaZad)
		{
			b = j;
		}
	}

	// Wyznaczanie a
	for (int j = 0; j < n; j++)
	{
		int suma = 0;
		for (int s = j; s <= b; s++)
		{
			suma += dane[kolejnoscWykonywaniaZadan[s]].czasObslugiZad;
		}

		if (Cmax == dane[kolejnoscWykonywaniaZadan[j]].terminDostepnosci + suma + dane[kolejnoscWykonywaniaZadan[b]].czasDostarczaniaZad)
		{
			a = j;
			cout << "Znalazlem a" << endl;
			break;
		}
	}

	// Wyznaczanie c
	for (int j = kolejnoscWykonywaniaZadan[a]; j <= kolejnoscWykonywaniaZadan[b]; j++)
	{
		if (dane[kolejnoscWykonywaniaZadan[j]].czasDostarczaniaZad > dane[kolejnoscWykonywaniaZadan[b]].czasDostarczaniaZad)
		{
			cout << "Znalazlem c" << endl;
			c = j;
		}
	}

	//wypisanie kolejnosci wykonywania zadan
	cout << "\nKolejnosc Wy" << endl;
	for (int i = 0; i < dane.size(); i++)
	{
		cout << kolejnoscWykonywaniaZadan[i] << " ";
	}
	cout << endl;
	//
	cout << " bi: " << kolejnoscWykonywaniaZadan[b] << endl;
	cout << " ai: "<<kolejnoscWykonywaniaZadan[a]<< endl;
	cout << " ci: " <<kolejnoscWykonywaniaZadan[c] << " " << c << endl;

	U = Schrage();

	getchar();
	return 0;
}