#include <bits/stdc++.h>

using namespace std;


class NumberFormatException : public exception
{
private:
    string message_;
public:
    const char* what() const noexcept
    {
        return message_.c_str();
    }
    NumberFormatException(const string& str)
    {
        message_ = "Value " + str + " is not a valid number.";
    }
};

class Number
{
public:
    static int64_t stoi(const string& str)
    {
        int found = 0;
        string copy = str;
        while(copy[0] == ' ')
        {
            copy.erase(copy.begin());
        }
        for(int i = 0; i < copy.length(); i++)
        {
            if(i == 0 && (copy[i] == '+' || copy[i] == '-')) continue;
            if(i >= 1 && !isdigit(copy[i])) break;
            if(isdigit(copy[i])) found = 1;
        }
        int64_t s = atol(str.c_str());
        if(s != 0 || found == 1) return s;
        throw NumberFormatException(str);
    }
};

class FileException : public exception
{
protected:
    string message_;
public:
    const char* what() const noexcept
    {
        return message_.c_str();
    }
};

class OpenFileException : public FileException
{
public:
    OpenFileException(const string& name)
    {
        message_ = "Cannot open file " + name + ".";
    }
};

class InputFile : public ifstream
{
public:
    InputFile() {}
    InputFile(const string& name) : ifstream(name)
    {
        if(!this->is_open()) throw OpenFileException(name);
    }
    void open(const string& name)
    {
        this->ifstream::open(name);
        if(!this->is_open()) throw OpenFileException(name);
    }
    ~InputFile()
    {
        if(this->is_open()) this->close();
    }
};

int main()
{
    string filename;
    while(cin >> filename)
    {
        try
        {
            InputFile f(filename);
            f.open(filename);
        }
        catch(FileException exc)
        {
            cout << exc.what() << endl;
            continue;
        }
        InputFile f(filename);
        string line;
        while(getline(f, line))
        {
            try
            {
                cout << Number::stoi(line) << endl;
            }
            catch(NumberFormatException exc)
            {
                cout << exc.what() << endl;
            }
        }
    }
    return 0;
}