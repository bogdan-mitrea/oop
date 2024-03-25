#include <bits/stdc++.h>

using namespace std;

class Person
{
public:
    string mName;
    string mProducts;
    double mSalary;
    Person() : mProducts("None"), mSalary(0), mName("") {}
    Person(string name, string prod, double sal) : mProducts(prod), mSalary(sal), mName(name) {}
    bool operator == (const Person& p) const
    {
        return mName == p.mName && mSalary == p.mSalary;
    }
    bool operator < (const Person& p) const
    {
        return mName < p.mName;
    }
};

class Product
{
public:
    string mName;
    string mType;
    double mPrice;
    Product() : mType("None"), mPrice(0), mName("") {}
    Product(string name, string type, double price) : mType(type), mPrice(price), mName(name) {}
    bool operator == (const Product& p) const
    {
        return mName == p.mName && mPrice == p.mPrice;
    }
    bool operator < (const Product& p) const
    {
        return mName < p.mName;
    }
};

class Store
{
protected:
    string mStoreName;
    string mType;
    vector<Person> mBuyers;
    vector<Product> mProducts;
public:
    Store(string name, string type) : mType(type), mStoreName(name) {}
    virtual void add(const Person& p) = 0;
    virtual void remove(const Person& p) = 0;
    virtual void addProduct(const Product& pr) = 0;
    virtual void removeProduct(const Product& pr) = 0;
    virtual Store* operator + () = 0;
    virtual Store* operator - (const Person& p) = 0;
    string getStoreName() const
    {
        return mStoreName;
    }
    string getType() const
    {
        return mType;
    }
    uint16_t getBuyersSize() const
    {
        return mBuyers.size();
    }
    uint16_t getProductsSize() const
    {
        return mProducts.size();
    }
    Person getBuyers(uint16_t i) const
    {
        return mBuyers[i];
    }
    Product getProducts(uint16_t i) const
    {
        return mProducts[i];
    }
};

class MiniMarket : public Store
{
    MiniMarket(string name) : Store(name, "MiniMarket")
    {
        mBuyers.clear();
        mProducts.clear();
    }
    Store* operator + ()
    {
        return this;
    }
    Store* operator - (const Person& p)
    {
        return this;
    }
    void add(const Person& p)
    {
        mBuyers.push_back(p);
    }
    void remove(const Person& p)
    {
        for(int i = 0; i < mBuyers.size(); i++)
        {
            if(mBuyers[i] == p)
            {
                mBuyers.erase(mBuyers.begin() + i);
                break;
            }
        }
    }
    void addProduct(const Product& pr)
    {
        mProducts.push_back(pr);
    }
    void removeProduct(const Product& pr)
    {
        for(int i = 0; i < mProducts.size(); i++)
        {
            if(mProducts[i] == pr)
            {
                mProducts.erase(mProducts.begin() + i);
                break;
            }
        }
    }
};

class Market : public Store
{
    Market(string name) : Store(name, "Market")
    {
        mBuyers.clear();
        mProducts.clear();
    }
    Store* operator + ()
    {
        return this;
    }
    Store* operator - (const Person& p)
    {
        return this;
    }
    void add(const Person& p)
    {
        mBuyers.push_back(p);
    }
    void remove(const Person& p)
    {
        for(int i = 0; i < mBuyers.size(); i++)
        {
            if(mBuyers[i] == p)
            {
                mBuyers.erase(mBuyers.begin() + i);
                break;
            }
        }
    }
    void addProduct(const Product& pr)
    {
        mProducts.push_back(pr);
    }
    void removeProduct(const Product& pr)
    {
        for(int i = 0; i < mProducts.size(); i++)
        {
            if(mProducts[i] == pr)
            {
                mProducts.erase(mProducts.begin() + i);
                break;
            }
        }
    }
};

class SuperMarket : public Store
{
    SuperMarket(string name) : Store(name, "SuperMarket")
    {
        mBuyers.clear();
        mProducts.clear();
    }
    Store* operator + ()
    {
        return this;
    }
    Store* operator - (const Person& p)
    {
        return this;
    }
    void add(const Person& p)
    {
        mBuyers.push_back(p);
    }
    void remove(const Person& p)
    {
        for(int i = 0; i < mBuyers.size(); i++)
        {
            if(mBuyers[i] == p)
            {
                mBuyers.erase(mBuyers.begin() + i);
                break;
            }
        }
    }
    void addProduct(const Product& pr)
    {
        mProducts.push_back(pr);
    }
    void removeProduct(const Product& pr)
    {
        for(int i = 0; i < mProducts.size(); i++)
        {
            if(mProducts[i] == pr)
            {
                mProducts.erase(mProducts.begin() + i);
                break;
            }
        }
    }
};

class Mall : public Store
{
    Mall(string name) : Store(name, "Mall")
    {
        mBuyers.clear();
        mProducts.clear();
    }
    Store* operator + ()
    {
        return this;
    }
    Store* operator - (const Person& p)
    {
        return this;
    }
    void add(const Person& p)
    {
        mBuyers.push_back(p);
    }
    void remove(const Person& p)
    {
        for(int i = 0; i < mBuyers.size(); i++)
        {
            if(mBuyers[i] == p)
            {
                mBuyers.erase(mBuyers.begin() + i);
                break;
            }
        }
    }
    void addProduct(const Product& pr)
    {
        mProducts.push_back(pr);
    }
    void removeProduct(const Product& pr)
    {
        for(int i = 0; i < mProducts.size(); i++)
        {
            if(mProducts[i] == pr)
            {
                mProducts.erase(mProducts.begin() + i);
                break;
            }
        }
    }
};

int main()
{
    string command, keyword, nume, magazin;
    double salariu;
    vector<Store*> stores;
    while(cin >> command)
    {
        cin >> keyword;
        if(command == "add")
        {
            if(keyword == "MiniMarket")
            {
                cin >> magazin;
                stores.push_back(new MiniMarket(magazin));
            }
            if(keyword == "Market")
            {
                cin >> magazin;
                stores.push_back(new Market(magazin));
            }
            if(keyword == "SuperMarket")
            {
                cin >> magazin;
                stores.push_back(new SuperMarket(magazin));
            }
            if(keyword == "Mall")
            {
                cin >> magazin;
                stores.push_back(new Mall(magazin));
            }
        //de aici
            if(keyword == "buyer")
            {
                cin >> nume >> produs >> salariu;
                Person p(nume, produs, salariu);
                for(int i = 0; i < stores.size(); i++)
                {
                    if(stores[i]->getStoreName() == cladire)
                    {
                        stores[i] = *stores[i] + p;
                        break;
                    }
                }
            }
            if(keyword == "product")
            {
                cin >> nume >> produs >> salariu >> cladire;
                Person p(nume, varsta, salariu);
                for(int i = 0; i < stores.size(); i++)
                {
                    if(stores[i]->getBuildingName() == cladire)
                    {
                        stores[i] = *stores[i] + p;
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
    return 0;
}