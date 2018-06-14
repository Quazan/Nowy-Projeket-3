#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int leap_year(int y)
{
    if((y%4 == 0 && y%100 != 0) || y%400 == 0) return 1;
    else return 0;
}

int days_in_month(int m, int y)
{
    int a = 31;
    int b = 30;

    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
    {
        return a;
    }
    else if(m == 4 || m == 6 || m == 9 || m == 11)
    {
        return b;
    }
    else if(m == 2)
    {
        if(leap_year(y))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
}
class Time
{
public:
    virtual string show() = 0;
};


class Date :public Time
{
protected:
    int day;
    int month;
    int year;

public:

    Date(int, int, int);
    string get_date();
    int get_day();
    int get_month();
    int get_year();
    void next_day();
    void next_week();
    void change(int, int, int);
    virtual string show()
    {
        return get_date();
    }
    friend ostream& operator<< (ostream& , const Date& );
};

Date :: Date(int d = 1, int m = 1, int y = 2018)
{
    day = d;
    month = m;
    year = y;
}

int Date :: get_day()
{
    return day;
}

int Date :: get_month()
{
    return month;
}

int Date :: get_year()
{
    return year;
}

void Date :: next_day()
{
    day++;

    if(day > days_in_month(month, year))
    {
        day = 1;
        month++;
        if(month > 12)
        {
            month = 1;
            year++;
        }
    }
}

void Date :: next_week()
{
    for(int i = 1; i <= 7; i++)
    {
        next_day();
    }
}

void Date :: change(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

string Date :: get_date()
{
    string o;

    if(day >= 10) o += to_string(day);
    else o += "0" + to_string(day);
    o += ".";
    if(month >= 10) o += to_string(month);
    else o += "0" + to_string(month);
    o += "." + to_string(year);

        return o;
}

ostream& operator << (ostream& out, const Date & da)
{
    int day = da.day;
    int month = da.month;
    int year = da.year;

    if(day >= 10) out<<day;
    else out<<"0"<<day;
    out<<".";
    if(month >= 10) out<<month;
    else out<<"0"<<month;
    out<<"."<<year;

    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
