#include "Company.h"
#include "Calendar.h"
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

Company firma("");
Date data(1, 1, 2018);

Time *ti;
Area *obszar;
void wczytaj_firme(string nazwa);
void menu();
void system();
void system_dzial(int x);
void system_pracownik(int x, int y);
void lista_dzialow();
void wypisz_raport();
void wczytaj_pracownika(int x);
void zapisz_raport();
void zapisz_firme(string nazwa);
int sprawdz(int a, int b, int z);

int main()
{
    menu();
}

void menu()
{
    string nazwa_pliku;

    cout<<"\t"<<"Podaj nazwe pliku z firma"<<"\n";
    cin>>nazwa_pliku;
    try
    {
        wczytaj_firme(nazwa_pliku);
    }
    catch(string w)
    {
        cout<<w<<"\n";
        menu();
        return;
    }
    system();
}

void system()
{
    int z = 1;

    while(z != 0)
    {
        cout<<data<<"\n\n";
        printf("SYSTEM ZARZADZANIA FIRMA\n\n");
        printf("\t[1] Wyswietl liste dzialow\n");
        printf("\t[2] Wybierz dzial\n");
        printf("\t[3] Wyswietl stan firmy\n");
        printf("\t[4] Zapisz firme\n");
        printf("\n");
        printf("\t[5] Nastepny dzien\n");
        printf("\n\n");
        printf("\t[0] Zakoncz\n\n");
        cin>>z;
        z = sprawdz(0, 5, z);
        cout<<"\n\n";

        switch(z)
        {
        case 1:
            lista_dzialow();
            break;

        case 2:
            int q;
            lista_dzialow();
            printf("\n Wybierz dzial poprzez wpisanie jego numeru do konsoli\n");
            cin>>q;
            obszar = &firma;
            q = sprawdz(1, obszar -> get_size(), q);
            system_dzial(q);
            break;

        case 3:
            int w;
            printf("STAN FIRMY ");
            cout<<data<<"\n\n";
            wypisz_raport();

            printf("\n\n");
            printf("Czy chcesz zapisac stan firmy? [1/0]\n");

            cin>>w;
            w = sprawdz(0, 1, w);

            if(w == 1)
            {
                zapisz_raport();
            }
            break;

        case 4:
            {
                string s;
                printf("Podaj nazwe pliku do zapisu\n");
                cin>>s;
                zapisz_firme(s);
                break;
            }

        case 5:
            data.next_day();
            if(data.get_day() == 10)
            {
                int w;
                printf("RAPORT NA KONIEC MIESIACA\n\n");
                firma.end_of_month();
                wypisz_raport();

                printf("\n\n");
                printf("Czy chcesz zapisac stan firmy? [1/0]\n");

                cin>>w;
                w = sprawdz(0, 1, w);

                if(w == 1)
                {
                zapisz_raport();
                }

            }
            break;

        case 0:
            printf("Czy chesz zapisac firme przed wyjsciem? [1/0]\n");
            int e;
            cin>>e;
            e = sprawdz(0, 1, e);

            if(e == 1)
            {
                string s;
                printf("Podaj nazwe pliku do zapisu\n");
                cin>>s;
                zapisz_firme(s);
            }

            break;
        }
        cout<<"\n\n";
    }
}

void system_dzial(int x)
{
    int z = 1;
    int y = 0;
    Branch br("");
    br = firma.return_branch(x);

    while(z != 0)
    {
        printf("SYSTEM ZARZADZANIA DZIALEM\n\n");
        printf("\t[1] Wybierz pracownika\n");
        printf("\t[2] Dodaj pracownika\n");
        printf("\t[3] Wyswietl stan dzialu\n");
        printf("\n\n");
        printf("\t[0] Wroc\n\n");

        cin>>z;
        z = sprawdz(0, 3, z);
        cout<<"\n\n";

        switch(z)
        {
        case 1:
            br = firma.return_branch(x);

            cout<<br<<"\n";
            printf("Wybierz pracownika poprzez wpisanie jego numeru do konsoli\n");
            cin>>y;
            obszar = &br;
            y = sprawdz(1, obszar -> get_size(), y);

            system_pracownik(x, y);
            break;

        case 2:
            wczytaj_pracownika(x);
            break;
        case 3:
            obszar = &br;
            printf("Ilosc pracownikow\t%d\n", obszar -> get_size());
            printf("Przychody:\t\t%d zl\n", obszar -> get_income());
            printf("Straty:\t\t\t%d zl\n", obszar -> get_outflow());
            printf("Bilans:\t\t\t%d zl\n", obszar -> get_income()- obszar -> get_outflow());
            printf("\n");
            break;
        }

        cout<<"\n\n";
        br = firma.return_branch(x);
    }
}

void system_pracownik(int x, int y)
{
    int z = 1;
    string pozy;
    int wyp;

    while(z != 0)
    {
        printf("SYSTEM ZARZADZANIA PRACOWNIKIEM\n\n");
        printf("\t[1] Awansuj\n");
        printf("\t[2] Daj podwyzke\n");
        printf("\t[3] Zwolnij\n");
        printf("\n\n");
        printf("\t[0] Wroc\n\n");

        cin>>z;
        z = sprawdz(0, 3, z);
        printf("\n\n");

        switch(z)
        {
        case 1:
            printf("Podaj wysokosc wyplaty\n");
            cin>>wyp;
            printf("Podaj nowe stanowisko\n");
            getline(cin, pozy);
            getline(cin, pozy);

            firma.promote_worker(x, y, pozy, wyp);
            break;

        case 2:
            printf("Podaj wysokosc wyplaty\n");
            cin>>wyp;

            firma.rise_worker(x, y, wyp);
            break;

        case 3:
            firma.fire_worker(x, y);
            z = 0;
            break;
        }

        printf("\n\n");
    }
}

void lista_dzialow()
{
    Branch br("");

    cout<<"LISTA DZIALOW:\n";
    obszar = &firma;
    for(int i = 1; i <= obszar -> get_size(); i++)
    {
        br = firma.return_branch(i);

        cout<<"\t"<<i<<". "<<br.get_name()<<"\n";
    }
}

void wypisz_raport()
{
    obszar = &firma;
    printf("Stan konta firmy:\t%d\n", firma.show_money());
    printf("Miesieczne przychody:\t%d\n", obszar -> get_income());
    printf("Miesieczne wydatki:\t%d\n", obszar -> get_outflow());
    printf("Bilans:\t\t\t%d\n", obszar -> get_income()- obszar -> get_outflow());
    printf("Liczba dzialow: \t%d\n", obszar -> get_size());
    printf("Liczba pracownikow:\t%d\n", firma.get_workers_size());
}

void zapisz_raport()
{
    string d;
    ti = &data;
    d = ti -> show();
    std::fstream plik;
    obszar = &firma;
    plik.open("Raport " + d + ".txt", std::ios::out);
    plik <<"STAN FIRMY\n\n";
    plik<<"Stan konta firmy:\t"<<firma.show_money()<<"\n";
    plik<<"Miesieczne przychody:\t"<<obszar -> get_income()<<"\n";
    plik<<"Miesieczne wydatki:\t"<<obszar -> get_outflow()<<"\n";
    plik<<"Bilans:\t\t\t"<<obszar -> get_income()- obszar -> get_outflow()<<"\n";
    plik<<"Liczba dzialow: \t"<<obszar -> get_size()<<"\n";
    plik<<"Liczba pracownikow:\t"<<firma.get_workers_size()<<"\n";
    plik.close();
}

void zapisz_firme(string nazwa_pliku)
{
    std::fstream plik;
    plik.open(nazwa_pliku + ".txt", std::ios::out);
    plik<<data<<"\n";
    plik<<firma;
    plik.close();
}

int sprawdz(int a, int b, int z)
{
    while(z < a || z > b)
    {
        printf("\tWpisz poprawny numer operacji\n");
        cin>>z;
    }

    return z;
}

void wczytaj_pracownika(int x)
{
    string n, s, g, st, po;
    int a, wy, prz;
    gender gend;
    position pos;

    printf("Wpisz informacje o pracowniku\n");
    printf("Imie Nazwisko plec wiek stanowisko pozycje wyplate przychod\n");

    cin>>s>>n>>g>>a>>st>>po>>wy>>prz;

    if(g[0] == 'm')
    {
        gend = mezczyzna;
    }
    else
    {
        gend = kobieta;
    }

    if(po[0] == 'k')
    {
        pos = kierownik;
    }
    else if( po[0] == 's')
    {
        pos = stazysta;
    }
    else
    {
        if(po[2] == 'e')
        {
            pos = prezes;
        }
        else if(po[3] == 'c')
        {
            pos = pracownik;
        }
        else
        {
            pos = praktykant;
        }
    }
    Employee emp(n, s, gend, a, st, pos, wy, prz);
    firma.add_worker(x, emp);
}

void wczytaj_firme(string nazwa_pliku)
{
	string nazwa_firmy;
	string nazwa_oddzialu;
	string imie, nazwisko, plec, stanowisko, pozycja;
    string s;
    char z;
	gender gend;
	position pos;
	int liczba_pracownikow;
	int wiek, wyplata, przychod;
	int pieniadze_firmy;
	int a, b, c;
	int liczba_oddzialow;

	std::ifstream plik;
    plik.open(nazwa_pliku + ".txt" );

    if( plik.good() != true )
    {
        string wyjatek = "Brak pliku o podanej nazwie";
        throw wyjatek;
    }

    plik>>a>>z>>b>>z>>c;

    data.change(a, b, c);

	getline(plik, s);
	getline(plik, nazwa_firmy);
	plik>>pieniadze_firmy;
	getline(plik, s);

    firma.change(nazwa_firmy, pieniadze_firmy);

	plik>>liczba_oddzialow;

	for(int i = 1; i <= liczba_oddzialow; i++)
    {
        plik>>a>>z;
        getline(plik, nazwa_oddzialu);

        Branch odzial(nazwa_oddzialu);

        plik>>liczba_pracownikow;

        for(int i = 1; i <= liczba_pracownikow; i++)
        {
            plik>>a>>z;
            plik>>imie>>nazwisko>>plec>>wiek>>stanowisko>>pozycja>>wyplata>>przychod;
            getline(plik, s);

            if(plec[0] == 'm')
            {
                gend = mezczyzna;
            }
            else
            {
                gend = kobieta;
            }

            if(pozycja[0] == 'k')
            {
                pos = kierownik;
            }
            else if( pozycja[0] == 's')
            {
                pos = stazysta;
            }
            else
            {
                if(pozycja[2] == 'e')
                {
                    pos = prezes;
                }
                else if(pozycja[3] == 'c')
                {
                    pos = pracownik;
                }
                else
                {
                    pos = praktykant;
                }
            }

            Employee prac(imie, nazwisko, gend, wiek, stanowisko, pos, wyplata, przychod);
            odzial.add_worker(prac);
        }
        firma.add_branch(odzial);
    }
	plik.close();
}

