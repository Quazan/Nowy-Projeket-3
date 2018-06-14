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
class Area
{
public:
    virtual int get_size() = 0;
    virtual int get_income() = 0;
    virtual int get_outflow() = 0;
    //virtual string get_name() = 0;
};

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
	void promotion(string, int);
	void rise(int);

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

void Work :: promotion(string tit, int sal)
{
    change_job_title(tit);
    change_position();
    change_income(income + (sal-salary)/3*4);
    change_salary(sal);
}

void Work :: rise(int ri)
{
    change_income(income+(ri-salary)/3*4);
    change_salary(ri);
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
	void change(Employee);

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
void Employee :: change(Employee emp)
{
    name = emp.name;
	surname = emp.surname;
	sex = emp.sex;
	age = emp.age;
    job_title = emp.job_title;
	job = emp.job;
	salary = emp.salary;
	income = emp.income;
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
class Branch :public Area
{
protected:
	string branch_name;
    vector <Employee> workers;
public:
    Branch();
	Branch(string);
	void add_worker(Employee);
	void fire_worker(int);
	void promote_worker(int , string, int);
	void give_rise(int, int);
	void change(Branch);
	virtual int get_income()
	{
        int inc = 0;
        for(int i = 0; i < workers.size(); i++)
        {
            inc += workers[i].get_income();
        }

        return inc;
	}
	virtual int get_outflow()
	{
	    int ou = 0;
        for(int i = 0; i < workers.size(); i++)
        {
            ou += workers[i].get_salary();
        }

        return ou;
	}
	virtual int get_size()
	{
	    return workers.size();
	}
    string get_name();
	friend ostream& operator<< (ostream& , Branch& );
};

Branch :: Branch()
{
    branch_name = "";
}

Branch :: Branch(string na)
{
	branch_name = na;
}

void Branch :: add_worker(Employee emp)
{
    workers.push_back(emp);
}

void Branch :: fire_worker(int n)
{
    workers.erase(workers.begin() + (n-1));
}

void Branch :: promote_worker(int n, string job_title, int salary)
{
    workers[n-1].promotion(job_title, salary);
}

void Branch :: give_rise(int n, int ri)
{
    workers[n-1].rise(ri);
}

/*int Branch :: get_income()
{
    int inc = 0;
    for(int i = 0; i < workers.size(); i++)
    {
        inc += workers[i].get_income();
    }

    return inc;
}

int Branch :: get_outflow()
{
    int ou = 0;
    for(int i = 0; i < workers.size(); i++)
    {
        ou += workers[i].get_salary();
    }

    return ou;
}

int Branch :: get_size()
{
    return workers.size();
}
*/
string Branch :: get_name()
{
    return branch_name;
}
void Branch :: change(Branch br)
{
    branch_name = br.branch_name;
    workers.clear();
    for(int i = 0; i < br.workers.size(); i++)
    {
        workers.push_back(br.workers[i]);
    }
}

ostream& operator<< (ostream& out, Branch& bra)
{
    out<<bra.branch_name<<"\n\t   "<<bra.get_size()<<"\n";
    for(int i = 0; i < bra.workers.size(); i++)
    {
        out<<"\t\t"<<i+1<<". "<<bra.workers[i]<<"\n";
    }
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Company :public Area
{
protected:
    string name;
    int money;
    int income;
    int outflow;
    vector<Branch> branches;

    void update_income();
    void update_outflow();
    void update_money();

public:
    Company();
    Company(string , int);
    void add_branch(Branch);
    void add_worker(int, Employee);
    void change(string, int);
    void promote_worker(int, int, string, int);
    void fire_worker(int, int);
    void rise_worker(int, int, int);
    int show_money();
    virtual int get_income()
    {
        update_income();
        return income;
    }
    virtual int get_outflow()
    {
        update_outflow();
        return outflow;
    }
    virtual int get_size()
    {
        return branches.size();
    }
    Branch return_branch(int);
    string show_report();
    int get_workers_size();
    void end_of_month();
    friend ostream& operator << (ostream& out, Company& );
};

Company :: Company()
{
    name = "";
    money = 0;
    income = 0;
    outflow = 0;
}
Company :: Company(string n = "Firma", int m = 100000)
{
    name = n;
    money = m;
    income = 0;
    outflow = 0;
}

void Company :: update_income()
{
    int in = 0;

    for(int i = 0; i < branches.size(); i++)
    {
        in += branches[i].get_income();
    }

    income = in;
}

void Company :: update_outflow()
{
    int ou = 0;
    for(int i = 0; i < branches.size(); i++)
    {
        ou += branches[i].get_outflow();
    }

    outflow = ou;
}

void Company :: update_money()
{
    money += income - outflow;
}

void Company :: add_branch(Branch br)
{
    branches.push_back(br);
}

void Company :: add_worker(int b, Employee emp)
{
    branches[b-1].add_worker(emp);
}

void Company :: change(string na, int mon)
{
    name = na;
    money = mon;
    income = 0;
    outflow = 0;
}

void Company :: promote_worker(int b, int e, string tit, int r)
{
    branches[b-1].promote_worker(e, tit, r);
}

void Company :: fire_worker(int b, int e)
{
    branches[b-1].fire_worker(e);
}

void Company :: rise_worker(int b, int e, int r)
{
    branches[b-1].give_rise(e, r);
}

int Company :: show_money()
{
    update_money();
    return money;
}

/*int Company :: show_income()
{
    update_income();
    return income;
}

int Company :: show_outflow()
{
    update_outflow();
    return outflow;
}
*/
void Company :: end_of_month()
{
    update_income();
    update_outflow();
    update_money();
}

/*int Company :: get_size()
{
    return branches.size();
}
*/
int Company :: get_workers_size()
{
    int sum = 0;

    for(int i = 0; i < branches.size(); i++)
    {
        sum += branches[i].get_size();
    }

    return sum;
}

Branch Company :: return_branch(int b)
{
    return branches[b-1];
}

ostream& operator << (ostream& out, Company& com)
{
    out<<com.name<<"\n"<<com.show_money()<<"\n"<<com.get_size()<<"\n";
    for(int i = 0; i < com.get_size(); i++)
    {

        out<<"\t"<<i+1<<". "<<com.branches[i];
    }
    return out;
}
