#include "people.h"
#include "Calendar.h"
//#include "branch.h"
#include <bits/stdc++.h>
using namespace std;



int main()
{
	//gender se = male;
	Employee a("Jan", "Kowalski", mezczyzna, 32, "IT", pracownik, 3200, 4000);
	Employee x("Jana", "Kowalski", mezczyzna, 32, "IT", pracownik, 3200, 4000);
	//if(a!=x) cout<<"TAK CHUJU";
		//Person a("Jan", "Kowalski", mezczyzna, 32);
	class Date d(28,12,2018);
    //a.change_position();
    //a.change_job_title("PR");
    //a.change_salary(4000);
    //a.change_income(5000);
	Branch b("Szlachta nie pracuje");
	b.add_worker(a);
	b.add_worker(x);
	//b.fire_worker(x);
	b.promote_worker(a, "PR", 4000, 5000);
	//cout<<d<<"\n"<<a<<"\n"<<a.get_income() <<" "<<a.get_salary();
	cout<<b;
}
