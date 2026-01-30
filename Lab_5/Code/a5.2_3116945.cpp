#include <bits/stdc++.h>
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

void input_use(string message, Use &use)
{
    cout << message << endl;
    cout << "daily (d)" << endl;
    cout << "mo_fr (m)" << endl;
    cout << "once (o)" << endl;
    cout << "sa_su (s)" << endl;
    cout << "weekly (w)? ";
    char useType;
    cin >> useType;
    if (useType == 'w')
        use = weekly;
    else if (useType == 'd')
        use = daily;
    else if (useType == 'm')
        use = mo_fr;
    else if (useType == 'o')
        use = once;
    else if (useType == 's')
        use = sa_su;
}

string UseType(Use use)
{
    string type;
    if (use == once)
        type = once;
    else if (use == daily)
        type = "daily";
    else if (use == mo_fr)
        type = "Monday to Friday";
    else if (use == sa_su)
        type = "Saturday and Sunday";
    else if (use == weekly)
        type = "weekly";
    return type;
}

class Consumer
{
private:
    string description;
    float watt;
    float watt_standby;
    float hours;
    Consumer *next;
    Use use;

public:
    Consumer() : next(nullptr){};

    string getDescription() { return this->description; }
    Consumer *getNext() { return this->next; }
    float getWatt() { return this->watt; }
    float getWattStandby() { return this->watt_standby; }
    float getHours() { return this->hours; }
    float getConsumption() { return (this->watt * this->hours) + (this->watt_standby * (24 - this->hours)); }
    Use getUse() { return this->use; }
    void setNext(Consumer *next) { this->next = next; }
    void setDescription(string desc) { this->description = desc; }
    void setWatt(float w) { this->watt = w; }
    void setWattStandby(float w_standby) { this->watt_standby = w_standby; }
    void setHours(float hrs) { this->hours = hrs; }
    void setUse(Use use) { this->use = use; }

    float annual_hours_of_use(Consumer &nconsumer)
    {
        if (nconsumer.use == once)
            return nconsumer.hours;
        else if (nconsumer.use == daily)
            return nconsumer.hours * 365.0;
        else if (nconsumer.use == mo_fr)
            return nconsumer.hours * 260.0;
        else if (nconsumer.use == sa_su)
            return nconsumer.hours * 104.0;
        else if (nconsumer.use == weekly)
            return nconsumer.hours * 52.0;
    }

    float annual_hours_of_standby(Consumer &nConsumer)
    {
        float standbyHours = 8760 - annual_hours_of_use(nConsumer);
        return standbyHours;
    }

    float annual_kWh(Consumer &nConsumer)
    {
        float annualUse = annual_hours_of_use(nConsumer);
        float annualUseStand = annual_hours_of_standby(nConsumer);
        float totalPowerConsumption = annualUse * nConsumer.watt + annualUseStand * nConsumer.watt_standby;
        return totalPowerConsumption / 1000.0;
    }
    void print_consumer(Consumer &powerConsumer, float priceInKWh, int index)
    {

        cout << std::right << setw(COLUMN_WIDTH) << "(this: " << this << ")" << endl;
        cout << std::right << setw(COLUMN_WIDTH - 2) << index << ": " << std::fixed << setprecision(2) << powerConsumer.description << " (at address: " << hex << &powerConsumer << dec << ")" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption: " << std::fixed << setprecision(2) << powerConsumer.watt << " W" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption Standby: " << std::fixed << setprecision(2) << powerConsumer.watt_standby << " W" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "annual hours of use: " << std::fixed << setprecision(2) << annual_hours_of_use(powerConsumer) << " h" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "annual hours of standby: " << std::fixed << setprecision(2) << annual_hours_of_standby(powerConsumer) << " h" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "annual consumption: " << std::fixed << setprecision(1) << annual_kWh(powerConsumer) << " kWh" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "annual costs: " << std::fixed << setprecision(2) << annual_kWh(powerConsumer) * priceInKWh << " EUR" << endl;
    }

    void input_consumer()
    {
        cout << "number of household? ";
        int householdNumber;
        cin >> householdNumber;
        cout << "what is the description of the power consumer? ";
        getline(cin >> std::ws, description);
        cout << "how many watt it will have? ";
        cin >> watt;
        cout << "how many watt standby it will have? ";
        cin >> watt_standby;
        input_use("how often it will be used?", use);
        cout << "how many hours it will be operating then? ";
        cin >> hours;
        // add_consumer_to_household(*households[householdNumber], newConsumer);
    }
    void swap(Consumer &other)
    {
        std::swap(description, other.description);
        std::swap(watt, other.watt);
        std::swap(watt_standby, other.watt_standby);
        std::swap(hours, other.hours);
        std::swap(use, other.use);
    }
};

class HouseHold
{
private:
    int noOfPerson;
    int noOfSquareMetre;
    int noOfElectricalDevice;
    bool isWaterHeatedElectrically;
    float priceInkWh;
    string powerSupplier;
    Consumer *consumers;

public:
    HouseHold() : consumers(nullptr){};

    float get_price_kWh() { return this->priceInkWh; }
    string get_power_supplier() { return this->powerSupplier; }
    int get_persons() { return this->noOfPerson; }

    int get_square_meters() { return this->noOfSquareMetre; }
    bool get_electric_water_heating() { return this->isWaterHeatedElectrically; }
    Consumer *get_consumers() { return this->consumers; }

    void set_price_kWh(float price) { this->priceInkWh = price; }
    void set_power_supplier(string supplier) { this->powerSupplier = supplier; }
    void set_persons(int persons) { this->noOfPerson = persons; }
    void set_square_meters(int square_meters) { this->noOfSquareMetre = square_meters; }
    void set_electric_water_heating(bool isWaterHeatedElectrically)
    {
        this->isWaterHeatedElectrically = isWaterHeatedElectrically;
    }
    void set_consumers(Consumer *consumers) { this->consumers = consumers; }

    void add_consumer_to_household(HouseHold &household, Consumer *consumers)
    {
        if (household.consumers)
        {
            consumers->setNext(household.consumers);
            household.consumers = consumers;
        }
        else
        {
            household.consumers = consumers;
        }
    }
    Consumer *move_up( int k)
    {
        if (k <= 1)
            return consumers;
        if (consumers == nullptr || consumers->getNext() == nullptr)
            return consumers;

        Consumer *prev = nullptr;
        Consumer *current = consumers;
        int position = 1;

        while (current != nullptr && position < k)
        {
            prev = current;
            current = current->getNext();
            position++;
        }

        if (current == nullptr)
            return consumers;

        if (prev != nullptr && current != nullptr)
        {
            prev->swap(*current);
        }

        return consumers;
    }
    void input_household()
    {
        cout << "how many square metres does the household have? ";
        cin >> noOfSquareMetre;

        cout << "how many persons live in this household? ";
        cin >> noOfPerson;

        char ishotwateruse;
        cout << "Is hot water produced electrically? (y(es) or n(o)): ";
        cin >> ishotwateruse;
        cout << "what is the price for one kWh in EUR? ";
        cin >> priceInkWh;
        cout << "who is the power supplier? ";
        cin >> powerSupplier;

        if (ishotwateruse == 'y')
            isWaterHeatedElectrically = 1;
        else
            isWaterHeatedElectrically = 0;

        consumers = nullptr;
    }

    void print_household(int i)
    {
        cout << "H O U S E H O L D   N O   " << i << "   P O W E R   C O N S U M P T I O N" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "price for one kWh: " << std::fixed << setprecision(2) << get_price_kWh() * 100 << " ct/kWh" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "power supplier: " << std::fixed << setprecision(2) << get_power_supplier() << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "square meters: " << std::fixed << setprecision(0) << get_square_meters() << " qm" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "persons: " << get_persons() << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "water heated using electricity: " << (get_electric_water_heating() ? "yes" : "no") << endl;
        cout << std::right << setw(COLUMN_WIDTH - 2) << "list of consumers" << endl;
        cout << "------------------------------------------------------" << endl;

        int index = 1;
        Consumer *current = get_consumers();
        while (current)
        {
            cout << std::right << setw(COLUMN_WIDTH - 2) << index << ": " << std::fixed << setprecision(2) << current->getDescription() << " (at address: " << hex << &current << dec << ")" << endl;
            cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption: " << std::fixed << setprecision(2) << current->getWatt() << " W" << endl;
            cout << std::right << setw(COLUMN_WIDTH) << "Power Consumption Standby: " << std::fixed << setprecision(2) << current->getWattStandby() << " W" << endl;
            cout << std::right << setw(COLUMN_WIDTH) << "annual hours of use: " << std::fixed << setprecision(2) << current->annual_hours_of_use(*current) << " h" << endl;
            cout << std::right << setw(COLUMN_WIDTH) << "annual hours of standby: " << std::fixed << setprecision(2) << current->annual_hours_of_standby(*current) << " h" << endl;
            cout << std::right << setw(COLUMN_WIDTH) << "annual consumption: " << std::fixed << setprecision(1) << current->annual_kWh(*current) << " kWh" << endl;
            cout << std::right << setw(COLUMN_WIDTH) << "annual costs: " << std::fixed << setprecision(2) << current->annual_kWh(*current) * get_price_kWh() << " EUR" << endl;

            // current->print_consumer(*current, households[i]->get_price_kWh(), index);
            current = current->getNext();
            cout << "------------------------------------------------------" << endl;
            index++;
        }
        float totalPowerConsumptionPerSquareMeter;
        float totalPowerConsumptionPerPerson;
        float totalPowerConsumption;
        if (get_electric_water_heating())
        {
            totalPowerConsumptionPerSquareMeter = get_square_meters() * annualAverageConsumptionPerSquareMetre;
            totalPowerConsumptionPerPerson = get_persons() * annualAverageConsumptionPerPersonWithElectricWaterHeating;
            totalPowerConsumption = totalPowerConsumptionPerSquareMeter + totalPowerConsumptionPerPerson;
        }
        else
        {
            totalPowerConsumptionPerSquareMeter = get_square_meters() * annualAverageConsumptionPerSquareMetre;
            totalPowerConsumptionPerPerson = get_persons() * annualAverageConsumptionPerPerson;
            totalPowerConsumption = totalPowerConsumptionPerSquareMeter + totalPowerConsumptionPerPerson;
        }

        current = get_consumers();
        while (current)
        {
            totalPowerConsumption += current->annual_kWh(*current);
            current = current->getNext();
        }

        float totalPowerCosts = totalPowerConsumption * get_price_kWh();

        cout << std::right << setw(COLUMN_WIDTH) << "power consumption square meters: " << std::fixed << setprecision(1) << totalPowerConsumptionPerSquareMeter << " kWh" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "power consumption all persons: " << std::fixed << setprecision(1) << totalPowerConsumptionPerPerson << " kWh" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "total annual power consumption: " << std::fixed << setprecision(1) << totalPowerConsumption << " kWh" << endl;
        cout << std::right << setw(COLUMN_WIDTH) << "total annual power costs: " << std::fixed << setprecision(1) << totalPowerCosts << " EUR" << endl;
        cout << endl;
    }
};

class Address
{
private:
    string street;
    string no;
    string zip;
    string city;

public:
    Address(){};
    string get_Street()
    {
        return this->street;
    };
    string get_No()
    {
        return this->no;
    };
    string get_Zip()
    {
        return this->zip;
    };
    string get_City()
    {
        return this->city;
    };

    void set_Street(string street)
    {
        this->street = street;
    };

    void set_No(string no)
    {
        this->no = no;
    };

    void set_Zip(string zip)
    {
        this->zip = zip;
    };

    void set_City(string city)
    {
        this->city = city;
    };

    string to_string()
    {
        return this->street + " " + this->no + "\n" + this->zip + " " + this->city;
    }

    void input()
    {
        cout << "what is the street name? ";
        getline(cin, street);
        cout << "what is house number? ";
        getline(cin, no);
        cout << "what is zip code? ";
        getline(cin, zip);
        cout << "what is the city name? ";
        getline(cin, city);
    }
};

class House
{
private:
    int number_of_households;
    HouseHold **households;
    Address address;

public:
    House(int num_households, Address addr) : number_of_households(num_households), address(addr)
    {
        households = new HouseHold *[number_of_households];
        for (int i = 0; i < number_of_households; i++)
        {
            households[i] = nullptr;
        }
        address = addr;
    }
    HouseHold *get_household(int n)
    {
        if (n >= 0 && n < number_of_households)
        {
            return households[n];
        }
        return nullptr;
    }
    HouseHold *operator[](int n)
    {
        return get_household(n);
    }

    void set_household(HouseHold *household, int n)
    {
        if (n >= 0 && n < number_of_households)
        {
            households[n] = household;
        }
    }

    Use findFrequencyOfUse(string type)
    {
        Use use;
        if (type == "once")
            use = once;
        else if (type == "daily")
            use = daily;
        else if (type == "Monday to Friday")
            use = mo_fr;
        else if (type == "Saturday and Sunday")
            use = sa_su;
        else if (type == "weekly")
            use = weekly;
        return use;
    }

    HouseHold *copy_consumers(HouseHold &FromHousehold, HouseHold &ToHousehold)
    {
        stack<Consumer *> ReverselyConsumersStack;

        Consumer *sourceCurrent = FromHousehold.get_consumers();
        while (sourceCurrent != nullptr)
        {
            ReverselyConsumersStack.push(sourceCurrent);
            sourceCurrent->setNext(sourceCurrent->getNext());
        }

        while (!ReverselyConsumersStack.empty())
        {
            Consumer *sourceConsumer = ReverselyConsumersStack.top();
            ReverselyConsumersStack.pop();

            Consumer *newConsumer = new Consumer();
            newConsumer->setDescription(sourceConsumer->getDescription());
            newConsumer->setWatt(sourceConsumer->getWatt());
            newConsumer->setWattStandby(sourceConsumer->getWattStandby());
            newConsumer->setHours(sourceConsumer->getHours());
            newConsumer->setUse(sourceConsumer->getUse());

            newConsumer->setNext(ToHousehold.get_consumers());
            ToHousehold.set_consumers(newConsumer);
        }

        return &ToHousehold;
    }

    // Print all households
    void print_all()
    {

        for (int i = 0; i < number_of_households; i++)
        {
            if (households[i] != nullptr)
            {
                households[i]->print_household(i + 1);
            }
        }
        cout << "======================================================================" << endl;
    }

    void writeDataToFile(const string &fileName, char separator)
    {
        ofstream file;
        file.open(fileName);
        file << "A5" << separator << number_of_households << separator << address.get_City() << endl;
        for (int i = 1; i <= number_of_households; i++)
        {
            if (households[i] != nullptr)
            {
                file << "household" << separator << i << separator << address.get_City() << separator << (households[i]->get_electric_water_heating() ? "true" : "false") << separator << households[i]->get_persons() << separator << households[i]->get_square_meters() << separator << households[i]->get_price_kWh() << separator << households[i]->get_power_supplier() << endl;
                if (households[i]->get_consumers())
                {
                    Consumer *current = households[i]->get_consumers();
                    while (current)
                    {
                        file << "consumer" << separator << current->getDescription() << separator << current->getHours() << separator << UseType(current->getUse()) << separator << current->getWatt() << separator << current->getWattStandby() << endl;
                        current = current->getNext();
                    }
                }
            }
        }
        file.close();
    }

    void readDataFromFile(const string &fileName, char separator)
    {
        ifstream inputFile;
        inputFile.open(fileName);
        vector<string> words;
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string word;

            while (getline(ss, word, separator))
            {
                /// cout<<word<<endl;
                if (!word.empty())
                    words.push_back(word);
            }
            line.clear();
            if (inputFile.eof())
            {
                break;
            }
        }
        int houseNo = -1;
        for (int i = 0; i < words.size();)
        {
            /// cout<<words[i] <<endl;
            if (words[i] == "A5")
            {
                /// cout<<numberOfHouseholds<<" "<<cityName<<" "<<priceInKWh<<endl;
                /// numberOfHouseholds = stoi(words[i + 1]);
                address.set_City(words[i + 2]);
                i += 3;
                /// cout<<numberOfHouseholds<<" "<<cityName<<" "<<priceInKWh<<endl;
            }
            else if (words[i] == "household")
            {
                HouseHold *newHousehold = new HouseHold;
                newHousehold->set_electric_water_heating(words[i + 3] == "true" ? 1 : 0);
                newHousehold->set_persons(stoi(words[i + 4]));
                newHousehold->set_square_meters(stof(words[i + 5]));
                newHousehold->set_price_kWh(stof(words[i + 6]));
                newHousehold->set_power_supplier(words[i + 7]);
                newHousehold->set_consumers(nullptr);
                households[stoi(words[i + 1])] = newHousehold;
                houseNo = stoi(words[i + 1]);
                /// cout<<houseNo<<endl;
                i += 8;
            }
            else if (words[i] == "consumer")
            {
                Consumer *newConsumer = new Consumer;
                newConsumer->setDescription(words[i + 1]);
                newConsumer->setHours(stof(words[i + 2]));

                Use usetype = findFrequencyOfUse(words[i + 3]);
                newConsumer->setUse(usetype);
                newConsumer->setWatt(stof(words[i + 4]));
                newConsumer->setWattStandby(stof(words[i + 5]));
                newConsumer->setNext(nullptr);
                HouseHold household;
                household.add_consumer_to_household(*households[houseNo], newConsumer);
                /// cout<<houseNo<<endl;
                i += 6;
            }
        }
    }
};
int main()
{
    House *house = nullptr;
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD" << endl;
    string cityName;
    cout << "in which city is the household located? ";
    getline(cin >> std::ws, cityName);

    char userChoice = ' ';
    while (true)
    {
        cout << "q quit" << endl;
        cout << "h house initialisation" << endl;
        cout << "i input power consumer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;
        cout << "a print all households" << endl;
        cout << "n new household" << endl;
        cout << "c copy all consumers (added to already existing ones)" << endl;
        cout << "r read data from file" << endl;
        cout << "w write data into file" << endl;
        cout << ">> ";
        cin >> userChoice;
        if (userChoice == 'q')
            break;
        else if (userChoice == 'i')
        {
            Consumer *newConsumer = new Consumer();
            newConsumer->setNext(nullptr);
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;

            HouseHold *household = house->get_household(householdNumber);
            if (house && household)
            {
                newConsumer->input_consumer();

                household->set_consumers(newConsumer);
            }
        }
        else if (userChoice == 'u')
        {
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;
            int k;
            cout << "which one? ";
            cin >> k;
            HouseHold *household = house->get_household(householdNumber);
            if (household)
            {
                household->move_up(k);
            }
        }
        else if (userChoice == 'p')
        {
            HouseHold* household = new HouseHold();
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;
            household = house->get_household(householdNumber);
            if (household)
            {
                household->print_household(householdNumber);
            }
        }
        else if (userChoice == 'n')
        {
            cout << "number of household? ";
            int householdNumebr;
            cin >> householdNumebr;
            HouseHold* household = new HouseHold();
			household->input_household();
			if (house)
			{
				house->set_household(household, householdNumebr-1);
			}
        }
        else if (userChoice == 'a')
        {
            if (house == nullptr)
                cout << "house is a nullptr, please first choose h to initialise a new house" << endl;
            else house->print_all();
        }
        else if (userChoice == 'h')
        {
            int number_of_households;
            cout << "how many households does the house have? ";
            cin >> number_of_households;

            Address addr;
            addr.input();
            /// cout << addr.to_string() << endl;

            house = new House(number_of_households, addr);
        }
        else if (userChoice == 'c')
        {

            int fromHousehold, toHousehold;
            cout << "number of household from which to copy consumers? ";
            cin >> fromHousehold;
            HouseHold* fromHouse = new HouseHold();
            fromHouse = house->get_household(fromHousehold);
            cout << "number of household to copy to? ";
            cin >> toHousehold;
            HouseHold* toHouse = new HouseHold();
            toHouse = house->get_household(toHousehold);
            house->copy_consumers(*fromHouse, *toHouse);
            
        }
        else if (userChoice == 'w')
        {
            string fileName;
            char separatorChar;
            cout << "input file name: ";
            cin >> fileName;
            cout << "input separator character: ";
            cin >> separatorChar;
            cout << "output file " << fileName << " opened..." << endl;
            house->writeDataToFile(fileName, separatorChar);
            cout << "output file " << fileName << " closed" << endl;
        }
        else if (userChoice == 'r')
        {
            string fileName;
            char separatorChar;
            cout << "input file name: ";
            cin >> fileName;
            cout << "input separator character: ";
            cin >> separatorChar;
            cout << "input file " << fileName << " opened..." << endl;
            house->readDataFromFile(fileName, separatorChar);
            cout << "input file " << fileName << " closed" << endl;
        }
        else
            cout << "sorry wrong choice" << endl;
    }
    // Your code here
    return 0;
}
