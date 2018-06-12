#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

enum gender
{
	mezczyzna,
	kobieta
};

enum position
{
	prezes,
	kierownik,
	pracownik,
	stazysta,
	praktykant
};

string int_to_string(int n)
{
    string s;
    char c;
    if(n == 0)
    {
        c = n+48;
        s += c;
    }
    while(n > 0)
    {
        c = (n%10+48);
        s += c;
        n/=10;
    }
    reverse(s.begin(), s.end());
    return s;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Person
{
protected:
	string name;
	string surname;
	gender sex;
	int age;
public:
	Person(string, string, gender, int);
	string show();
	//friend ostream& operator << (ostream& out, const Person &);
};

Person :: Person(string na, string su, gender se, int ag)
{
	name = na;
	surname = su;
	sex = se;
	age = ag;
}

string Person :: show()
{
	string o ;
	o += name + " " + surname + " ";
	if(sex == 0) o += "mezczyzna";
    else o += "kobieta";
    o += " ";
    o += int_to_string(age);
    return o;
}
ostream& operator << (ostream & out, Person& per)
{
	out<<per.show();
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Work
{
protected:
	string job_title;
	position job;
	int salary;
	int income;

public:
	Work(string, position, int, int);
	string show();
    int get_income();
	int get_salary();
	void change_job_title(string);
	void change_position();
	void change_income(int);
	void change_salary(int);
	void promotion(string, int, int);

	friend ostream& operator << (ostream& out, Work& );
};

Work :: Work(string title, position jo, int sal, int inc)
{
	job_title = title;
	job = jo;
	salary = sal;
	income = inc;
}

int Work :: get_income()
{
    return income;
}

int Work :: get_salary()
{
    return salary;
}

void Work :: change_job_title(string tit)
{
    job_title = tit;
}

void Work :: change_position()
{
    switch (job)
    {
    	case 0:
    	break;

    	case 1:
    	break;

    	case 2:
    	job = kierownik;
    	break;

    	case 3:
    	job = pracownik;
    	break;

    	case 4:
    	job = stazysta;
    	break;
    }
}

void Work :: change_salary(int sal)
{
    salary = sal;
}

void Work :: change_income(int inc)
{
    income = inc;
}

void Work :: promotion(string tit, int sal, int inc)
{
    change_job_title(tit);
    change_position();
    change_salary(sal);
    change_income(inc);
}

string Work :: show()
{
    string o;
    o += job_title + " ";
    switch (job)
    {
    	case 0:
    	o += "prezes";
    	break;

    	case 1:
    	o += "kierownik";
    	break;

    	case 2:
    	o += "pracownik";
    	break;

    	case 3:
    	o += "stazysta";
    	break;

    	case 4:
    	o += "praktykant";
    	break;
    }

    o += " ";

    o += int_to_string(salary);
    o += " ";
    o += int_to_string(income);

    return o;
}


ostream& operator << (ostream & out, Work & wor)
{
	out<<wor.show();

    return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Employee: public Person, public Work
{
public:
	Employee(string , string , gender , int , string , position , int , int );
	string show();

	friend ostream& operator << (ostream& out, Employee& );
    friend bool operator ==( const Employee &, const Employee & );
    friend bool operator !=( const Employee &, const Employee & );
};

Employee :: Employee(string na, string su, gender se, int ag, string title, position jo, int sal, int inc)
:Person(na, su, se, ag), Work(title, jo, sal, inc)
{

}

string Employee :: show()
{
    string o;

    o += Person :: show() + " " + Work :: show();

    return o;
}

bool operator ==( const Employee& l , const Employee& r )
{
    if(l.name == r.name && l.surname == r.surname && l.age == r.age && l.sex == r.sex && l.job_title == r.job_title && l.job == r.job && l.salary == r.salary && l.income == r.income)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator !=( const Employee& l , const Employee& r )
{
    if(l.name == r.name && l.surname == r.surname && l.age == r.age && l.sex == r.sex && l.job_title == r.job_title && l.job == r.job && l.salary == r.salary && l.income == r.income)
    {
        return false;
    }
    else
    {
        return true;
    }
}

ostream& operator << (ostream & out, Employee & emp)
{
	out<<emp.show();

    return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Branch
{
protected:
	string branch_name;
    vector <Employee> workers;
public:
	Branch(string);
	void add_worker(Employee);
	void fire_worker(Employee);
	void promote_worker(Employee, string, int, int);
	//void move_worker(Employee);
	friend ostream& operator<< (ostream& , Branch& );
};

Branch :: Branch(string na)
{
	branch_name = na;
}

void Branch :: add_worker(Employee emp)
{
    workers.push_back(emp);
}

void Branch :: fire_worker(Employee emp)
{
    for(int i = 0; i < workers.size(); i++)
    {
        if(emp == workers[i])
        {
            workers.erase(workers.begin() + i);
            break;
        }
    }
}

void Branch :: promote_worker(Employee emp, string job_title, int salary, int income)
{
    for(int i = 0; i < workers.size(); i++)
    {
        if(emp == workers[i])
        {
            workers[i].promotion(job_title, salary, income);
            break;
        }
    }
}

ostream& operator<< (ostream& out, Branch& bra)
{
    out<<bra.branch_name<<"\n";
    for(int i = 0; i < bra.workers.size(); i++)
    {
        out<<i+1<<". "<<bra.workers[i]<<"\n";
    }
    return out;
}
