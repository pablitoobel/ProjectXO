#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

//Ka¿de pole jest struktora, ktora ma swoje parametry typu:znak, czyJestKomputerem itd.
struct pole {
	char znak;
	int czyJestKomputerem;
	int dostepne;
	int pustePole;
	int wybranePole;
};

//wype³ania plansze
void wypelnianie(pole **plansza) {
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			plansza[i][j].dostepne = 1;
			plansza[i][j].czyJestKomputerem = 0;
		}
	}

	plansza[0][0].dostepne = 0;
	plansza[0][1].dostepne = 0;
	plansza[0][5].dostepne = 0;
	plansza[0][6].dostepne = 0;
	plansza[1][0].dostepne = 0;
	plansza[1][1].dostepne = 0;
	plansza[1][5].dostepne = 0;
	plansza[1][6].dostepne = 0;
	plansza[5][0].dostepne = 0;
	plansza[5][1].dostepne = 0;
	plansza[5][5].dostepne = 0;
	plansza[5][6].dostepne = 0;
	plansza[6][0].dostepne = 0;
	plansza[6][1].dostepne = 0;
	plansza[6][5].dostepne = 0;
	plansza[6][6].dostepne = 0;

	for (int i = 0; i < 7; i++)
	{
		plansza[4][i].znak = 'x';
	}
	plansza[5][2].znak = 'x';
	plansza[5][3].znak = 'x';
	plansza[5][4].znak = 'x';
	plansza[6][2].znak = 'x';
	plansza[6][3].znak = 'x';
	plansza[6][4].znak = 'x';

	plansza[3][3].czyJestKomputerem = 1;
	plansza[3][3].znak = 'o';

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (plansza[i][j].dostepne == 1 and plansza[i][j].znak != 'x' and plansza[i][j].znak != 'o') //szuka pola ktore jest puste
				plansza[i][j].pustePole = 1;
			else
				plansza[i][j].pustePole = 0;
		}
	}
}


//wypisuje plansze
void wypisz(pole **plansza) {
	char znak = 71;
	for (int i = 0; i < 7; i++)
	{
		cout <<char( znak - i);
		for (int j = 0; j < 7; j++)
		{

			if (plansza[i][j].dostepne == 1)
				cout << " | ";
			else if (j > 0 and plansza[i][j].dostepne == 0 and plansza[i][j - 1].dostepne == 1)
				cout << " | ";
			else
				cout << "   ";
			if (plansza[i][j].znak == 'x')
				cout << 'x';
			else if (plansza[i][j].znak == 'o')
				cout << 'o';
			else
				cout << ' ';
			if (j == 6 and plansza[i][j].dostepne == 1)
				cout << " | ";
			
		}
	
		cout << endl;
		
		cout << endl;
	}
	cout << "  ";
	for (int i = 0; i < 7; i++)
	{
		cout <<"  "<< i<<" ";
	}
	cout << endl;

}

//jezeli pole jest X i ma naooko³o puste pola; czy jest to x którym da sie ruszyc
int DobrePole(pole **plansza, int wiersz, int kolumna) {
	if (plansza[wiersz][kolumna].znak == 'x' and (
		(wiersz - 1>=0 and plansza[wiersz - 1][kolumna].pustePole==1) or
		(wiersz + 1 <= 6 and plansza[wiersz + 1][kolumna].pustePole == 1) or 
		(kolumna - 1 >= 0 and plansza[wiersz][kolumna - 1].pustePole == 1) or 
		(kolumna +1 <= 6 and plansza[wiersz][kolumna + 1].pustePole == 1)))
		return 1;
	else
		return 0;
}

//DobrePoleRuch sprawdza czy dane pole jest puste  i czy dooko³a jest x ¿eby russzyc
int DobrePoleRuch(pole **plansza, int wiersz, int kolumna)
{
	if (plansza[wiersz][kolumna].pustePole == 1)
	{
		if ((wiersz - 1 >= 0 and plansza[wiersz - 1][kolumna].wybranePole == 1) or
			(wiersz + 1 <= 6 and plansza[wiersz + 1][kolumna].wybranePole == 1)or
			(kolumna - 1 >= 0 and plansza[wiersz][kolumna - 1].wybranePole == 1)or
			(kolumna +1 <= 6 and plansza[wiersz][kolumna + 1].wybranePole == 1))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

//znajdz wybranego X i przesuñ na wybrane przez siebie pole
void przesun(pole **plansza, int wiersz, int kolumna) {
	pole buff;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (plansza[i][j].wybranePole == 1)
			{
				plansza[i][j].wybranePole = 0; //zamiana pol
				buff = plansza[i][j];
				plansza[i][j] = plansza[wiersz][kolumna];
				plansza[wiersz][kolumna] = buff;
			}
		}
	}

}

//zamiana miejsca komputera i usuniecie pionka gracza
void przesunKomputerIZbij(pole **plansza,int wierszP, int kolumnaP, int wierszD, int kolumnaD, int wierszX, int kolumnaX)
{
	pole buff = plansza[wierszP][kolumnaP];
	plansza[wierszP][kolumnaP] = plansza[wierszD][kolumnaD];
	plansza[wierszD][kolumnaD] = buff;
	plansza[wierszX][kolumnaX].znak = 'p';
	plansza[wierszX][kolumnaX].pustePole = 1;

}

//zamienia miejsce komputera z docelowym
void przesunKomputer(pole **plansza, int wierszP, int kolumnaP, int wierszD, int kolumnaD) {
	pole buff = plansza[wierszP][kolumnaP];
	plansza[wierszP][kolumnaP] = plansza[wierszD][kolumnaD];
	plansza[wierszD][kolumnaD] = buff;
}

//sprawdza gdzie jest o, sprawdza czy mo¿e zbiæ X, 
int ruchKompa(pole **plansza, int & zbitePionki) {
	int wierszKomp, kolumnaKomp, losowa, licznik = 0;

	for (int i = 0; i < 7; i++) //gdzie jest nem o 
	{
		for (int j = 0; j < 7; j++)
		{
			if (plansza[i][j].czyJestKomputerem)
			{
				wierszKomp = i;
				kolumnaKomp = j;
			}
		}
	}

	//warunki sprawdzajace czy o bije X i jest wolne pole
	if (kolumnaKomp + 2 <= 6 and plansza[wierszKomp][kolumnaKomp + 1].znak == 'x' and plansza[wierszKomp][kolumnaKomp + 2].pustePole)
	{
		przesunKomputerIZbij(plansza,wierszKomp, kolumnaKomp, wierszKomp, kolumnaKomp + 2, wierszKomp, kolumnaKomp + 1);
		zbitePionki++;
		return 0;
	}
	else if (wierszKomp - 2 >= 0 and plansza[wierszKomp - 1][kolumnaKomp].znak == 'x' and plansza[wierszKomp - 2][kolumnaKomp].pustePole)
	{
		przesunKomputerIZbij(plansza, wierszKomp, kolumnaKomp, wierszKomp - 2, kolumnaKomp, wierszKomp - 1, kolumnaKomp);
		zbitePionki++;
		return 0;
	}
	else if (wierszKomp + 2 <= 6 and plansza[wierszKomp + 1][kolumnaKomp].znak == 'x' and plansza[wierszKomp + 2][kolumnaKomp].pustePole)
	{
		przesunKomputerIZbij(plansza, wierszKomp, kolumnaKomp, wierszKomp + 2, kolumnaKomp, wierszKomp + 1, kolumnaKomp);
		zbitePionki++;
		return 0;
	}
	else if (kolumnaKomp - 2 >= 0 and plansza[wierszKomp][kolumnaKomp - 1].znak == 'x' and plansza[wierszKomp][kolumnaKomp - 2].pustePole)
	{
		przesunKomputerIZbij(plansza, wierszKomp, kolumnaKomp, wierszKomp, kolumnaKomp - 2, wierszKomp, kolumnaKomp - 1);
		zbitePionki++;
		return 0;
	}
	while (licznik < 1000)//kierunek ruchu losowo
	{
		losowa = rand() % 4; //0-prawo,1-dó³,2-lewo, 3-góra
		if (losowa == 0 )
		{
			if (kolumnaKomp + 1 <= 6 and plansza[wierszKomp][kolumnaKomp + 1].pustePole)//sprawdza czy moze sie ruszyc
			{
				przesunKomputer(plansza, wierszKomp, kolumnaKomp, wierszKomp, kolumnaKomp + 1);
				return 0;
			}
		}
		else if (losowa == 1)
		{
			if (wierszKomp + 1 <= 6 and plansza[wierszKomp + 1][kolumnaKomp].pustePole)
			{
				przesunKomputer(plansza, wierszKomp, kolumnaKomp, wierszKomp + 1, kolumnaKomp);
				return 0;
			}
		}
		else if (losowa == 2)
		{
			if (kolumnaKomp - 1 >= 0 and plansza[wierszKomp][kolumnaKomp - 1].pustePole)
			{
				przesunKomputer(plansza, wierszKomp, kolumnaKomp, wierszKomp, kolumnaKomp - 1);
				return 0;
			}
		}
		else if (losowa == 3)
		{
			if (wierszKomp - 1 >= 0 and plansza[wierszKomp - 1][kolumnaKomp].pustePole)
			{
				przesunKomputer(plansza, wierszKomp, kolumnaKomp, wierszKomp - 1, kolumnaKomp);
				return 0;
			}
		}
		licznik++;
	}
	return 1;
}


int main() {
	srand(time(NULL));
	pole **plansza = new pole *[7];
	for (int i = 0; i < 7; i++)
	{
		plansza[i] = new pole[7];//siedem wskaznikow wskazuje na tablice pol
	}
	wypelnianie(plansza);
	wypisz(plansza);
	char wiersz, wierszD;

	int wierszL;
	int kolumna, kolumnaD;
	int poprawnosc;
	int zbitePionki = 0;
	int wygrana;

	do {  //game loop
		system("cls");

		wypisz(plansza);
		cout << "Ruch gracza" << endl;
		cout << "Podaj wiersz i kolumne pionka ktorym chcesz ruszyc, zbite pionki : " << zbitePionki << endl;
		cout << "Wiersz kolumna : ";
		cin >> wiersz;
		cin >> kolumna;
		if ((wiersz >= 'a' and wiersz <= 'z') or(wiersz>='A' and wiersz<='G'))
		{
			wiersz -= 32;

			if (wiersz < 'A' or wiersz > 'G' or kolumna < 0 or kolumna > 6)
			{
				poprawnosc = 0;
			}
			else
			{
				poprawnosc = DobrePole(plansza, 71 - wiersz, kolumna);
			}

			while (wiersz < 'A' or wiersz > 'G' or kolumna < 0 or kolumna > 6 or poprawnosc == 0)
			{
				cout << "Podaj  wiersz i kolumne jeszcze raz" << endl;
				cout << "Wiersz kolumna: ";
				cin >> wiersz;
				cin >> kolumna;
				if (wiersz >= 'a' and wiersz <= 'z')
				{
					wiersz -= 32;
				}
				poprawnosc = DobrePole(plansza, 71 - wiersz, kolumna);
			}
			wierszL = 71 - wiersz;
			plansza[wierszL][kolumna].wybranePole = 1; 
			cout << "dobre pole" << endl;

			cout << "Podaj  wiersz i kolumne, na ktora chesz jechac" << endl;
			cout << "Wiersz kolumna: ";
			cin >> wierszD;
			cin >> kolumnaD;
			if (wierszD >= 'a' and wierszD <= 'z')
			{
				wierszD -= 32;
			}
			if (wierszD < 'A' or wierszD > 'G' or kolumnaD < 0 or kolumnaD > 6)
			{
				poprawnosc = 0;
			}
			else      
			{
				poprawnosc = DobrePoleRuch(plansza, 71 - wierszD, kolumnaD); 
			}
			while (wierszD < 'A' or wierszD > 'G' or kolumnaD < 0 or kolumnaD > 6 or poprawnosc == 0)
			{
				cout << "Podaj  wiersz i kolumne jeszcze raz " << endl;
				cout << "Wiersz kolumna: ";
				cin >> wierszD;
				cin >> kolumnaD;
				if (wierszD >= 'a' and wierszD <= 'z')
				{
					wierszD -= 32;
				}
				poprawnosc = DobrePoleRuch(plansza, 71 - wierszD, kolumnaD);
			}
			przesun(plansza, 71 - wierszD, kolumnaD);
			system("cls");
			wypisz(plansza);
			cout << "Ruch sztucznej inteligencji" << endl;
			Sleep(1500);
			wygrana = ruchKompa(plansza, zbitePionki);
			if (wygrana)
			{
				cout << "Wygrales!!!!!!!!!!!!" << endl;
				break;
			}
			else if (zbitePionki >= 8)
			{
				cout << "Przegrana :( !!!" << endl;
				break;
			}
		}
		else
		{
			cout << "hej";
		}
	} while (true);
	system("pause");
	return 0;
}
