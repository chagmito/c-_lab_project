/***********************************************************************
Matr.-Nr:                     ...3116945
Nachname/Surname:             ...GHOSH
Vorname/Given name:           ...MITO CHANDRA
Uni-Email:                    ...mito.ghosh@stud.uni-due.de
Studiengang/Course of studis: ...ISE(CE)
***********************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int COLUMN_WIDTH = 35;
const int annualAverageConsumptionPerPerson = 200;
const int annualAverageConsumptionPerPersonWithElectricWaterHeating = 550;
const int annualAverageConsumptionPerSquareMetre = 9;
const int annualAverageConsumptionPerElectricalDevice = 200;
const int numberOfDaysInYear = 10;
const int quarterIntervalsHourDays = 12;

enum Use
{
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    once,
    daily,
    mo_fr,
    sa_su,
};

struct year
{
    int yearValue;
    Use firstDayOfWeek;
    string unit;
    float values[numberOfDaysInYear][quarterIntervalsHourDays];
};

ostream& operator<<(std::ostream& os, const Use& use)
{
    if (use == Use::monday)
    {
        os << "Monday";
    }
    else if (use == Use::tuesday)
    {
        os << "Tuesday";
    }
    else if (use == Use::wednesday)
    {
        os << "Wednesday";
    }
    else if (use == Use::thursday)
    {
        os << "Thursday";
    }
    else if (use == Use::friday)
    {
        os << "Friday";
    }
    else if (use == Use::saturday)
    {
        os << "Saturday";
    }
    else if (use == Use::sunday)
    {
        os << "Sunday";
    }
    else if (use == Use::once)
    {
        os << "once";
    }
    else if (use == Use::daily)
    {
        os << "daily";
    }
    else if (use == Use::mo_fr)
    {
        os << "Monday to Friday";
    }
    else if (use == Use::sa_su)
    {
        os << "Saturday and Sunday";
    }
    else
    {
        os << "Unknown";
    }
    return os;
}

Use& operator++(Use& use)
{
    if (use == Use::monday) use =  Use::tuesday;
    else if (use == Use::tuesday) use = Use::wednesday;
    else if (use == Use::wednesday) use = Use::thursday;
    else if (use == Use::thursday) use = Use::friday;
    else if (use == Use::friday) use = Use::saturday;
    else if (use == Use::saturday) use = Use::sunday;
    else if (use == Use::sunday) use = Use::monday;
    else if (use == Use::once) use = Use::once;
    else if (use == Use::daily) use = Use::daily;
    else if (use == Use::mo_fr) use = Use::mo_fr;
    else if (use == Use::sa_su) use = Use::sa_su;

    return use;
}

void input_use(string message, Use& use)
{
    cout<<message<<endl;
    cout<<"Monday (0)"<<endl;
    cout<<"Tuesday (1)"<<endl;
    cout<<"Wednesday (2)"<<endl;
    cout<<"Thursday (3)"<<endl;
    cout<<"Friday (4)"<<endl;
    cout<<"Saturday (5)"<<endl;
    cout<<"Sunday (6)"<<endl;
    cout<< "daily (d)" <<endl;
    cout<<"mo_fr (m)"<<endl;
    cout<<"once (o)"<<endl;
    cout<<"sa_su (s)"<<endl;
    //cout<<"weekly (w)? "<<endl;
    char useType;
    cin >> useType;
    if(useType == '0') use = monday;
    else if(useType == '1') use = tuesday;
    else if(useType == '2') use = wednesday;
    else if(useType == '3') use = thursday;
    else if(useType == '4') use = friday;
    else if(useType == '5') use = saturday;
    else if(useType == '6') use = sunday;
    else if(useType == 'd') use = daily;
    else if(useType == 'm') use = mo_fr;
    else if(useType == 'o')
    {
        char day;
        cout<<"on which day? ";
        cin >> day;
        if(day == '0') use = monday;
        else if(day == '1') use = tuesday;
        else if(day == '2') use = wednesday;
        else if(day == '3') use = thursday;
        else if(day == '4') use = friday;
        else if(day == '5') use = saturday;
        else if(day == '6') use = sunday;
    }
    else if(useType == 's') use = sa_su;
}

inline year& zeros(year& year)
{
    for(int i = 0; i < numberOfDaysInYear; i++)
    {
        for(int j= 0; j < quarterIntervalsHourDays; j++)
        {
            year.values[i][j] = 0.0f;
        }
    }
    return year;
}

inline year& ones(year& Year)
{
    for(int i = 0; i < numberOfDaysInYear; i++)
    {
        for(int j= 0; j < quarterIntervalsHourDays; j++)
        {
            Year.values[i][j] = 1.0f;
        }
    }
    return Year;
}

inline int time(int h, int m)
{
    return h * 60 + m;
}

std::ostream& operator<<(ostream& os, year& Year)
{
    os <<"Year: "<< Year.yearValue <<" (unit: "<< Year.unit << ")" << endl;
    int day = 0;
    Use CurDay = Year.firstDayOfWeek;

    for(int i = 0; i < numberOfDaysInYear; i++)
    {
        os << "Day: " << day << ": " << CurDay << endl;
        for(int h = 0; h < 3; h++)
        {
            cout << h <<":00\t";
            for(int m = 0; m < 60; m += 15)
            {
                int minOfDay = time(h, m);
                os << std::fixed << setprecision(2)<< float(Year.values[i][minOfDay / 15]) <<"\t";

            }
            cout<<endl;
        }
        cout<<endl;
        day++;
        ++CurDay;
    }
    return os;
}

year operator+(year& year1, year& year2)
{
    if(year1.yearValue != year2.yearValue || year1.firstDayOfWeek != year2.firstDayOfWeek || year1.unit != year2.unit)
    {
        return year1;
    }
    year newYear;
    newYear.yearValue = year1.yearValue;
    newYear.unit = year1.unit;
    newYear.firstDayOfWeek = year1.firstDayOfWeek;
    for(int i = 0; i < numberOfDaysInYear; i++)
    {
        for(int j= 0; j < quarterIntervalsHourDays; j++)
        {
            newYear.values[i][j] = year1.values[i][j] + year2.values[i][j];
        }
    }
    return newYear;

}

year operator-(year& year1, year& year2)
{
    if(year1.yearValue != year2.yearValue || year1.firstDayOfWeek != year2.firstDayOfWeek || year1.unit != year2.unit)
    {
        return year1;
    }
    year newYear;
    newYear.yearValue = year1.yearValue;
    newYear.unit = year1.unit;
    newYear.firstDayOfWeek = year1.firstDayOfWeek;
    for(int i = 0; i < numberOfDaysInYear; i++)
    {
        for(int j= 0; j < quarterIntervalsHourDays; j++)
        {
            newYear.values[i][j] = year1.values[i][j] - year2.values[i][j];
        }
    }
    return newYear;
}

year operator*(float multiply, year& year2)
{
    year newYear;
    newYear.yearValue = year2.yearValue;
    newYear.unit = year2.unit;
    newYear.firstDayOfWeek = year2.firstDayOfWeek;
    for(int i = 0; i < numberOfDaysInYear; i++)
    {
        for(int j= 0; j < quarterIntervalsHourDays; j++)
        {
            newYear.values[i][j] = year2.values[i][j] * multiply;
        }
    }
    return newYear;
}

void set_unit(year& Year, string unit)
{
    Year.unit = unit;
}
void add_consumption(year& Year, int day, int fromMin, int toMin, float wattage)
{
    for (int i = fromMin; i < toMin; i++)
    {
        Year.values[day][i/15] += wattage/60.0;
    }
}


void add_consumption(year& Year, Use usage, int fromMinute, int toMinute, float wattage)
{
    int day = 0;
    if(usage == Use::monday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 0)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::tuesday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 1)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::wednesday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 2)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::thursday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 3)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::friday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 4)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::saturday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 5)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::sunday)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 6)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::daily)
    {
        for(int i = 0; i < numberOfDaysInYear; i++) add_consumption(Year, i, fromMinute, toMinute, wattage);
    }
    else if(usage == Use::mo_fr)
    {
        for(int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 0 || day == 1 || day == 2 || day == 3 || day == 4)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
    else if(usage == Use::sa_su)
    {
        for (int i = 0; i < numberOfDaysInYear; i++)
        {
            if (day == 5 || day == 6)
            {
                add_consumption(Year, i, fromMinute, toMinute, wattage);
            }
            day++;
            if (day == 7)
            {
                day = 0;
            }
        }
    }
}


inline float sum(const year& Year)
{
    float sum = 0.0f;
    for (int i = 0; i < numberOfDaysInYear; i++)
    {
        for (int j = 0; j < quarterIntervalsHourDays; j++)
        {
            sum += Year.values[i][j];
        }
    }
    return sum;
}


int main()
{
    year actual;
    year total;

    actual.yearValue = 2024;
    actual.firstDayOfWeek = Use::monday;
    actual.unit = "Watt";
    zeros(actual);

    total.yearValue = 2024;
    total.firstDayOfWeek = Use::monday;
    total.unit = "Watt";
    zeros(total);

    //float priceInKW = 0.30f;
    char choice;
    cout << "YEARLY CONSUMPTION QUARTER HOUR" << endl;
    while(true)
    {
        cout << "q quit" <<endl;
        cout << "a add actual to total (using operator +)" << endl;
        cout << "m subtract actual from total (using operator -)" <<endl;
        cout << "s scalar multiplication" << endl;
        cout << "c change unit" << endl;
        cout << "v sum up values" << endl;
        cout << "o output actual (using operator <<)" << endl;
        cout << "t output total (using operator <<)" << endl;
        cout << "u add consumption according to frequency of use (call functions add_consumption)" <<endl;
        cout << "y set actual to ones (call function ones)" << endl;
        cout << "z set actual to zeros (call function zeros)" <<endl;
        cout <<">> ";
        cin >> choice;
        if(choice == 'q') break;
        else if(choice == 'a') total = total + actual;
        else if(choice == 'm') total = total - actual;
        else if(choice == 's')
        {
            cout << "a for actual"<<endl;
            cout << "t for total" << endl;
            float scalar;
            char ch;
            cin >> ch;
            cout << "value of scalar? ";
            cin >> scalar;
            if (ch == 'a') actual = scalar * actual;
            else if(ch == 't') total = scalar * total;

        }
        else if(choice == 'c')
        {
            cout << "a for actual"<<endl;
            cout << "t for total" << endl;
            char ch;
            string unitType;
            cin >> ch;
            cout << "what is the new unit? ";
            cin >> unitType;
            if (ch == 'a') set_unit(actual, unitType);
            else if(ch == 't') set_unit(total, unitType);
        }
        else if(choice == 'v')
        {
            cout << "sum actual = " << sum(actual) << " " <<actual.unit << endl;
            cout << "sum total = " << sum(total) << " " << total.unit << endl;
        }
        else if(choice == 'o') cout << actual << endl;
        else if(choice == 't') cout << total <<endl;
        else if(choice == 'u')
        {
            string time;
            int fromMinute, fromHour;
            int toHour, toMinute;
            float wattage;

            Use use;
            input_use("how often it will be used?", use);
            if(use == Use::once)
            {
              //  int day;
                cout << "on which day? ";

            }
            cout << "from hour:minute? ";
            cin >> time;
            std::stringstream ss(time);
            char delimiter;
            ss >> fromHour >> delimiter >> fromMinute;
            fromMinute += fromHour * 60;
            cout << "to hour:minute? ";
            cin >> time;
            std::stringstream ss1(time);
            ss1 >> toHour >> delimiter >> toMinute;
            toMinute += toHour * 60;
            cout << "how many watt it will have? ";
            cin >> wattage;

            add_consumption(actual, use, fromMinute, toMinute, wattage);
        }
        else if(choice == 'y') ones(actual);
        else if(choice == 'z')
        {
            zeros(actual);
        }
    }
    return 0;
}



