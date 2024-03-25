//Pentru a ajuta dezvoltarea unui motor de calcul algebric, vi se cere să scrieți un program care să implementeze operații de calcul cu polinoame.


#include <bits/stdc++.h>

using namespace std;

class Polynomial
{
protected:
    vector<double> mCoeffs;
    uint32_t mDegree;
public:
    Polynomial(const vector<double>& vd) : mDegree(vd.size()-1), mCoeffs(vd) {}
    Polynomial(uint32_t gr) : mDegree(gr), mCoeffs(gr+1,0) {}
    Polynomial derivate() const
    {
        Polynomial P(mCoeffs);
        P.mDegree = this->mDegree;
        uint32_t grad = mDegree;
        for(int i = 0; i < mCoeffs.size(); i++)
        {
            P.mCoeffs[i] *= grad;
            grad--;
        }
        P.mDegree--;
        return P;
    }
    double calculate(double value) const
    {
        double y = 0;
        uint32_t grad = mDegree;
        for(int i = 0; i < mCoeffs.size(); i++)
        {
            y += mCoeffs[i] * pow(value, grad);
            grad--;
        }
        return y;
    }
    complex<double> calculate(const complex<double>& value) const
    {
        complex<double> y = 0;
        uint32_t grad = mDegree;
        for(int i = 0; i < mCoeffs.size(); i++)
        {
            y += mCoeffs[i] * pow(value, grad);
            grad--;
        }
        return y;
    }
    uint32_t getDegree() const
    {
        return mDegree;
    }
    double& operator[](uint32_t index)
    {
        double *p = &mCoeffs[index];
        return *p;
    }
    double operator[](uint32_t index) const
    {
        return mCoeffs[index];
    }
    Polynomial operator+(const Polynomial& rhs) const
    {
        uint32_t maxDeg = max(mDegree, rhs.mDegree);
        if(maxDeg == mDegree)
        {
            Polynomial S = *this;
            for(int i = mDegree - rhs.mDegree; i < mDegree + 1; i++)
            {
                S.mCoeffs[i] += rhs.mCoeffs[i - (mDegree - rhs.mDegree)];
            }
            return S;
        }
        Polynomial S = rhs;
        for(int i = rhs.mDegree - mDegree; i < rhs.mDegree + 1; i++)
        {
            S.mCoeffs[i] += mCoeffs[i - (rhs.mDegree - mDegree)];
        }
        return S;
    }
    Polynomial operator*(const Polynomial& rhs) const
    {
        uint32_t newDeg = mDegree + rhs.mDegree;
        vector<double> v(newDeg + 1, 0);
        for(int i = 0; i < mDegree + 1; i++)
        for(int j = 0; j < rhs.mDegree + 1; j++)
        {
            v[i + j] += mCoeffs[i] * rhs.mCoeffs[j];
        }
        return Polynomial(v);
    }
    Polynomial& operator*=(const double constant)
    {
        for(int i = 0; i < mCoeffs.size(); i++)
        {
            mCoeffs[i] *= constant;
        }
        return *this;
    }
    Polynomial& operator/=(const double constant)
    {
        for(int i = 0; i < mCoeffs.size(); i++)
        {
            mCoeffs[i] /= constant;
        }
        return *this;
    }
    virtual vector<complex<double>> roots() const
    {
        printf("Implementation for method roots for polynomials with degree = %u is not available.\n", 
        mDegree);
        vector<complex<double>> v;
        v.clear();
        return v;
    }
};

class ZeroDegreePolynomial : public Polynomial
{
public:
    ZeroDegreePolynomial(const vector<double>& vd) : Polynomial(vd) {}
    vector<complex<double>> roots() const
    {
        printf("Polynomials with degree 0 doesn't have roots.\n");
        vector<complex<double>> v;
        v.clear();
        return v;
    }
};

class FirstDegreePolynomial : public Polynomial
{
public:
    FirstDegreePolynomial(const vector<double>& vd) : Polynomial(vd) {}
    vector<complex<double>> roots() const
    {
        vector<complex<double>> v;
        v.push_back(-mCoeffs[1] / mCoeffs[0]);
        return v;
    }
};

class SecondDegreePolynomial : public Polynomial
{
public:
    SecondDegreePolynomial(const vector<double>& vd) : Polynomial(vd) {}
    vector<complex<double>> roots() const
    {
        complex<double> delta = mCoeffs[1] * mCoeffs[1] - 4 * mCoeffs[0] * mCoeffs[2];
        complex<double> root1 = (-mCoeffs[1] + sqrt(delta)) / (2 * mCoeffs[0]);
        complex<double> root2 = (-mCoeffs[1] - sqrt(delta)) / (2 * mCoeffs[0]);
        vector<complex<double>> v;
        v.push_back(root1);
        v.push_back(root2);
        return v;
    }
};

char semn(double val)
{
    if(val < 0) return '-';
    return '+';
}

int main()
{
    int n;
    cin >> n;
    vector<Polynomial*> polynomials;
    scanf(" ");
    for(int i = 0; i < n; i++)
    {
        double x;
        vector<double> v;
        string s;
        getline(cin, s);
        stringstream ss(s);
        while(ss >> x)
        {
            v.push_back(x);
        }
        if(v.size() == 1) polynomials.push_back(new ZeroDegreePolynomial(v));
        if(v.size() == 2) polynomials.push_back(new FirstDegreePolynomial(v));
        if(v.size() == 3) polynomials.push_back(new SecondDegreePolynomial(v));
        if(v.size() > 3) polynomials.push_back(new Polynomial(v));
    }
    string command;
    while(cin >> command)
    {
        if(command == "roots")
        {
            int index;
            cin >> index;
            if(polynomials[index]->getDegree() == 1 || polynomials[index]->getDegree() == 2)
                printf("Roots of polynomial with index %d are:\n", index);
            if(polynomials[index]->getDegree() == 1)
            {
                double real = (polynomials[index]->roots())[0].real();
                double im = (polynomials[index]->roots())[0].imag();
                cout << "x1 = " << fixed << setprecision(3) << real;
                if(im != 0) cout << semn(im) << fixed << setprecision(3) << abs(im) << "*i";
            }
            if(polynomials[index]->getDegree() == 2)
            {
                double real1 = (polynomials[index]->roots())[0].real();
                double im1 = (polynomials[index]->roots())[0].imag();
                double real2 = (polynomials[index]->roots())[1].real();
                double im2 = (polynomials[index]->roots())[1].imag();
                cout << "x1 = " << fixed << setprecision(3) << real1;
                if(im1 != 0) cout << semn(im1) << fixed << setprecision(3) << abs(im1) << "*i";
                cout << endl;
                cout << "x2 = " << fixed << setprecision(3) << real2;
                if(im2 != 0) cout << semn(im2) << fixed << setprecision(3) << abs(im2) << "*i";
            }
            else polynomials[index]->roots();
            cout << endl;
        }
        if(command == "derivate")
        {
            int index, index1;
            cin >> index >> index1;
            *polynomials[index] = polynomials[index1]->derivate();
        }
        if(command == "calculate")
        {
            int index;
            double val1, val2;
            int d = scanf("%d %lf %lf", &index, &val1, &val2);
            if(d == 2)
                printf("Polynomial %d evaluated in %lf is: %lf", index, val1, polynomials[index]->calculate(val1));
            if(d == 3)
            {
                complex<double> val(val1, val2);
                printf("Polynomial %d evaluated in ", index);
                cout << val << " is: " << polynomials[index]->calculate(val);
            }
        }
        if(command == "add")
        {
            int index, index1, index2;
            cin >> index >> index1 >> index2;
            *polynomials[index] = *polynomials[index1] + *polynomials[index2];
        }
        if(command == "mult")
        {
            double index, val1, val2;
            int d = scanf("%lf %lf %lf", &index, &val1, &val2);
            if(d == 2) *polynomials[(int) index] *= val1;
            if(d == 3) *polynomials[(int) index] = (*polynomials[(int) val1]) * (*polynomials[(int) val2]);
        }
        if(command == "div")
        {
            int index;
            double val;
            cin >> index >> val;
            *polynomials[index] /= val;
        }
    }
    for(int i = 0; i < n; i++)
    {
        printf("%.3lf", (*polynomials[i])[0]);
        cout << "*x^" << polynomials[i]->getDegree();
        for(int j = 1; j < polynomials[i]->getDegree() + 1; j++)
        {
            cout << semn((*polynomials[i])[j]);
            printf("%.3lf", abs((*polynomials[i])[j]));
            cout << "*x^" << polynomials[i]->getDegree() - j;
        }
        cout << endl;
    }
    return 0;
}