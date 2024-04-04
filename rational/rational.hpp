#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include "rational.h"

namespace numbers
{
    
    // default constructor.
    rational::rational()
        : _numerator(0), _denominator(1){}

    // one argument constructor.
    rational::rational(int numerator)
        : _numerator(numerator), _denominator(1){}

    // two argument constructor.
    rational::rational(int numerator, int denominator)
        : _numerator(numerator), _denominator(denominator)
    {
        reduce();
    }

    rational::rational(const char* value)
    {
        std::stringstream ss(value);
        char slash;
        ss >> _numerator >> slash >> _denominator;
        if (slash != '/' or ss.fail()) {
            throw std::invalid_argument("Invalid input format: " + std::string(value));
        }
        reduce();
    }


    rational::rational(const std::string& value)
        :rational(value.c_str()) 
    {
        reduce();
    }


    // copy constructor.(same type)
    rational::rational(const rational& r)
        : _numerator(r._numerator), _denominator(r._denominator)
    {
        reduce();
    }


    // get numerator.
    int rational::numerator() const
    {
        return _numerator;
    }

    // get denominator.
    int rational::denominator() const
    {
        return _denominator;
    }


    // assign.
    void rational::assign(int num, int den)
    {
        _numerator = num;
        _denominator = den;
        reduce();
    }


    // equality operator.
    bool rational::operator==(rational const& other)const
    {
        return _numerator == other._numerator and _denominator == other._denominator;
    }


    // inequality operator.
    bool rational::operator!=(rational const& other)const
    {
        return not(other == *this);
    }


    // less than operator.
    bool rational::operator<(rational const& other)const
    {
        return (_numerator * other._denominator < other._numerator * _denominator);
    }


    // less than or equal operator.
    bool rational::operator<=(rational const& other)const
    {
        return not (other < *this);
    }


    // more than operator.
    bool rational::operator>(rational const& other)const
    {
        return (other < *this);
    }


    // more than or equal operator.
    bool rational::operator>=(rational const& other) const {
        return not(other > *this);
    }


    // Addition operator overloads
    rational rational::operator+(rational const& other) const {
        int num = _numerator * other._denominator + other._numerator * _denominator;
        int den = _denominator * other._denominator;
        return rational(num, den);
    }

    rational rational::operator+(int value) const {
        return *this + rational(value);
    }

    rational operator+(int value, const rational& r) {
        return r + value;
    }


    // Subtraction operator overloads
    rational rational::operator-(rational const& other) const {
        int num = _numerator * other._denominator - other._numerator * _denominator;
        int den = _denominator * other._denominator;
        return rational(num, den);
    }

    rational rational::operator-(int value) const {
        return *this - rational(value);
    }

    rational operator-(int value, const rational& r)
    {
        return rational(value) - r;
    }


    // Multiplication operator overloads
    rational rational::operator*(rational const& other) const {
        int num = _numerator * other._numerator;
        int den = _denominator * other._denominator;
        return rational(num, den);
    }

    rational rational::operator*(int value) const 
    {
        return *this * rational(value);
    }

    rational operator*(int value, const rational& r)
    {
        return r * value;
    }


    // Division operator overloads
    rational rational::operator/(rational const& other) const 
    {
        int num = _numerator * other._denominator;
        int den = _denominator * other._numerator;
        return rational(num, den);
    }

    rational rational::operator/(int value) const 
    {
        return *this / rational(value);
    }

    rational operator/(int value, const rational& r)
    {
        return rational(value) / r;
    }


    // Definitions of assignment operators

    // assignment operator.
    rational& rational::operator=(const rational& other)
    {
        if (this != &other) {
            _numerator = other._numerator;
            _denominator = other._denominator;
        }
        return *this;
    }


    // value assignment operator.
    rational& rational::operator=(int value)
    {
        _numerator = value;
        _denominator = 1;
        return *this;
    }

    // char* assignment operator.
    rational& rational::operator=(const char* value)
    {
        std::stringstream ss(value);
        char slash;
        ss >> _numerator >> slash >> _denominator;
        if (slash != '/' || ss.fail()) {
            throw std::invalid_argument("Invalid input format: " + std::string(value));
        }
        reduce();
        return *this;
    }


    // string Assignment operator.
    rational& rational::operator=(const std::string& value)
    {
        std::stringstream ss(value);
        char slash;
        ss >> _numerator >> slash >> _denominator;
        if (slash != '/' || ss.fail()) {
            throw std::invalid_argument("Invalid input format: " + std::string(value));
        }
        reduce();
        return *this;    
    }

    // Definitions of compound assignment operators
    rational& rational::operator+=(const rational& other)
    {
        *this = *this + other;
        return *this;
    }

    rational& rational::operator+=(int value)
    {
        *this = *this + rational(value);
        return *this;
    }

    rational& rational::operator-=(const rational& other)
    {
        *this = *this - other;
        return *this;
    }

    rational& rational::operator-=(int value)
    {
        *this = *this - rational(value);
        return *this;
    }

    rational& rational::operator*=(const rational& other)
    {
        *this = *this * other;
        return *this;
    }

    rational& rational::operator*=(int value)
    {
        *this = *this * rational(value);
        return *this;
    }

    rational& rational::operator/=(const rational& other)
    {
        *this = *this / other;
        return *this;
    }

    rational& rational::operator/=(int value)
    {
        *this = *this / rational(value);
        return *this;
    }


    // Definitions of increment and decrement operators
    rational& rational::operator++()
    {
        *this += 1;
        return *this;
    }

    rational rational::operator++(int)
    {
        rational temp = *this;
        ++(*this);
        return temp;
    }

    rational& rational::operator--()
    {
        *this -= 1;
        return *this;
    }

    rational rational::operator--(int)
    {
        rational temp = *this;
        --(*this);
        return temp;
    }


    // Definitions of unary operators
    rational rational::operator-() const
    {
        return rational(-_numerator, _denominator);
    }

    rational rational::operator+() const
    {
        return *this;
    }



    //private reduce function.
    void rational::reduce()
    {
        assert(_denominator != 0);
        if(_denominator < 0)
        {
            _numerator = - _numerator;
            _denominator = - _denominator;
        }

        int div{std::gcd(_numerator, _denominator)};
        _numerator /=  div;
        _denominator /= div;
    }

    std::istream& operator>>(std::istream& in, rational& r)
    {
    int n;
    int d;
    char c;

    if (! (in >> n)) return in;
    if (! (in >> c)) return in;
    if (c != '/') {
        // Malformed input.
        in.setstate(std::ios_base::badbit);
        return in;
    }
    if (! (in >> d)) return in;
    r.assign(n, d);
    return in;
    }

    std::ostream& operator<<(std::ostream& out, const rational& r) {
    std::ostringstream s;
    s.flags(out.flags());
    s.imbue(out.getloc());
    s.precision(out.precision());
    s << r.numerator() << '/' << r.denominator();
    out << s.str();
    return out;
    }
}
#endif