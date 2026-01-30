/***********************************************************************
Matr.-Nr:                     ...3116945
Nachname/Surname:             ...Ghosh
Vorname/Given name:           ...Mito Chandra
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
float priceInkWh;
enum Use
{
    once,
    daily,
    mo_fr,
    sa_su,
    weekly
};

struct consumer
{
    string description;
    float watt;
    float watt_standby;
    float hours;
    Use use;
    consumer* next;

};

struct HouseHold
{
    string cityName;
    int noOfPerson;
    int noOfSquareMetre;
    int noOfElectricalDevice;
    bool isWaterHeatedElectrically;
    consumer* consumers;

};

void add_consumer_to_household(HouseHold& household, consumer* consumers)
{
    if(household.consumers)
    {
        consumers->next = household.consumers;
        household.consumers = consumers;
    }
    else
    {
        household.consumers = consumers;
    }
}

float annual_hours_of_use(consumer& nconsumer)
{
    if (nconsumer.use == once) return nconsumer.hours;
    else if (nconsumer.use == daily) return nconsumer.hours * 365.0;
    else if (nconsumer.use == mo_fr) return nconsumer.hours * 260.0;
    else if (nconsumer.use == sa_su) return nconsumer.hours * 104.0;
    else if(nconsumer.use == weekly) return nconsumer.hours * 52.0;

}

float annual_hours_of_standby(consumer& nConsumer)
{
    float standbyHours = 8760 - annual_hours_of_use(nConsumer);
    return standbyHours;
}

float annual_kWh(consumer& nConsumer)
{
    float annualUse = annual_hours_of_use(nConsumer);
    float annualUseStand = annual_hours_of_standby(nConsumer);
    float totalPowerConsumption = annualUse * nConsumer.watt + annualUseStand * nConsumer.watt_standby;
    return totalPowerConsumption / 1000.0;
}

consumer* move_up(consumer* head, int k)
{
    if (k <= 1) return head;
    if(head == nullptr || head->next == nullptr) return head;

    consumer* prev = nullptr;
    consumer* current = head;
    int position = 1;

    while (current != nullptr && position < k)
    {
        prev = current;
        current = current->next;
        position++;
    }

    if (current == nullptr) return head;

    swap(prev->description, current->description);
    swap(prev->watt, current->watt);
    swap(prev->watt_standby, current->watt_standby);
    swap(prev->hours, current->hours);
    swap(prev->use, current->use);

    return head;
}
void print_consumer(consumer& powerConsumer, int index)
{

    cout << std::right << setw(COLUMN_WIDTH - 2) << index << ": "  << std::fixed << setprecision(2) << powerConsumer.description << " (at address: " << hex << &powerConsumer << dec <<")"<<endl;
    cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption: "  << std::fixed << setprecision(2) << powerConsumer.watt<< " W" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption Standby: "  << std::fixed << setprecision(2) << powerConsumer.watt_standby << " W" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual hours of use: "  << std::fixed << setprecision(2) << annual_hours_of_use(powerConsumer) << " h" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual hours of standby: "  << std::fixed << setprecision(2) << annual_hours_of_standby(powerConsumer) << " h" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual consumption: "  << std::fixed << setprecision(1) << annual_kWh(powerConsumer) << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual costs: " << std::fixed << setprecision(2) << annual_kWh(powerConsumer) * priceInkWh << " EUR" << endl;
}

void input_use(string message, Use& use)
{
    cout<<message<<endl;
    cout<< "daily (d)" <<endl;
    cout<<"mo_fr (m)"<<endl;
    cout<<"once (o)"<<endl;
    cout<<"sa_su (s)"<<endl;
    cout<<"weekly (w)? ";
    char useType;
    cin >> useType;
    if(useType == 'w') use = weekly;
    else if(useType == 'd') use = daily;
    else if(useType == 'm') use = mo_fr;
    else if(useType == 'o') use = once;
    else if(useType == 's') use = sa_su;
}

void print_household(HouseHold& household, float PriceInKWH, int householdNo)
{
    cout << "H O U S E H O L D   N O   "<<householdNo<<"   P O W E R   C O N S U M P T I O N" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "city: " << household.cityName <<" (at address: " << hex << &household << dec <<")" <<endl;
    cout << std::right << setw(COLUMN_WIDTH) << "price for one kWh: " << std::fixed << setprecision(2) << priceInkWh*100 << " ct/kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "square meters: " << std::fixed << setprecision(0) << household.noOfSquareMetre << " qm" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "persons: " << household.noOfPerson << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "water heated using electricity: " << (household.isWaterHeatedElectrically ? "yes" : "no") << endl;
    cout << std::right << setw(COLUMN_WIDTH - 2) << "list of consumers" << endl;
    cout << "------------------------------------------------------" << endl;

    int index = 1;
    consumer* current = household.consumers;
    while (current)
    {
        print_consumer(*current, index);
        current = current->next;
        cout << "------------------------------------------------------" << endl;
        index++;
    }
    float totalPowerConsumptionPerSquareMeter;
    float totalPowerConsumptionPerPerson;
    float totalPowerConsumption;
    if(household.isWaterHeatedElectrically)
    {
        totalPowerConsumptionPerSquareMeter = household.noOfSquareMetre * annualAverageConsumptionPerSquareMetre;
        totalPowerConsumptionPerPerson = household.noOfPerson *  annualAverageConsumptionPerPersonWithElectricWaterHeating;
        totalPowerConsumption = totalPowerConsumptionPerSquareMeter + totalPowerConsumptionPerPerson;
    }
    else{
        totalPowerConsumptionPerSquareMeter = household.noOfSquareMetre * annualAverageConsumptionPerSquareMetre;
        totalPowerConsumptionPerPerson = household.noOfPerson *  annualAverageConsumptionPerPerson;
        totalPowerConsumption = totalPowerConsumptionPerSquareMeter + totalPowerConsumptionPerPerson;
    }


    current = household.consumers;
    while (current)
    {
        totalPowerConsumption += annual_kWh(*current);
        current = current->next;
    }

    float totalPowerCosts = totalPowerConsumption * priceInkWh;

    cout << std::right << setw(COLUMN_WIDTH) << "power consumption square meters: " << std::fixed << setprecision(1) << totalPowerConsumptionPerSquareMeter << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "power consumption all persons: " << std::fixed << setprecision(1) << totalPowerConsumptionPerPerson << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "total annual power consumption: " << std::fixed << setprecision(1) << totalPowerConsumption << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "total annual power costs: " << std::fixed << setprecision(1) << totalPowerCosts << " EUR" << endl;
}


HouseHold* copy_consumers(HouseHold& FromHousehold, HouseHold& ToHousehold)
{
    stack<consumer*> ReverselyConsumersStack;

    consumer* sourceCurrent = FromHousehold.consumers;
    while (sourceCurrent != nullptr)
    {
        ReverselyConsumersStack.push(sourceCurrent);
        sourceCurrent = sourceCurrent->next;
    }

    while (!ReverselyConsumersStack.empty())
    {
        consumer* sourceConsumer = ReverselyConsumersStack.top();
        ReverselyConsumersStack.pop();

        consumer* newConsumer = new consumer;
        newConsumer->description = sourceConsumer->description;
        newConsumer->watt = sourceConsumer->watt;
        newConsumer->watt_standby = sourceConsumer->watt_standby;
        newConsumer->hours = sourceConsumer->hours;
        newConsumer->use = sourceConsumer->use;

        newConsumer->next = ToHousehold.consumers;
        ToHousehold.consumers = newConsumer;
    }

    return &ToHousehold;
}



void input_household(HouseHold& household)
{
    cout << "how many square metres does the household have? ";
    cin >> household.noOfSquareMetre;

    cout << "how many persons live in this household? ";
    cin >> household.noOfPerson;

    char ishotwateruse;
    cout << "Is hot water produced electrically? (y(es) or n(o)): ";
    cin >> ishotwateruse;

    if(ishotwateruse == 'y') household.isWaterHeatedElectrically = 1;
    else household.isWaterHeatedElectrically = 0;

    household.consumers = nullptr;
}


int main()
{
    HouseHold household;
    int noOfHOusehold;
    cout<<"CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD"<<endl;
    cout << "how many households does the house have? ";
    cin >> noOfHOusehold;
    HouseHold* households[noOfHOusehold + 1];
    for (int i = 0; i <= noOfHOusehold; ++i)
    {
        households[i] = nullptr;
    }
    string cityName;
    cout << "in which city is the household located? ";
    cin >> cityName;
    cout <<"what is the price for one kWh in EUR? ";
    cin >> priceInkWh;

    char userChoice = ' ';
    while (true)
    {
        cout << "q quit" << endl;
        cout << "i input power consumer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;
        cout << "a print all households" <<endl;
        cout << "n new household" <<endl;
        cout << "c copy all consumers (added to already existing ones)" <<endl;
        cout << ">> ";
        cin >> userChoice;
        if(userChoice == 'q') break;
        else if (userChoice == 'i')
        {
            consumer* newConsumer = new consumer;
            newConsumer->next = nullptr;
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;
            cout << "what is the description of the power consumer? ";
            cin >> newConsumer->description;
            cout << "how many watt it will have? ";
            cin >> newConsumer->watt;
            cout << "how many watt standby it will have? ";
            cin >> newConsumer->watt_standby;
            input_use("how often it will be used?", newConsumer->use);
            cout << "how many hours it will be operating then? ";
            cin >> newConsumer->hours;
            add_consumer_to_household(*households[householdNumber], newConsumer);
        }
        else if (userChoice == 'u')
        {
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;
            int k;
            cout << "which one? ";
            cin >> k;
            households[householdNumber]->consumers = move_up(households[householdNumber]->consumers, k);
        }
        else if (userChoice == 'p')
        {
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;
            print_household(*households[householdNumber], priceInkWh, householdNumber);
        }
        else if(userChoice == 'n')
        {
            cout << "number of household? ";
            int householdNumebr;
            cin >> householdNumebr;
            if(households[householdNumebr] != nullptr) cout<<"Household "<<householdNumebr<<" already exist" <<endl;
            else
            {
                households[householdNumebr] = new HouseHold;
                households[householdNumebr]->cityName = cityName;
                input_household(*households[householdNumebr]);
            }
        }
        else if(userChoice == 'a')
        {
            for(int i = 1; i <= noOfHOusehold; i++)
            {
                if(households[i] != nullptr) print_household(*households[i], priceInkWh, i);
            }
        }
        else if(userChoice == 'c')
        {

            int fromHousehold, toHousehold;
            cout << "number of household from which to copy consumers? ";
            cin >> fromHousehold;
            cout <<"number of household to copy to? ";
            cin >> toHousehold;
            copy_consumers(*households[fromHousehold], *households[toHousehold]);

        }
        else cout << "sorry wrong choice" << endl;

    }

    return 0;

}
