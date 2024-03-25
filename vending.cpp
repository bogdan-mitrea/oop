#include <bits/stdc++.h>

using namespace std;

class eroare_aparat : public exception
{
public:
    const char * what() const noexcept
    {
        return "Aparatul necesita revizie!";
    }
};

class produs
{
public:
    string nume_produs;
    uint16_t pret;
    uint16_t cantitate;
    produs(string np, uint16_t pr, uint16_t c) : nume_produs(np), pret(pr), cantitate(c) {}
};

class aparat_vending
{
protected:
    string tip;
    uint16_t serie;
    uint16_t suma_in_bancnotiera;
    uint16_t capacitate_bancnotiera;
    uint16_t suma_totala;
public:
    aparat_vending(string t, uint16_t s, uint16_t cb) : tip(t), serie(s), capacitate_bancnotiera(cb), suma_in_bancnotiera(0), suma_totala(0) {}
    bool check_space(uint16_t pr)
    {
        if(capacitate_bancnotiera - suma_in_bancnotiera >= pr) return true;
        return false;
    }
    uint16_t getSerie() const
    {
        return serie;
    }
    uint16_t getSumaTotala() const
    {
        return suma_totala;
    }
    virtual void CumparareProdus(const string& nume) = 0;
    virtual void aprovizionare() = 0;
};

class aparat_cafea : public aparat_vending
{
private:
    uint16_t boabe_cafea;
    uint16_t lapte;
    uint16_t plicuri_ceai;
public:
    aparat_cafea(uint16_t s, uint16_t cb) : aparat_vending("aparat_cafea", s, cb), boabe_cafea(100), lapte(1000), plicuri_ceai(20) {}
    void CumparareProdus(const string& nume)
    {
        if(nume == "cafea")
        {
            if(boabe_cafea < 10 || this->check_space(5) == false) throw eroare_aparat();
            if(boabe_cafea >= 10 && this->check_space(5) == true)
            {
                suma_in_bancnotiera += 5;
                boabe_cafea -= 10;
            }
        }
        if(nume == "cappuccino")
        {
            if(boabe_cafea < 7 || lapte < 100 || check_space(8) == false) throw eroare_aparat();
            if(boabe_cafea >= 7 && lapte >= 100 && check_space(8) == true)
            {
                suma_in_bancnotiera += 8;
                boabe_cafea -= 7;
                lapte -= 100;
            }
        }
        if(nume == "ceai")
        {
            if(plicuri_ceai < 1 || check_space(4) == false) throw eroare_aparat();
            if(plicuri_ceai >= 1 && check_space(4) == true)
            {
                suma_in_bancnotiera += 4;
                plicuri_ceai--;
            }
        }
    }
    void aprovizionare()
    {
        boabe_cafea = 100;
        lapte = 1000;
        plicuri_ceai = 20;
        suma_totala += suma_in_bancnotiera;
        suma_in_bancnotiera = 0;
        
    }
};

class aparat_snack : public aparat_vending
{
private:
    vector<produs> produse;
public:
    aparat_snack(uint16_t s, uint16_t cb, vector<produs> p) : aparat_vending("aparat_snack", s, cb), produse(p) {}
    void CumparareProdus(const string& nume)
    {
        bool produs_gasit = false;
        for(int i = 0; i < produse.size(); i++)
        {
            if(nume == produse[i].nume_produs)
            {
                produs_gasit = true;
                if(produse[i].cantitate == 0 || check_space(produse[i].pret) == false) throw eroare_aparat();
                else 
                {
                    suma_in_bancnotiera += produse[i].pret;
                    produse[i].cantitate--;
                }
            }
        }
        if(produs_gasit == false) throw eroare_aparat();
    }
    void aprovizionare()
    {
        for(int i = 0; i < produse.size(); i++)
        {
            produse[i].cantitate += 4;
        }
        suma_totala += suma_in_bancnotiera;
        suma_in_bancnotiera = 0;
    }
};

int main()
{
    int n;
    cin >> n;
    string type;
    uint16_t serial, capacity;
    vector<aparat_vending*> aparate;
    for(int i = 0; i < n; i++)
    {
        cin >> type >> serial >> capacity;
        if(type == "aparat_cafea") aparate.push_back(new aparat_cafea(serial, capacity));
        if(type == "aparat_snack")
        {
            int nr_prod;
            cin >> nr_prod;
            string nume_prod;
            uint16_t pret, cantit;
            vector<produs> products;
            for(int i = 0; i < nr_prod; i++)
            {
                cin >> nume_prod >> pret >> cantit;
                products.push_back(produs(nume_prod, pret, cantit));
            }
            aparate.push_back(new aparat_snack(serial, capacity, products));
        }
    }
    string command, name;
    uint16_t sr;
    int cumpara_count = 0;
    while(cin >> command)
    {
        if(command == "cumpara")
        {
            cumpara_count++;
            cin >> sr >> name;
            for(int i = 0; i < n; i++)
            {
                if(sr == aparate[i]->getSerie()) 
                {
                    try 
                    {
                        aparate[i]->CumparareProdus(name);
                    }
                    catch(eroare_aparat ea)
                    {
                        cout << ea.what();
                        return 0;
                    }
                    break;
                }
            }
        }
        if(command == "aprovizioneaza" || command == "aprovizionare")
        {
            cin >> sr;
            for(int i = 0; i < n; i++)
            {
                if(sr == aparate[i]->getSerie()) 
                {
                    aparate[i]->aprovizionare();
                    break;
                }
            }
        }
    }
    uint16_t maxbani = 0, serie_max;
    for(int i = 0; i < n; i++)
    {
        if(aparate[i]->getSumaTotala() > maxbani)
        {
            maxbani = aparate[i]->getSumaTotala();
            serie_max = aparate[i]->getSerie();
        }
    }
    if(cumpara_count == 0)
    {
        cout << "Nu s-au cumparat produse!";
        return 0;
    }
    cout << serie_max;
    return 0;
}