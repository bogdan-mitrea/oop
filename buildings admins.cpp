//Ați fost puși să administrați baza de date a clădirilor care se află pe o anumită așezare. 
//Va trebui să adăugați clădiri în acea bază de date și să adăugați locuitori, angajați și 
//șefi în acele clădiri, iar la sfârșit o statistică acestor date.


#include <bits/stdc++.h>

using namespace std;

class Person
{
public:
    string mName;
    unsigned short mAge;
    double mSalary;
    Person() : mName(""), mAge(0), mSalary(0) {}
    Person(string name, unsigned short age, double salary) : mName(name), mAge(age), mSalary(salary) {}
    bool operator == (const Person & p) const
    {
        if(mName == p.mName && mAge == p.mAge && mSalary == p.mSalary) return true;
        return false;
    }
    bool operator < (const Person & p) const
    {
        if(mName < p.mName) return true;
        return false;
    }
};

class Building
{
protected:
    string mBuildingName;
    string mType;
    Person mCoordinator;
    vector<Person> mEmployees;
    vector<Person> mCitizens;
public:
    Building(string buildingname, string type) : mBuildingName(buildingname), mType(type) {}
    virtual void add(const Person & p) = 0;
    virtual void remove(const Person & p) = 0;
    virtual Building * operator + (const Person & p) = 0;
    virtual Building * operator - (const Person & p) {return nullptr;}
    virtual Building * operator - () {return nullptr;}
    string getBuildingName() const
    {
        return mBuildingName;
    }
    string getType() const
    {
        return mType;
    }
    unsigned short getEmployeesSize() const
    {
        return mEmployees.size();
    }
    unsigned short getCitizensSize() const
    {
        return mCitizens.size();
    }
    Person getEmployee(unsigned short i) const
    {
        return mEmployees[i];
    }
    Person getCitizen(unsigned short i) const
    {
        return mCitizens[i];
    }
    Person getCoordinator() const
    {
        return mCoordinator;
    }
};

class CityHall : public Building
{
public:
    CityHall(string nume_primarie) : Building(nume_primarie, "CityHall")
    {
        mCitizens.clear();
        mCoordinator = Person();
    }
    Building * operator+ (const Person & p)
    {
        if(mCoordinator == Person())
        {
            mCoordinator = p;
        }
        return this;
    }
    Building * operator - ()
    {
        mCoordinator = Person();
        return this;
    }
    void add(const Person & p)
    {
        mCitizens.push_back(p);
    }
    void remove(const Person & p)
    {
        for(int i = 0; i < mCitizens.size(); i++)
        {
            if(mCitizens[i].mName == p.mName)
            {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class Hospital : public Building
{
public:
    Hospital(string nume_spital) : Building(nume_spital, "Hospital")
    {
        mCitizens.clear();
        mEmployees.clear();
    }
    Building * operator+ (const Person & p)
    {
        mEmployees.push_back(p);
        return this;
    }
    Building * operator - (const Person & p)
    {
        for(int i = 0; i < mEmployees.size(); i++)
        {
            if(mEmployees[i].mName == p.mName)
            {
                mEmployees.erase(mEmployees.begin() + i);
                break;
            }
        }
        return this;
    }
    void add(const Person & p)
    {
        mCitizens.push_back(p);
    }
    void remove(const Person & p)
    {
        for(int i = 0; i < mCitizens.size(); i++)
        {
            if(mCitizens[i].mName == p.mName)
            {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class PoliceStation : public Building
{
public:
    PoliceStation(string nume_sectie) : Building(nume_sectie, "PoliceStation")
    {
        mCitizens.clear();
        mEmployees.clear();
    }
    Building * operator+ (const Person & p)
    {
        mEmployees.push_back(p);
        return this;
    }
    Building * operator - (const Person & p)
    {
        for(int i = 0; i < mEmployees.size(); i++)
        {
            if(mEmployees[i].mName == p.mName)
            {
                mEmployees.erase(mEmployees.begin() + i);
                break;
            }
        }
        return this;
    }
    void add(const Person & p)
    {
        mCitizens.push_back(p);
    }
    void remove(const Person & p)
    {
        for(int i = 0; i < mCitizens.size(); i++)
        {
            if(mCitizens[i].mName == p.mName)
            {
                mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class House : public Building
{
    unsigned short mMaxNumber;
public:
    House(string nume_casa, unsigned short maxnumber) : Building(nume_casa, "House"), mMaxNumber(maxnumber)
    {
        mCitizens.clear();
        mCoordinator = Person();
    }
    Building * operator+ (const Person & p)
    {
        if(mCoordinator == Person())
        {
            mCoordinator = p;
        }
        return this;
    }
    Building * operator - ()
    {
        mCoordinator = Person();
        return this;
    }
    void add(const Person & p)
    {
        if(mCitizens.size() < mMaxNumber - 1) mCitizens.push_back(p);
    }
    void remove(const Person & p)
    {
        for(int i = 0; i < mCitizens.size(); i++)
        {
            if(mCitizens[i].mName == p.mName)
            {
                if(mCitizens[i].mAge >= 18)
                    mCitizens.erase(mCitizens.begin() + i);
                break;
            }
        }
    }
};

class Block : public Building
{
    unsigned short mMaxNumberPerFloor;
public:
    Block(string nume_bloc, unsigned short nretaje, unsigned short maxnumber) : Building(nume_bloc, "Block"), mMaxNumberPerFloor(maxnumber)
    {
        mCitizens.clear();
        mCoordinator = Person();
        for(int i = 0; i < nretaje * mMaxNumberPerFloor; i++)
            mCitizens.push_back(Person());
    }
    Building * operator+ (const Person & p)
    {
        if(mCoordinator == Person())
        {
            mCoordinator = p;
        }
        return this;
    }
    Building * operator - ()
    {
        mCoordinator = Person();
        return this;
    }
    void add(const Person & p)
    {
        for(int i = 0; i < mCitizens.size(); i++)
        {
            if(mCitizens[i] == Person())
            {
                mCitizens[i] = p;
                break;
            }
        }
    }
    void remove(const Person & p)
    {
        for(int i = 0; i < mCitizens.size(); i++)
        {
            if(mCitizens[i].mName == p.mName)
            {
                if(mCitizens[i].mAge >= 18)
                    mCitizens[i] = Person();
                break;
            }
        }
    }
};

int main()
{
    string command, keyword, nume, cladire;
    unsigned short maxpers, etaje, maxetaj, varsta;
    double salariu;
    int nrc = 0, nrs = 0, nrp = 0, nrh = 0, nrb = 0;
    vector<Building *> buildings;
    while(cin >> command)
    {
        cin >> keyword;
        if(command == "add")
        {
            if(keyword == "CityHall")
            {
                cin >> cladire;
                buildings.push_back(new CityHall(cladire));
                nrc++;
            }
            if(keyword == "Hospital")
            {
                cin >> cladire;
                buildings.push_back(new Hospital(cladire));
                nrs++;
            }
            if(keyword == "PoliceStation")
            {
                cin >> cladire;
                buildings.push_back(new PoliceStation(cladire));
                nrp++;
            }
            if(keyword == "House")
            {
                cin >> cladire >> maxpers;
                buildings.push_back(new House(cladire, maxpers));
                nrh++;
            }
            if(keyword == "Block")
            {
                cin >> cladire >> etaje >> maxetaj;
                buildings.push_back(new Block(cladire, etaje, maxetaj));
                nrb++;
            }
            if(keyword == "coordinator")
            {
                cin >> nume >> varsta >> salariu >> cladire;
                Person p(nume, varsta, salariu);
                for(int i = 0; i < buildings.size(); i++)
                {
                    if(buildings[i]->getBuildingName() == cladire)
                    {
                        buildings[i] = *buildings[i] + p;
                        break;
                    }
                }
            }
            if(keyword == "employee")
            {
                cin >> nume >> varsta >> salariu >> cladire;
                Person p(nume, varsta, salariu);
                for(int i = 0; i < buildings.size(); i++)
                {
                    if(buildings[i]->getBuildingName() == cladire)
                    {
                        buildings[i] = *buildings[i] + p;
                        break;
                    }
                }
            }
            if(keyword == "citizen")
            {
                cin >> nume >> varsta >> salariu >> cladire;
                Person p(nume, varsta, salariu);
                for(int i = 0; i < buildings.size(); i++)
                {
                    if(buildings[i]->getBuildingName() == cladire)
                    {
                        buildings[i]->add(p);
                        break;
                    }
                }
            }
        }
        if(command == "remove")
        {
            cin >> nume >> cladire;
            Person p(nume, 0, 0);
            if(keyword == "coordinator")
            {
                for(int i = 0; i < buildings.size(); i++)
                {
                    if(buildings[i]->getBuildingName() == cladire)
                    {
                        buildings[i] = -*buildings[i];
                        break;
                    }
                }
            }
            if(keyword == "employee")
            {
                for(int i = 0; i < buildings.size(); i++)
                {
                    if(buildings[i]->getBuildingName() == cladire)
                    {
                        buildings[i] = *buildings[i] - p;
                        break;
                    }
                }
            }
            if(keyword == "citizen")
            {
                for(int i = 0; i < buildings.size(); i++)
                {
                    if(buildings[i]->getBuildingName() == cladire)
                    {
                        buildings[i]->remove(p);
                        break;
                    }
                }
            }
        }
    }
    
    string oras;
    if(nrc >= 3 && nrh >= 2 && nrp >= 3 && nrh >= 8 && nrb >= 4) oras = "Capital";
    else if(nrc >= 2 && nrh >= 1 && nrp >= 2 && nrh >= 4 && nrb >= 1) oras = "Town";
    else oras = "Village";
    cout << "Type: " << oras << endl;
    
    double s = 0;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "Hospital")
            s += buildings[i]->getCitizensSize();
    }
    cout << "Number of patients in hospitals: " << s << endl;
    
    s = 0;
    int ns = 0;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "Hospital")
            for(int j = 0; j < buildings[i]->getEmployeesSize(); j++)
            {
                s += buildings[i]->getEmployee(j).mSalary;
                ns++;
            }
    }
    cout << "Average salary for doctors: ";
    if(s == 0 && ns == 0) cout << "0" << endl;
    else cout << (double) s / ns << endl;
    
    s = 0;
    ns = 0;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "PoliceStation")
            for(int j = 0; j < buildings[i]->getEmployeesSize(); j++)
            {
                s += buildings[i]->getEmployee(j).mSalary;
                ns++;
            }
    }
    cout << "Average salary for cops: ";
    if(s == 0 && ns == 0) cout << "0" << endl;
    else cout << (double) s / ns << endl;
    
    s = 0;
    ns = 0;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "CityHall" && Person() < buildings[i]->getCoordinator())
        {
            s += buildings[i]->getCoordinator().mSalary;
            ns++;
        }
    }
    cout << "Average salary for mayors: ";
    if(s == 0 && ns == 0) cout << "0" << endl;
    else cout << (double) s / ns << endl;
    
    s = 0;
    ns = 0;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "CityHall")
            for(int j = 0; j < buildings[i]->getCitizensSize(); j++)
            {
                s += buildings[i]->getCitizen(j).mSalary;
                ns++;
            }
    }
    cout << "Average salary for city hall employees: ";
    if(s == 0 && ns == 0) cout << "0" << endl;
    else cout << (double) s / ns << endl;
    
    s = 0;
    ns = 0;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "PoliceStation")
            for(int j = 0; j < buildings[i]->getCitizensSize(); j++)
            {
                s += buildings[i]->getCitizen(j).mAge;
                ns++;
            }
    }
    cout << "Average age of busted in police stations: ";
    if(s == 0 && ns == 0) cout << "0" << endl;
    else cout << (double) s / ns << endl;
    
    for(int i = 0; i < buildings.size(); i++)
    {
        if(buildings[i]->getType() == "House")
        {
            s = buildings[i]->getCitizensSize();
            if(Person() < buildings[i]->getCoordinator()) s++;
            cout << "Number of people in House " << buildings[i]->getBuildingName() << ": " << s << endl;
        }
        if(buildings[i]->getType() == "Block")
        {
            s = 0;
            for(int j = 0; j < buildings[i]->getCitizensSize(); j++)
            {
                if(Person() < buildings[i]->getCitizen(j)) s++;
            }
            if(Person() < buildings[i]->getCoordinator()) s++;
            cout << "Number of people in Block " << buildings[i]->getBuildingName() << ": " << s << endl;
        }
    }
    
    vector<Person> adminicasa;
    vector<Person> adminibloc;
    for(int i = 0; i < buildings.size(); i++)
    {
        if(Person() < buildings[i]->getCoordinator() && buildings[i]->getType() == "House")
            adminicasa.push_back(buildings[i]->getCoordinator());
        if(Person() < buildings[i]->getCoordinator() && buildings[i]->getType() == "Block")
            adminibloc.push_back(buildings[i]->getCoordinator());
    }
    cout << "Administrators of house and block:";
    int ok = 0;
    for(int i = 0; i < adminicasa.size(); i++)
    for(int j = 0; j < adminibloc.size(); j++)
    {
        if(adminicasa[i] == adminibloc[j])
        {
            ok = 1;
            cout << " " << adminicasa[i].mName;
        }
    }
    if(ok == 0) cout << " Nobody";
    return 0;
}
