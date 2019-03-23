#ifndef CODINGPRACTICE_COMPLEX_H
#define CODINGPRACTICE_COMPLEX_H
#include <ostream>
#include <istream>

namespace exercises
{


class Complex;

std::ostream& operator<<(std::ostream&, const Complex&);
std::istream& operator>>(std::istream, Complex&);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

//return const Complex to prohibit operations such as a + b += c;
const Complex operator+(const Complex& lhs, const Complex& rhs);
const Complex operator-(const Complex& lhs, const Complex& rhs);
const Complex operator*(const Complex& lhs, const Complex& rhs);
const Complex operator/(const Complex& lhs, const Complex& rhs);

class Complex
{
public:

    Complex(double real = 0, double im = 0);

    ~Complex() = default;
    Complex(const Complex&) = default;
    Complex& operator=(const Complex&) = default;
    Complex& operator=(Complex&&) = default;
    Complex(Complex&&) = default;

    double GetReal() const;
    double GetIm() const;

    void SetReal(double real);
    void SetIm(double im);

    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);
    Complex& operator*=(const Complex& rhs);
    Complex& operator/=(const Complex& rhs);
private:
    double mReal;
    double mIm;
};

}//exercises
#endif //CODINGPRACTICE_COMPLEX_H
