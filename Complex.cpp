#include "Complex.h"
namespace exercises
{
Complex::Complex(double real /*= 0*/, double im /*= 0*/) : mReal(real), mIm(im) {}


double Complex::GetReal() const
{
    return mReal;
}
double Complex::GetIm() const
{
    return mIm;
}

void Complex::SetReal(double real)
{
    mReal = real;
}
void Complex::SetIm(double im)
{
    mIm = im;
}

Complex& Complex::operator+=(const Complex& rhs)
{
    mReal += rhs.mReal;
    mIm += rhs.mIm;

    return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
    mReal -= rhs.mReal;
    mIm -= rhs.mIm;

    return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
    //(a + ib)*(c + id) = ac - bd +i(ad + bc)
    double a = mReal;
    double b = mIm;
    double c =rhs.mReal;
    double d =rhs.mIm;

    *this = {a*c - b*d, a*d + b*c};

    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    //(a + ib)       ( a + ib )( c - id )
    //---------- =  -----------------------
    //(c + id)	        ( c^2 + d^2 )

    double a = mReal;
    double b = mIm;
    double c =rhs.mReal;
    double d =rhs.mIm;

    double denom = c*c + d*d;
    *this = {(a*c +b*d)/denom, (b*c-a*d)/denom};

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    return os << "(" << c.GetReal() << ", " <<c.GetIm()<<")";
}

std::istream& operator>>(std::istream& is, Complex& c) //assumes (a,bi) format
{
    char open = 0;
    double a = 0;
    char comma = 0;
    char b = 0;
    char i = 0;
    char close = 0;

    is >> open >> a >> comma >> b >> i >> close;
    if(is && open == '(' && comma == ',' && i == 'i' && close == ')')
    {
        c.SetReal(a);
        c.SetIm(b);
    }
    else{
        is.setstate(std::ios::failbit);
    }

    return is;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
    return lhs.GetReal() == rhs.GetReal() && lhs.GetIm() == lhs.GetIm();
}
bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

const Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex result {lhs};
    return result += rhs;
}

const Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex result {lhs};
    return result -= rhs;
}
const Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex result {lhs};
    return result *= rhs;
}
const Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex result {lhs};
    return result /= rhs;
}

}//namespace exercises

