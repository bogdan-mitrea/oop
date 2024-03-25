/*
Aţi fost aleşi de către un car dealer pentru a organiza eficient mașinile si consumul acestora de combustibil, in cadrul unui proiect de cercetare pentru creșterea eficienței vehiculelor și scăderea poluării.

Există mai multe tipuri de mașini, si anume: mașini cu ardere internă(ce pot fi acelea ce funcționează cu benzină și cele ce funcționează pe motorină), cele hibride si cele full electrice.
*/

#include <bits/stdc++.h>
#include <regex>

using namespace std;

class Car
{
protected:
    string mBrand;
    string mLicensePlate;
    uint16_t mYearOfFabrication;
    double mAverageConsumption;
    uint32_t mNumberOfKilometers;
public:
    Car(string b, string lp, uint16_t yof, double ac, uint32_t nok) : mBrand(b), mLicensePlate(lp), mYearOfFabrication(yof),
    mAverageConsumption(ac), mNumberOfKilometers(nok) {}
    string getBrand() const
    {
        return mBrand;
    }
    string getLicensePlate() const
    {
        return mLicensePlate;
    }
    uint16_t getYearOfFabrication() const
    {
        return mYearOfFabrication;
    }
    double getAverageConsumption() const
    {
        return mAverageConsumption;
    }
    uint32_t getNumberOfKilometers() const
    {
        return mNumberOfKilometers;
    }
    virtual double getFuelConsumption() const = 0;
    virtual double getFuelCost() const = 0;
    virtual string getType() const = 0;
    bool operator < (const Car& c)
    {
        if(mYearOfFabrication < c.getYearOfFabrication()) return true;
        if(mYearOfFabrication == c.getYearOfFabrication() && mNumberOfKilometers > c.getNumberOfKilometers()) return true;
        if(mYearOfFabrication == c.getYearOfFabrication() && mNumberOfKilometers == c.getNumberOfKilometers() &&
        mAverageConsumption < c.getAverageConsumption()) return true;
        return false;
    }
};

class PetrolCar : public Car
{
public:
    PetrolCar(string b, string lp, uint16_t yof, double ac, uint32_t nok) : Car(b, lp, yof, ac, nok) {}
    double getFuelConsumption() const
    {
        return (0.879 * mAverageConsumption * mNumberOfKilometers) / 100;
    }
    double getFuelCost() const
    {
        return 4.5 * this->getFuelConsumption();
    }
    string getType() const
    {
        return "benzina";
    }
};

class DieselCar : public Car
{
public:
    DieselCar(string b, string lp, uint16_t yof, double ac, uint32_t nok) : Car(b, lp, yof, ac, nok) {}
    double getFuelConsumption() const
    {
        return (0.789 * mAverageConsumption * mNumberOfKilometers) / 100;
    }
    double getFuelCost() const
    {
        return 4.8 * this->getFuelConsumption();
    }
    string getType() const
    {
        return "diesel";
    }
};

class HybridCar : public Car
{
public:
    HybridCar(string b, string lp, uint16_t yof, double ac, uint32_t nok) : Car(b, lp, yof, ac, nok) {}
    double getFuelConsumption() const
    {
        return (mAverageConsumption * mNumberOfKilometers - 0.124 * mNumberOfKilometers) / 100;
    }
    double getFuelCost() const
    {
        return 4.5 * this->getFuelConsumption();
    }
    string getType() const
    {
        return "hibrid";
    }
};

class ElectricCar : public Car
{
public:
    ElectricCar(string b, string lp, uint16_t yof, double ac, uint32_t nok) : Car(b, lp, yof, ac, nok) {}
    double getFuelConsumption() const
    {
        return 0;
    }
    double getFuelCost() const
    {
        return 0;
    }
    string getType() const
    {
        return "electrica";
    }
};

int main()
{
    int n;
    cin >> n;
    string brand, nr_inm, tip_comb;
    uint16_t an;
    double consum;
    uint32_t nr_km;
    vector<Car*> cars;
    for(int i = 0; i < n; i++)
    {
        cin >> brand >> tip_comb >> nr_inm >> an >> consum >> nr_km;
        if(tip_comb == "benzina") cars.push_back(new PetrolCar(brand, nr_inm, an, consum, nr_km));
        if(tip_comb == "diesel") cars.push_back(new DieselCar(brand, nr_inm, an, consum, nr_km));
        if(tip_comb == "hibrid") cars.push_back(new HybridCar(brand, nr_inm, an, consum, nr_km));
        if(tip_comb == "electrica") cars.push_back(new ElectricCar(brand, nr_inm, an, consum, nr_km));
    }
    char cerinta;
    cin >> cerinta;
    if(cerinta == 'a')
    {
        for(int i = 0; i < cars.size() - 1; i++)
        for(int j = i + 1; j < cars.size(); j++)
        {
            if(*cars[i] < *cars[j]) swap(cars[i], cars[j]);
        }
        for(int i = 0; i < cars.size(); i++)
        {
            cout << "Masina " << cars[i]->getBrand() << " cu numarul de inmatriculare " << cars[i]->getLicensePlate() << " a parcurs "
            << cars[i]->getNumberOfKilometers() << "km si a consumat ";
            printf("%.3lf litri.\n", cars[i]->getFuelConsumption());
        }
    }
    if(cerinta == 'b')
    {
        double s = 0;
        for(int i = 0; i < cars.size(); i++)
        {
            s += cars[i]->getFuelCost();
        }
        printf("%.2lf", s);
    }
    if(cerinta == 'c')
    {
        while(cin >> brand >> tip_comb >> nr_inm >> an >> consum >> nr_km)
        {
            if(tip_comb == "benzina") cars.push_back(new PetrolCar(brand, nr_inm, an, consum, nr_km));
            if(tip_comb == "diesel") cars.push_back(new DieselCar(brand, nr_inm, an, consum, nr_km));
            if(tip_comb == "hibrid") cars.push_back(new HybridCar(brand, nr_inm, an, consum, nr_km));
            if(tip_comb == "electrica") cars.push_back(new ElectricCar(brand, nr_inm, an, consum, nr_km));
        }
        uint32_t distanta = 0;
        double consum_med = 0;
        for(int i = 0; i < cars.size(); i++)
        {
            distanta += cars[i]->getNumberOfKilometers();
            consum_med += cars[i]->getAverageConsumption();
        }
        consum_med /= cars.size();
        printf("%u km\n%.2lf L/100km", distanta, consum_med);
    }
    if(cerinta == 'd')
    {
        int nrb = 0, nrd = 0, nrh = 0, nre = 0;
        for(int i = 0; i < cars.size(); i++)
        {
            if(cars[i]->getType() == "benzina") nrb++;
            if(cars[i]->getType() == "diesel") nrd++;
            if(cars[i]->getType() == "hibrid") nrh++;
            if(cars[i]->getType() == "electrica") nre++;
        }
        printf("benzina -> %d\ndiesel -> %d\nelectrica -> %d\nhibrid -> %d", nrb, nrd, nre, nrh);
    }
    if(cerinta == 'e')
    {
        for(int i = 0; i < cars.size(); i++)
        {
            string numar = cars[i]->getLicensePlate();
            int l = numar.length();
            bool ok = 1;
            if(isupper(numar[0]) == 0 || isupper(numar[l-1]) == 0 || isupper(numar[l-2]) == 0 || isupper(numar[l-3]) == 0) ok = 0;
            if(isupper(numar[1]))
            {
                if(isdigit(numar[2]) == 0 || isdigit(numar[3]) == 0) ok = 0;
                if(isupper(numar[4]) && l != 7) ok = 0;
                if(isdigit(numar[4]) && l != 8) ok = 0;
            }
            if(isdigit(numar[1]))
            {
                if(isdigit(numar[2]) == 0) ok = 0;
                if(isupper(numar[3]) && l != 6) ok = 0;
                if(isdigit(numar[3]) && l != 7) ok = 0;
            }
            if(ok == 0) cout << cars[i]->getLicensePlate() << ": numar de inmatriculare invalid" << endl;
        }
    }
    return 0;
}