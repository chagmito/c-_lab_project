
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
    float priceInkWh;
    string powerSupplier;
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

void add_consumer_from_file_to_household(HouseHold& household, consumer* consumers)
{
    if(household.consumers)
    {
        consumer* current = household.consumers;
        while(current->next != nullptr) current = current->next;
        current->next = consumers;
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
    return nconsumer.hours;

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
void print_consumer(consumer& powerConsumer, HouseHold& household, int index)
{

    cout << std::right << setw(COLUMN_WIDTH - 2) << index << ": "  << std::fixed << setprecision(2) << powerConsumer.description << " (at address: " << hex << &powerConsumer << dec <<")"<<endl;
    cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption: "  << std::fixed << setprecision(2) << powerConsumer.watt<< " W" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption Standby: "  << std::fixed << setprecision(2) << powerConsumer.watt_standby << " W" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual hours of use: "  << std::fixed << setprecision(2) << annual_hours_of_use(powerConsumer) << " h" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual hours of standby: "  << std::fixed << setprecision(2) << annual_hours_of_standby(powerConsumer) << " h" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual consumption: "  << std::fixed << setprecision(1) << annual_kWh(powerConsumer) << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "annual costs: " << std::fixed << setprecision(2) << annual_kWh(powerConsumer) * household.priceInkWh << " EUR" << endl;
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

void print_household(HouseHold& household, int householdNo)
{
    cout << "H O U S E H O L D   N O   "<<householdNo<<"   P O W E R   C O N S U M P T I O N" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "city: " << household.cityName <<" (at address: " << hex << &household << dec <<")" <<endl;
    cout << std::right << setw(COLUMN_WIDTH) << "price for one kWh: " << std::fixed << setprecision(2) << household.priceInkWh*100 << " ct/kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "power supplier: " << std::fixed << setprecision(2) << household.powerSupplier<< endl;
    cout << std::right << setw(COLUMN_WIDTH) << "square meters: " << std::fixed << setprecision(0) << household.noOfSquareMetre << " qm" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "persons: " << household.noOfPerson << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "water heated using electricity: " << (household.isWaterHeatedElectrically ? "yes" : "no") << endl;
    cout << std::right << setw(COLUMN_WIDTH - 2) << "list of consumers" << endl;
    cout << "------------------------------------------------------" << endl;

    int index = 1;
    consumer* current = household.consumers;
    while (current)
    {
        print_consumer(*current, household, index);
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
    else
    {
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

    float totalPowerCosts = totalPowerConsumption * household.priceInkWh;

    cout << std::right << setw(COLUMN_WIDTH) << "power consumption square meters: " << std::fixed << setprecision(1) << totalPowerConsumptionPerSquareMeter << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "power consumption all persons: " << std::fixed << setprecision(1) << totalPowerConsumptionPerPerson << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "total annual power consumption: " << std::fixed << setprecision(1) << totalPowerConsumption << " kWh" << endl;
    cout << std::right << setw(COLUMN_WIDTH) << "total annual power costs: " << std::fixed << setprecision(1) << totalPowerCosts << " EUR" << endl;
    cout<<endl;
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
    cout <<"what is the price for one kWh in EUR? ";
    cin >> household.priceInkWh;
    cout<<"who is the power supplier? ";
    cin >> household.powerSupplier;

    if(ishotwateruse == 'y') household.isWaterHeatedElectrically = 1;
    else household.isWaterHeatedElectrically = 0;

    household.consumers = nullptr;
}

Use findFrequencyOfUse(string type)
{
    Use use;
    if(type == "once") use = once;
    else if(type == "daily") use = daily;
    else if(type == "Monday to Friday") use = mo_fr;
    else if(type == "Saturday and Sunday") use = sa_su;
    else if(type == "weekly") use = weekly;
    return use;
}

void readDataFromFile(const string& fileName, char separator, HouseHold* households[], int& numberOfHouseholds, string& cityName)
{
    ifstream inputFile;
    inputFile.open(fileName);
    vector<string > words;
    string line;
    while(getline(inputFile, line))
    {
        stringstream ss(line);
        string word;

        while(getline(ss, word, separator))
        {
            ///cout<<word<<endl;
            if(!word.empty())words.push_back(word);
        }
        line.clear();
        if (inputFile.eof())
        {
            break;
        }
    }
    int houseNo = -1;
    for (int i = 0; i < words.size(); )
    {
        ///cout<<words[i] <<endl;
        if(words[i] == "A4")
        {
            ///cout<<numberOfHouseholds<<" "<<cityName<<" "<<priceInKWh<<endl;
            ///numberOfHouseholds = stoi(words[i + 1]);
            cityName = words[i + 2];
            i += 3;
            ///cout<<numberOfHouseholds<<" "<<cityName<<" "<<priceInKWh<<endl;
        }
        else if(words[i] == "household")
        {
            HouseHold* newHousehold = new HouseHold;
            newHousehold->cityName = words[i + 2];
            newHousehold->isWaterHeatedElectrically = words[i + 3] == "true"?1:0;
            newHousehold->noOfPerson = stoi(words[i + 4]);
            newHousehold->noOfSquareMetre = stof(words[i + 5]);
            newHousehold->priceInkWh = stof(words[i + 6]);
            newHousehold->powerSupplier = words[i + 7];
            newHousehold->consumers = nullptr;
            households[stoi(words[i+1])] = newHousehold;
            houseNo = stoi(words[i+1]);
            ///cout<<houseNo<<endl;
            i += 8;
        }
        else if(words[i] == "consumer")
        {
            consumer* newConsumer = new consumer;
            newConsumer->description = words[i + 1];
            newConsumer->hours = stof(words[i + 2]);

            Use usetype= findFrequencyOfUse(words[i + 3]);
            newConsumer->use = usetype;
            newConsumer->watt = stof(words[i + 4]);
            newConsumer->watt_standby = stof(words[i + 5]);
            newConsumer->next = nullptr;
            add_consumer_from_file_to_household(*households[houseNo], newConsumer);
            ///cout<<houseNo<<endl;
            i += 6;

        }
    }
}

string UseType(Use use)
{
    string type;
    if(use == once) type = once;
    else if(use == daily) type = "daily";
    else if(use == mo_fr) type = "Monday to Friday";
    else if(use == sa_su) type = "Saturday and Sunday";
    else if(use == weekly) type = "weekly";
    return type;
}

void writeDataToFile(const string& fileName, char separator, HouseHold* households[], int numberOfHouseholds, const string& cityName)
{
    ofstream file;
    file.open(fileName);
    file <<"A4" << separator << numberOfHouseholds<<separator<< cityName<<endl;
    for(int i = 1; i <= numberOfHouseholds; i++)
    {
        if(households[i] != nullptr)
        {
            file << "household" <<separator<<i<<separator<<households[i]->cityName<< separator<<(households[i]->isWaterHeatedElectrically?"true":"false" )<<separator<<households[i]->noOfPerson<<separator<<households[i]->noOfSquareMetre<<separator<<households[i]->priceInkWh<<separator<<households[i]->powerSupplier<<endl;
            if(households[i]->consumers)
            {
                consumer* current = households[i]->consumers;
                while (current)
                {
                    file<<"consumer"<<separator<<current->description<<separator<<current->hours<<separator<<UseType(current->use)<<separator<<current->watt<<separator<<current->watt_standby<<endl;
                    current = current->next;
                }
            }
        }
    }
    file.close();
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
    getline(cin >> std::ws, cityName);

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
        cout<< "r read data from file" << endl;
        cout << "w write data into file" << endl;
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
            getline(cin >> std::ws, newConsumer->description);
            ///cin >> newConsumer->description;
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
            print_household(*households[householdNumber], householdNumber);
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
                if(households[i] != nullptr) print_household(*households[i], i);
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
        else if(userChoice == 'w')
        {
            string fileName;
            char separatorChar;
            cout << "input file name: ";
            cin >> fileName;
            cout << "input separator character: ";
            cin >> separatorChar;
            cout << "output file "<<fileName<<" opened..."<<endl;
            writeDataToFile(fileName,separatorChar,households, noOfHOusehold, cityName);
            cout << "output file "<<fileName<<" closed"<<endl;

        }
        else if(userChoice == 'r')
        {
            string fileName;
            char separatorChar;
            cout << "input file name: ";
            cin >> fileName;
            cout << "input separator character: ";
            cin >> separatorChar;
            cout << "input file "<<fileName<<" opened..."<<endl;
            readDataFromFile(fileName,separatorChar,households, noOfHOusehold, cityName);
            cout << "input file "<<fileName<<" closed"<<endl;

        }
        else cout << "sorry wrong choice" << endl;

    }

    return 0;

}
