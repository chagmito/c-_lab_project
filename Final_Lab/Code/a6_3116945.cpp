/***********************************************************************
Matr.-Nr:                     ...3116945
Nachname/Surname:             ...GHOSH
Vorname/Given name:           ...MITO CHANDRA
Uni-Email:                    ...mito.ghosh@stud.uni-due.de
Studiengang/Course of studis: ...ISE(CE)
***********************************************************************/

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

void input_use(const string &message, Use &use)
{
    cout << message << endl;
    cout << "daily (d)" << endl;
    cout << "mo_fr (m)" << endl;
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
        type = "once";
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

class Device
{
private:
    string description;
    Device *next;

public:
    Device(Device *next = nullptr) : next(next) {}

    virtual ~Device()
    {
        cout << "Device " << get_description() << " at address " << this << " deleted" << endl;
    }

    string get_description()
    {
        return description;
    }

    Device *get_next()
    {
        return next;
    }

    void set_description(string description)
    {
        this->description = description;
    }

    void set_next(Device *next)
    {
        this->next = next;
    }

    virtual void input()
    {
        cout << "what is the description? ";
        getline(cin >> ws, description);
    }

    virtual void print(int index, float price_in_KWh) = 0;

    virtual float annual_kWh() = 0;

    virtual Device *get_a_copy() = 0;

    virtual string get_string_for_file(char separator) = 0;
};

class Consumer : public Device
{
private:
    float watt;
    Use use;

    static int total_number;

public:
    Consumer(Device *next = nullptr) : Device(next)
    {
        total_number++;
    }

    virtual ~Consumer()
    {
        total_number--;
        cout << "Consumer " << get_description() << " at address " << this << " deleted" << endl;
    }

    static int get_total_number() { return total_number; }

    float get_watt() { return this->watt; }

    Use get_use() { return this->use; }

    void set_watt(float w) { this->watt = w; }

    void set_use(Use use) { this->use = use; }

    virtual void input()
    {
        Device::input();
        cout << "how many watt it will have? ";
        cin >> watt;
        input_use("how often it will be used?", use);
    }
};

int Consumer::total_number = 0;

class Immobile : public Consumer
{
private:
    float watt_standby;
    float hours;

public:
    Immobile(Device *next = nullptr) : Consumer(next) {}

    virtual ~Immobile()
    {
        cout << "Immobile " << get_description() << " at address " << this << " deleted" << endl;
    }

    float get_watt_standby() { return this->watt_standby; }

    float get_hours() { return this->hours; }

    void set_watt_standby(float w_standby) { this->watt_standby = w_standby; }

    void set_hours(float hrs) { this->hours = hrs; }

    float annual_hours_of_use()
    {
        if (get_use() == once)
            return hours;
        else if (get_use() == daily)
            return hours * 365.0f;
        else if (get_use() == mo_fr)
            return hours * 260.0f;
        else if (get_use() == sa_su)
            return hours * 104.0f;
        else if (get_use() == weekly)
            return hours * 52.0f;
        else
            return 0;
    }

    float annual_hours_of_standby()
    {
        float standbyHours = 8760 - annual_hours_of_use();
        return standbyHours;
    }

    float annual_kWh()
    {
        return (annual_hours_of_use() * get_watt() + annual_hours_of_standby() * watt_standby) / 1000.0f;
    }

    void print(int index, float price_in_KWh)
    {
        cout << right << setw(COLUMN_WIDTH - 2) << index << ": " << fixed << setprecision(2)
             << get_description() << endl;
        cout << right << setw(COLUMN_WIDTH) << "(this: " << this << ")" << endl;
        cout << right << setw(COLUMN_WIDTH) << "solar cells installed power: " << fixed << setprecision(2)
             << get_watt() << " W" << endl;
        cout << right << setw(COLUMN_WIDTH) << "Power Consumption Standby: " << fixed << setprecision(2)
             << watt_standby << " W" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual hours of use: " << fixed << setprecision(2)
             << annual_hours_of_use() << " h" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual hours of standby: " << fixed << setprecision(2)
             << annual_hours_of_standby() << " h" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual consumption: " << fixed << setprecision(1)
             << annual_kWh() << " kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual costs: " << fixed << setprecision(2)
             << annual_kWh() * price_in_KWh << " EUR" << endl;
    }

    void input()
    {
        Consumer::input();
        cout << "how many watt standby it will have? ";
        cin >> watt_standby;
        cout << "how many hours it will be operating then? ";
        cin >> hours;
    }

    virtual Device *get_a_copy()
    {
        Immobile *obj = new Immobile();
        *obj = *this;
        return obj;
    }

    virtual string get_string_for_file(char separator)
    {
        stringstream ss;
        ss << "Immobile";
        ss << separator << get_description();
        ss << separator << get_watt();
        ss << separator << UseType(get_use());
        ss << separator << watt_standby;
        ss << separator << hours;
        return ss.str();
    }
};

class Mobile : public Consumer
{
private:
    float km;

public:
    Mobile(Device *next = nullptr) : Consumer(next) {}

    virtual ~Mobile()
    {
        cout << "Mobile " << get_description() << " at address " << this << " deleted" << endl;
    }

    float get_km() const
    {
        return km;
    }

    void set_km(float km)
    {
        Mobile::km = km;
    }

    void input()
    {
        Consumer::input();
        cout << "how many kilometer will be driven? ";
        cin >> km;
    }

    float frequency_of_use()
    {
        if (get_use() == once)
            return 1;
        else if (get_use() == daily)
            return 365.0f;
        else if (get_use() == mo_fr)
            return 260.0f;
        else if (get_use() == sa_su)
            return 104.0f;
        else if (get_use() == weekly)
            return 52.0f;
        else
            return 0;
    }

    virtual float annual_kWh()
    {
        return frequency_of_use() * (km / 100.0f) * (get_watt() / 1000.0f);
    }

    virtual void print(int index, float price_in_KWh)
    {
        cout << right << setw(COLUMN_WIDTH - 2) << index << ": " << fixed << setprecision(2)
             << get_description() << endl;
        cout << right << setw(COLUMN_WIDTH) << "(this: " << this << ")" << endl;
        cout << right << setw(COLUMN_WIDTH) << "Power Consumption Per 100 km: " << fixed << setprecision(2)
             << (get_watt() / 1000.0f) << " kW" << endl;
        cout << right << setw(COLUMN_WIDTH) << "kilometer driven: " << fixed << setprecision(2)
             << km << " km " << UseType(get_use()) << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual consumption: " << fixed << setprecision(1)
             << annual_kWh() << " kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual costs: " << fixed << setprecision(2)
             << annual_kWh() * price_in_KWh << " EUR" << endl;
    }

    virtual Device *get_a_copy()
    {
        Mobile *obj = new Mobile();
        *obj = *this;
        return obj;
    }

    virtual string get_string_for_file(char separator)
    {
        stringstream ss;
        ss << "Mobile";
        ss << separator << get_description();
        ss << separator << km;
        ss << separator << UseType(get_use());
        ss << separator << get_watt();
        return ss.str();
    }
};

class Producer : public Device
{
public:
    Producer(Device *next = nullptr) : Device(next) {}

    virtual ~Producer()
    {
        cout << "Producer " << get_description() << " at address " << this << " deleted" << endl;
    }

    void input()
    {
        Device::input();
    }
};

class Solar : public Producer
{
private:
    float watt_peak;
    int year;

public:
    Solar(Device *next = nullptr) : Producer(next) {}

    virtual ~Solar()
    {
        cout << "Solar " << get_description() << " at address " << this << " deleted" << endl;
    }

    float get_watt_peak() const
    {
        return watt_peak;
    }

    void set_watt_peak(float wattPeak)
    {
        watt_peak = wattPeak;
    }

    int get_year() const
    {
        return year;
    }

    void set_year(int year)
    {
        Solar::year = year;
    }

    void input()
    {
        Producer::input();
        cout << "how many watt peak have been installed? ";
        cin >> watt_peak;
        cout << "in which year the solar modules are installed? ";
        cin >> year;
    }

    void print(int index, float price_in_KWh)
    {
        cout << right << setw(COLUMN_WIDTH - 2) << index << ": " << fixed << setprecision(2)
             << get_description() << endl;
        cout << right << setw(COLUMN_WIDTH) << "(this: " << this << ")" << endl;
        cout << right << setw(COLUMN_WIDTH) << "solar cells installed power: " << fixed << setprecision(2)
             << watt_peak << " watt_peek" << endl;
        cout << right << setw(COLUMN_WIDTH) << "Age of solar plant: " << fixed << setprecision(2)
             << (2024 - year) << " years" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual production: " << fixed << setprecision(1)
             << annual_kWh() << " kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "annual savings: " << fixed << setprecision(2)
             << annual_kWh() * price_in_KWh << " EUR" << endl;
    }

    virtual float annual_kWh()
    {
        return -watt_peak * (1 - 0.005 * (2024 - year));
    }

    virtual Device *get_a_copy()
    {
        Solar *obj = new Solar();
        *obj = *this;
        return obj;
    }

    virtual string get_string_for_file(char separator)
    {
        stringstream ss;
        ss << "Solar";
        ss << separator << get_description();
        ss << separator << year;
        ss << separator << watt_peak;
        return ss.str();
    }
};

class HouseHold
{
private:
    int noOfPerson;
    float noOfSquareMetre;
    int noOfElectricalDevice;
    bool isWaterHeatedElectrically;
    float priceInkWh;
    string powerSupplier;
    Device *devices;

public:
    HouseHold() : devices(nullptr){};

    ~HouseHold()
    {

        Device *current = get_devices();
        while (current)
        {
            Device *next = current->get_next();

            delete current;
            current = next;
        }
        cout << "HouseHold at address " << this << " deleted" << endl;
    }

    Device *get_devices() const
    {
        return devices;
    }

    void set_devices(Device *devices)
    {
        HouseHold::devices = devices;
    }

    float get_price_kWh() { return this->priceInkWh; }

    string get_power_supplier() { return this->powerSupplier; }

    int get_persons() { return this->noOfPerson; }

    float get_square_meters() { return this->noOfSquareMetre; }

    bool get_electric_water_heating() { return this->isWaterHeatedElectrically; }

    void set_price_kWh(float price) { this->priceInkWh = price; }

    void set_power_supplier(string supplier) { this->powerSupplier = supplier; }

    void set_persons(int persons) { this->noOfPerson = persons; }

    void set_square_meters(float square_meters) { this->noOfSquareMetre = square_meters; }

    void set_electric_water_heating(bool isWaterHeatedElectrically)
    {
        this->isWaterHeatedElectrically = isWaterHeatedElectrically;
    }

    void add_device_to_household(Device *device)
    {
        if (device == nullptr)
        {
            cerr << "Invalid" << endl;
        }

        if (devices == nullptr)
        {
            devices = device;
        }
        else
        {

            Device *cu = devices;

            while (cu->get_next() != nullptr)
            {
                cu = cu->get_next();
            }
            cu->set_next(device);
        }
    }

    Device *move_up(int k)
    {
        if (k <= 1)
            return devices;
        if (devices == nullptr || devices->get_next() == nullptr)
            return devices;

        Device *prev_prev = nullptr;
        Device *prev = nullptr;
        Device *current = devices;
        int position = 1;

        while (current != nullptr && position < k)
        {
            prev_prev = prev;
            prev = current;
            current = current->get_next();
            position++;
        }

        if (current == nullptr)
            return devices;

        if (prev != nullptr)
        {
            prev->set_next(current->get_next());
            current->set_next(prev);
            if (prev_prev != nullptr)
            {
                prev_prev->set_next(current);
            }
            else
            {
                return current;
            }
        }

        return devices;
    }

    static HouseHold *copy_devices(HouseHold &FromHousehold, HouseHold &ToHousehold)
    {
        stack<Device *> ReverselyDevicesStack;

        Device *sourceCurrent = FromHousehold.get_devices();
        while (sourceCurrent != nullptr)
        {
            ReverselyDevicesStack.push(sourceCurrent);
            sourceCurrent = sourceCurrent->get_next();
        }

        while (!ReverselyDevicesStack.empty())
        {
            Device *sourceDevice = ReverselyDevicesStack.top();
            ReverselyDevicesStack.pop();

            Device *newDevice = sourceDevice->get_a_copy();
            newDevice->set_next(ToHousehold.get_devices());
            ToHousehold.set_devices(newDevice);
        }

        return &ToHousehold;
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
            isWaterHeatedElectrically = true;
        else
            isWaterHeatedElectrically = false;

        devices = nullptr;
    }

    void print_household(int i)
    {
        cout << "H O U S E H O L D   N O   " << i << "   P O W E R   C O N S U M P T I O N" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << right << setw(COLUMN_WIDTH) << "(this: " << this << ")" << endl;
        cout << right << setw(COLUMN_WIDTH) << "price for one kWh: " << fixed << setprecision(2)
             << get_price_kWh() * 100 << " ct/kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "power supplier: " << fixed << setprecision(2)
             << get_power_supplier() << endl;
        cout << right << setw(COLUMN_WIDTH) << "square meters: " << fixed << setprecision(2)
             << get_square_meters() << " qm" << endl;
        cout << right << setw(COLUMN_WIDTH) << "persons: " << get_persons() << endl;
        cout << right << setw(COLUMN_WIDTH) << "water heated using electricity: "
             << (get_electric_water_heating() ? "yes" : "no") << endl;
        cout << right << setw(COLUMN_WIDTH - 2) << "list of devices" << endl;
        cout << "----------------------------------------------------------------------" << endl;

        int index = 1;
        Device *current = get_devices();
        while (current)
        {
            current->print(index, priceInkWh);
            current = current->get_next();
            index++;
        }
        if (index > 1)
            cout << "----------------------------------------------------------------------" << endl;

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

        current = get_devices();
        while (current)
        {
            totalPowerConsumption += current->annual_kWh();
            current = current->get_next();
        }

        float totalPowerCosts = totalPowerConsumption * get_price_kWh();

        cout << right << setw(COLUMN_WIDTH) << "power consumption square meters: " << fixed << setprecision(1)
             << totalPowerConsumptionPerSquareMeter << " kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "power consumption all persons: " << fixed << setprecision(1)
             << totalPowerConsumptionPerPerson << " kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "total annual power consumption: " << fixed << setprecision(1)
             << totalPowerConsumption << " kWh" << endl;
        cout << right << setw(COLUMN_WIDTH) << "total annual power costs: " << fixed << setprecision(1)
             << totalPowerCosts << " EUR" << endl;
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

    ~Address()
    {
        cout << "Address " << to_string() << "at address " << this << " deleted" << endl;
    }

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
        return this->street + " " + this->no + " , " + this->zip + "  " + this->city;
    }

    void input()
    {
        cout << "what is the street name? ";
        cin >> street;
        cout << "what is house number? ";
        cin >> no;
        cout << "what is zip code? ";
        cin >> zip;
        cout << "what is the city name? ";
        cin >> city;
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

    ~House()
    {
        for (int i = 0; i < number_of_households; i++)
        {
            delete households[i];
            households[i] = nullptr;
        }

        delete[] households;

        cout << "House at address " << &households << " deleted" << endl;
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

    static Use findFrequencyOfUse(string type)
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

    void print_all()
    {
        cout << "======================================================================" << endl;
        cout << right << setw(COLUMN_WIDTH) << " House " << endl;
        cout << "======================================================================" << endl;
        cout << right << setw(COLUMN_WIDTH) << "(this: " << &households << ") " << endl;
        cout << right << setw(COLUMN_WIDTH) << "address: " << address.to_string() << " " << endl;
        cout << right << setw(COLUMN_WIDTH) << "number of households: " << number_of_households << " " << endl;
        cout << right << setw(COLUMN_WIDTH) << "total numbers of devices: " << Consumer::get_total_number()
             << endl;

        cout << "======================================================================" << endl;

        for (int i = 0; i < number_of_households; i++)
        {
            if (households[i] != nullptr)
            {
                households[i]->print_household(i);
            }
        }
        cout << "======================================================================" << endl;
    }

    void writeDataToFile(const string &fileName, char separator)
    {
        ofstream file;
        file.open(fileName);
        file << "A6" << separator << number_of_households << separator << address.get_Street() << separator
             << address.get_No() << separator << address.get_Zip() << separator << address.get_City() << endl;
        for (int i = 0; i < number_of_households; i++)
        {
            if (households[i] != nullptr)
            {
                file << "Household" << separator << i << separator
                     << (households[i]->get_electric_water_heating() ? "true" : "false") << separator
                     << households[i]->get_persons() << separator << households[i]->get_square_meters() << separator
                     << households[i]->get_price_kWh() << separator << households[i]->get_power_supplier() << endl;
                if (households[i]->get_devices())
                {
                    Device *current = households[i]->get_devices();
                    while (current)
                    {
                        file << current->get_string_for_file(separator) << endl;
                        current = current->get_next();
                    }
                }
            }
        }
        file.close();
    }

    static void readDataFromFile(House *&house, const string &fileName, char separator)
    {
        ifstream inputFile;
        inputFile.open(fileName);
        string line;

        int current_in;

        while (getline(inputFile, line))
        {
            if (line.find("A6") != string::npos)
            {

                istringstream stream(line);
                string element;

                vector<string> elements;
                while (getline(stream, element, separator))
                {
                    elements.push_back(element);
                }

                Address address;
                address.set_Street(elements[2]);
                address.set_No(elements[3]);
                address.set_Zip(elements[4]);
                address.set_City(elements[5]);
                house = new House(stoi(elements[1]), address);
            }
            else if (line.find("Household") != string::npos)
            {

                istringstream stream(line);
                string element;

                vector<string> elements;
                while (getline(stream, element, separator))
                {

                    elements.push_back(element);
                }

                string xx = elements[1];
                int x = stoi(xx);

                current_in = x;

                if (x >= 0)
                {
                    if (house->get_household(x) == nullptr)
                    {
                        house->set_household(new HouseHold(), x);
                    }
                }
                HouseHold *newHousehold = house->get_household(x);

                newHousehold->set_electric_water_heating(elements[2] == "true" ? 1 : 0);

                newHousehold->set_persons(stoi(elements[3]));
                newHousehold->set_square_meters(stof(elements[4]));
                newHousehold->set_price_kWh(stof(elements[5]));
                newHousehold->set_power_supplier(elements[6]);
            }
            else if (line.find("Mobile") != string::npos)
            {
                istringstream stream(line);
                string element;

                vector<string> elements;
                while (getline(stream, element, separator))
                {
                    elements.push_back(element);
                }

                Mobile *newMobile = new Mobile();

                newMobile->set_description(elements[1]);
                newMobile->set_km(stof(elements[2]));
                newMobile->set_use(findFrequencyOfUse(elements[3]));
                newMobile->set_watt(stof(elements[4]));
                newMobile->set_next(nullptr);

                house->get_household(current_in)->add_device_to_household(newMobile);
            }
            else if (line.find("Immobile") != string::npos)
            {
                istringstream stream(line);
                string element;

                vector<string> elements;
                while (getline(stream, element, separator))
                {
                    elements.push_back(element);
                }

                Immobile *newImmobile = new Immobile();

                newImmobile->set_description(elements[1]);
                newImmobile->set_hours(stof(elements[2]));
                newImmobile->set_use(findFrequencyOfUse(elements[3]));
                newImmobile->set_watt(stof(elements[4]));
                newImmobile->set_watt_standby(stof(elements[5]));
                newImmobile->set_next(nullptr);

                house->get_household(current_in)->add_device_to_household(newImmobile);
            }
            else if (line.find("Solar") != string::npos)
            {
                istringstream stream(line);
                string element;

                vector<string> elements;
                while (getline(stream, element, separator))
                {
                    elements.push_back(element);
                }

                Solar *newSolar = new Solar();

                newSolar->set_description(elements[1]);
                newSolar->set_year(stoi(elements[2]));
                newSolar->set_watt_peak(stof(elements[3]));
                newSolar->set_next(nullptr);

                house->get_household(current_in)->add_device_to_household(newSolar);
            }
        }
    }
};

int main()
{
    House *house = nullptr;
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD - Class Version" << endl;

    char userChoice = ' ';
    while (true)
    {
        cout << "q quit" << endl;
        cout << "d delete house" << endl;
        cout << "h house initialisation" << endl;
        cout << "i input immobile consumer" << endl;
        cout << "m input mobile consumer" << endl;
        cout << "s input solar producer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;
        cout << "a print all households" << endl;
        cout << "n new household" << endl;
        cout << "c copy all devices (added to already existing ones)" << endl;
        cout << "r read data from file" << endl;
        cout << "w write data into file" << endl;
        cout << ">> ";
        cin >> userChoice;

        switch (userChoice)
        {
        case 'q':
            return 0;
        case 'd':
        {
            delete house;
            house = nullptr;
            break;
        }
        case 'i':
        {
            Immobile *newImmobile = new Immobile();
            newImmobile->set_next(nullptr);
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;

            HouseHold *household = house->get_household(householdNumber);
            if (house && household)
            {
                newImmobile->input();
                household->add_device_to_household(newImmobile);
            }
            break;
        }
        case 'm':
        {
            Mobile *newMobile = new Mobile();
            newMobile->set_next(nullptr);
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;

            HouseHold *household = house->get_household(householdNumber);
            if (house && household)
            {
                newMobile->input();
                household->add_device_to_household(newMobile);
            }
            break;
        }
        case 's':
        {
            Solar *newSolar = new Solar();
            newSolar->set_next(nullptr);
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;

            HouseHold *household = house->get_household(householdNumber);
            if (house && household)
            {
                newSolar->input();
                household->add_device_to_household(newSolar);
            }
            break;
        }
        case 'u':
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
            break;
        }
        case 'p':
        {
            HouseHold *household = new HouseHold();
            cout << "number of household? ";
            int householdNumber;
            cin >> householdNumber;
            household = house->get_household(householdNumber);
            if (household)
            {
                household->print_household(householdNumber);
            }
            break;
        }
        case 'n':
        {
            cout << "number of household? ";
            int householdNumebr;
            cin >> householdNumebr;
            HouseHold *household = new HouseHold();
            household->input_household();
            if (house)
            {
                house->set_household(household, householdNumebr);
            }
            break;
        }
        case 'a':
        {
            if (house == nullptr)
                cout << "house is a nullptr, please first choose h to initialise a new house" << endl;
            else
                house->print_all();
            break;
        }
        case 'h':
        {

            int number_of_households;
            cout << "how many households does the house have? ";
            cin >> number_of_households;

            Address addr;
            addr.input();

            house = new House(number_of_households, addr);
            break;
        }
        case 'c':
        {
            int fromHousehold, toHousehold;
            cout << "number of household from which to copy devices? ";
            cin >> fromHousehold;
            HouseHold *fromHouse = house->get_household(fromHousehold);
            cout << "number of household to copy to? ";
            cin >> toHousehold;
            HouseHold *toHouse = house->get_household(toHousehold);
            HouseHold::copy_devices(*fromHouse, *toHouse);
            break;
        }
        case 'w':
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
            break;
        }
        case 'r':
        {
            string fileName;
            char separatorChar;
            cout << "input file name: ";
            cin >> fileName;
            cout << "input separator character: ";
            cin >> separatorChar;
            cout << "input file " << fileName << " opened..." << endl;
            House::readDataFromFile(house, fileName, separatorChar);
            cout << "input file " << fileName << " closed" << endl;
            break;
        }
        default:
            cout << "sorry wrong choice" << endl;
        }
    }
    return 0;
}
