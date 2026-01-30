/***********************************************************************
Matr.-Nr:                                 3116945
Nachname/Surname:             GHOSH
Vorname/Given name:           MITO CHANDRA
Uni-Email:                               mito.ghosh@stud.uni-due.de
Studiengang/Course of studis: ISE CE
***********************************************************************/

#include<bits/stdc++.h>
using namespace std;

int annualAverageConsumptionPerPerson = 200;
int annualAverageConsumptionPerPersonWithElectricWaterHeating = 550;
int annualAverageConsumptionPerSquareMetre = 9;
int annualAverageConsumptionPerElectricalDevice = 200;

struct HouseHold
{
    string cityName;
    int noOfPerson;
    int noOfSquareMetre;
    int noOfElectricalDevice;
    bool isWaterHeatedElectrically;

};

float the_annual_power_consumption(HouseHold household)
{
    float Power_consumption;
    if(household.isWaterHeatedElectrically)
    {
        Power_consumption = (household.noOfPerson * annualAverageConsumptionPerPersonWithElectricWaterHeating)
                            + (household.noOfSquareMetre * annualAverageConsumptionPerSquareMetre)
                            + (household.noOfElectricalDevice * annualAverageConsumptionPerElectricalDevice);
    }
    else
    {
        Power_consumption = (household.noOfPerson * annualAverageConsumptionPerPerson)
                            + (household.noOfSquareMetre * annualAverageConsumptionPerSquareMetre)
                            + (household.noOfElectricalDevice * annualAverageConsumptionPerElectricalDevice);
    }

    return Power_consumption;
}

float the_annual_power_costs(HouseHold household, float PriceInKWH)
{
    float total_cost = the_annual_power_consumption(household) * PriceInKWH;
    return  total_cost;
}

void input_city(string* cityName)
{
    cout<<"in which city is the household located? ";
    cin >> *cityName;
}

void input_integer(string msg, int* number)
{
    cout << msg<<" ";
    cin >> *number;
}

void input_electric_water_heating(bool* isWaterHeatedElectricity)
{
    cout<<"is hot water heated using electricity? (y(es) or n(o)) ";
    char boolValue;
    cin >> boolValue;
    if(boolValue == 'y') *isWaterHeatedElectricity = 1;
    else *isWaterHeatedElectricity = 0;
}

void print_household(HouseHold household, float PriceInKWH)
{
    string strWaterHeatedElectrically;
    if(household.isWaterHeatedElectrically) strWaterHeatedElectrically = "yes";
    else strWaterHeatedElectrically = "no";
    cout<<"AVERAGE POWER COSTS"<<endl;
    cout<<"==================="<<endl;
    cout<<"household in:"<<"\t\t\t\t"<<household.cityName<<endl;
    cout<<"square metres:"<<"\t\t\t\t"<<household.noOfSquareMetre<<endl;
    cout<<"persons:"<<"\t\t\t\t"<<household.noOfPerson<<endl;
    cout<<"(major) electrical devices:"<<"\t\t"<<household.noOfElectricalDevice<<endl;
    cout<<"water heated using electricity: "<<"\t"<<strWaterHeatedElectrically<<endl;
    cout <<"price for one kWh:"<<"\t\t\t"<<PriceInKWH<<" EUR"<<endl;
    cout<<"annual power consumption:"<<"\t\t"<<the_annual_power_consumption(household)<<" kWh"<<endl;
    cout<<"annual power costs:"<<"\t\t\t"<<the_annual_power_costs(household, PriceInKWH)<<" EUR"<<endl;
    cout<<endl;


}

int main()
{
    HouseHold household;
    cout<<"CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD"<<endl;
    float priceInkWh;
    input_city(&household.cityName);
    input_integer("how many square metres does the household have?", &household.noOfSquareMetre);
    input_integer("how many (major) electrical devices does the household have?", &household.noOfElectricalDevice);
    input_electric_water_heating(&household.isWaterHeatedElectrically);

    for(int person = 1; person <= 5; person++)
    {
        household.noOfPerson = person;
        for(float priceInkWh = 0.3; priceInkWh < 0.45; priceInkWh += 0.05){
            print_household(household, priceInkWh);
        }
    }

}

