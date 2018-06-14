#include "people.h"
#include "Calendar.h"
//#include "branch.h"
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

Company firma("");
Date data(1, 1, 2018);

void wczytaj_firme();
void menu();
void system();
void system_dzial(int x);
void system_pracownik(int x, int y);
void lista_dzialow();
void wczytaj_pracownika(int x);
int sprawdz(int a, int b, int z);

int main()
{
    //Company firma();
/*
	//gender se = male;
	Employee a("Jan", "Kowalski", mezczyzna, 32, "IT", pracownik, 3200, 4000);
	Employee x("Jana", "Kowalski", mezczyzna, 32, "IT", pracownik, 3200, 4000);
	//if(a!=x) cout<<"TAK CHUJU";
		//Person a("Jan", "Kowalski", mezczyzna, 32);
	//class Date d(28,12,2018);
    //a.change_position();
    //a.change_job_title("PR");
    //a.change_salary(4000);
    //a.change_income(5000);
	Branch b("Szlachta nie pracuje");
	b.add_worker(a);
    b.add_worker(x);
	//b.fire_worker(x);
	b.give_rise(a, 5000);
	//cout<<d<<"\n"<<a<<"\n"<<a.get_income() <<" "<<a.get_salary();
	//cout<<b.get_income() <<" "<<b.get_outflow()<<"\n"<<b<<"\n";

	Company xxx("Tristram", 100);
    //Branch c;
	xxx.add_branch(b);
	//xxx.add_worker(1, x);
    //c = xxx.return_branch(1);
	cout<<xxx;
    //Branch c;
    //c.change(b);
    //x.change(a);
    //cout<<x;
*/

    //wczytaj_firme();
    menu();
    //cout<<data;
}

void menu()
{
    string nazwa_pliku;
    //int z = 1;

    cout<<"\t"<<"Podaj nazwe pliku"<<"\n";
    cin>>nazwa_pliku;
    wczytaj_firme(/*nazwa_pliku*/);
    system();

    /*while(z != 0)
    {
        printf("[1] Wczytaj firme z pliku\n");
        printf("\n\n\n");
        printf("[0] Zakoncz\n");
        cin>>z;
        z = sprawdz(0, 1, z);
        /*while(z < 0 || z > 1)
        {
            printf("\tWpisz poprawny numer operacji");
            cin>>z;
        }*/
    /*
        switch(z)
        {
        case 1:
            cout<<"\t"<<"Podaj nazwe pliku"<<"\n";
            cin>>nazwa_pliku;
            wczytaj_firme(/*nazwa_pliku);
            system();
            break;

        case 0:
            break;
        }
    }*/
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
        printf("\n");
        printf("\t[4] Nastepny dzien\n");
        printf("\n\n");
        printf("\t[0] Zakoncz\n\n");
        cin>>z;
        z = sprawdz(0, 7, z);
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
            q = sprawdz(1, firma.get_size(), q);
            system_dzial(q);
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
            y = sprawdz(1, br.get_size(), y);
            system_pracownik(x, y);
            break;

        case 2:
            wczytaj_pracownika(x);
            break;
        }

        cout<<"\n\n";
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
            break;
        }

        printf("\n\n");
    }
}

void lista_dzialow()
{
    Branch br("");
    cout<<"LISTA DZIALOW:\n";
    for(int i = 1; i <= firma.get_size(); i++)
    {
        br = firma.return_branch(i);
        cout<<"\t"<<i<<". "<<br.get_name()<<"\n";
    }
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

void wczytaj_firme()
{
    string nazwa_pliku;
	string nazwa_firmy;
	string nazwa_oddzialu;
	gender gend;
	position pos;
	int liczba_pracownikow;
	string imie, nazwisko, plec, stanowisko, pozycja;
	int wiek, wyplata, przychod;
	int pieniadze_firmy;
	string s;
	int a, b, c;
	int liczba_oddzialow;
	char z;

	std::ifstream plik;
    plik.open("1.txt" );
    plik>>a>>z>>b>>z>>c;

	//Date date(a, b, c);
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

