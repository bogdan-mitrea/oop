//În noua aplicație web pe care ați dezvoltat-o este necesară introducerea unor elemente 
//suplimentare de securitate. Pentru asta veți dezvolta o bibliotecă de Password Policies. 
//Aceste politici de parolă sunt configurate de fiecare client care folosește biblioteca 
//voastră și apoi fiecare parola setată de utilizatori este verificată contra acestor reguli.

#include <bits/stdc++.h>

using namespace std;

class Policy
{
protected:
    bool isChecked = 1;
public:
    virtual void check(const string& pass) = 0;
    bool getCheck() const
    {
        return isChecked;
    }
};

class LengthPolicy : public Policy
{
    uint16_t minLength;
    uint16_t maxLength;
public:
    LengthPolicy(uint16_t min) : minLength(min), maxLength(255) {}
    LengthPolicy(uint16_t min, uint16_t max) : minLength(min), maxLength(max) {}
    void check(const string& pass)
    {
        if(minLength <= pass.length() && pass.length() <= maxLength) isChecked = 1;
        else isChecked = 0;
    }
};

class ClassPolicy : public Policy
{
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t min) : minClassCount(min) {}
    void check(const string& pass)
    {
        isChecked = 0;
        int q = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
        for(int i = 0; i < pass.length(); i++)
        {
            if(pass[i] >= 'a' && pass[i] <= 'z') t1++;
            if(pass[i] >= 'A' && pass[i] <= 'Z') t2++;
            if(isdigit(pass[i])) t3++;
            if(pass[i] < '0' || (pass[i] > '9' && pass[i] < 'A') || (pass[i] > 'Z' && pass[i] < 'a')
            || pass[i] > 'z') t4++;
        }
        if(t1 > 0) q++;
        if(t2 > 0) q++;
        if(t3 > 0) q++;
        if(t4 > 0) q++;
        if(q >= minClassCount) isChecked = 1;
    }
};

class IncludePolicy : public Policy
{
    char characterType;
public:
    IncludePolicy(char ch) : characterType(ch) {}
    void check(const string& pass)
    {
        isChecked = 0;
        if(characterType == 'a')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if('a' <= pass[i] && pass[i] <= 'z')
                {
                    isChecked = 1;
                    break;
                }
            }
        }
        if(characterType == 'A')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if('A' <= pass[i] && pass[i] <= 'Z')
                {
                    isChecked = 1;
                    break;
                }
            }
        }
        if(characterType == '0')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if(isdigit(pass[i]))
                {
                    isChecked = 1;
                    break;
                }
            }
        }
        if(characterType == '$')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if(pass[i] < '0' || (pass[i] > '9' && pass[i] < 'A') || (pass[i] > 'Z' && pass[i] < 'a')
                    || pass[i] > 'z')
                {
                    isChecked = 1;
                    break;
                }
            }
        }
    }
};

class NotIncludePolicy : public Policy
{
    char characterType;
public:
    NotIncludePolicy(char ch) : characterType(ch) {}
    void check(const string& pass)
    {
        isChecked = 1;
        if(characterType == 'a')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if('a' <= pass[i] && pass[i] <= 'z')
                {
                    isChecked = 0;
                    break;
                }
            }
        }
        if(characterType == 'A')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if('A' <= pass[i] && pass[i] <= 'Z')
                {
                    isChecked = 0;
                    break;
                }
            }
        }
        if(characterType == '0')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if(isdigit(pass[i]))
                {
                    isChecked = 0;
                    break;
                }
            }
        }
        if(characterType == '$')
        {
            for(int i = 0; i < pass.length(); i++)
            {
                if(pass[i] < '0' || (pass[i] > '9' && pass[i] < 'A') || (pass[i] > 'Z' && pass[i] < 'a')
                    || pass[i] > 'z')
                {
                    isChecked = 0;
                    break;
                }
            }
        }
    }
};

class RepetitionPolicy : public Policy
{
    uint16_t maxCount;
public:
    RepetitionPolicy(char mx) : maxCount(mx) {}
    void check(const string& pass)
    {
        isChecked = 1;
        int ct = 1;
        int maxct = 1;
        for(int i = 1; i < pass.length(); i++)
        {
            if(pass[i] == pass[i-1]) ct++;
            else {
                if(ct > maxct) maxct = ct;
                ct = 1;
            }
        }
        if(maxct > maxCount) isChecked = 0;
    }
};

class ConsecutivePolicy : public Policy
{
    uint16_t maxCount;
public:
    ConsecutivePolicy(char mx) : maxCount(mx) {}
    void check(const string& pass)
    {
        isChecked = 1;
        int ct = 1;
        int maxct = 1;
        for(int i = 1; i < pass.length(); i++)
        {
            if(pass[i] == pass[i-1] + 1) ct++;
            else {
                if(ct > maxct) maxct = ct;
                ct = 1;
            }
        }
        if(maxct > maxCount) isChecked = 0;
    }
};

string checkPassword(string pass, vector<Policy*> policies)
{
    for(int i = 0; i < policies.size(); i++)
    {
        policies[i]->check(pass);
        if(policies[i]->getCheck() == 0) return "NOK";
    }
    return "OK";
}

int main()
{
    int n;
    cin >> n;
    vector<Policy*> policies;
    string condition;
    uint16_t n1, n2;
    for(int i = 0; i < n ; i++)
    {
        cin >> condition;
        if(condition == "include")
        {
            char chr;
            cin >> chr;
            policies.push_back(new IncludePolicy(chr));
        }
        if(condition == "ninclude")
        {
            char chr;
            cin >> chr;
            policies.push_back(new NotIncludePolicy(chr));
        }
        if(condition == "length")
        {
            int count = scanf(" %hu %hu", &n1, &n2);
            if(count == 2) policies.push_back(new LengthPolicy(n1, n2));
            if(count == 1) policies.push_back(new LengthPolicy(n1));
        }
        if(condition == "class")
        {
            cin >> n1;
            policies.push_back(new ClassPolicy(n1));
        }
        if(condition == "repetition")
        {
            cin >> n1;
            policies.push_back(new RepetitionPolicy(n1));
        }
        if(condition == "consecutive")
        {
            cin >> n1;
            policies.push_back(new ConsecutivePolicy(n1));
        }
    }
    string password;
    while(cin >> password)
    {
        cout << checkPassword(password, policies) << endl;
    }
    return 0;
}