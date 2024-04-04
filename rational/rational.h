#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>
#include <cassert>
#include <numeric>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <ios>
#include <sstream>
#include <string>
#include <cstdlib>
#include <type_traits>
#include <bit>

namespace numbers
{

    class rational
    {
    public:
        rational();
        rational(int);

        template <typename T>
        rational(T value,
                 typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr)
        {
            _numerator = static_cast<int>(value * 10000000);
            _denominator = 10000000;
            reduce();
        }

        rational(int, int);

        template <typename T1, typename T2>
        rational(T1 value1, T2 value2,
                 typename std::enable_if<std::is_arithmetic<T1>::value &&
                                         std::is_arithmetic<T2>::value>::type * = nullptr)
        {
            int max_digits = std::max(std::countl_zero(*reinterpret_cast<unsigned int *>(&value1)) - 20,
                                      std::countl_zero(*reinterpret_cast<unsigned int *>(&value2)) - 20);

            double factor = std::pow(10, max_digits);

            _numerator = static_cast<int>(value1 * factor);
            _denominator = static_cast<int>(value2 * factor);

            reduce();
        }

        rational(const char *value);
        rational(const std::string &value);
        rational(const rational &r);

        int numerator() const;
        int denominator() const;

        void assign(int, int);

        bool operator==(rational const &) const;
        bool operator!=(rational const &) const;
        bool operator<(rational const &) const;
        bool operator<=(rational const &) const;
        bool operator>(rational const &) const;
        bool operator>=(rational const &) const;

        rational operator+(rational const &) const;
        rational operator+(int) const;
        rational operator-(rational const &) const;
        rational operator-(int) const;
        rational operator*(rational const &) const;
        rational operator*(int) const;
        rational operator/(rational const &) const;
        rational operator/(int) const;

        // Assignment operators
        rational &operator=(const rational &other);
        rational &operator=(int value);
        rational &operator=(const char *);
        rational &operator=(const std::string &);

        // Compound assignment operators
        rational &operator+=(const rational &other);
        rational &operator+=(int value);
        rational &operator-=(const rational &other);
        rational &operator-=(int value);
        rational &operator*=(const rational &other);
        rational &operator*=(int value);
        rational &operator/=(const rational &other);
        rational &operator/=(int value);

        // Increment and decrement operators
        rational &operator++();   // Prefix increment
        rational operator++(int); // Postfix increment
        rational &operator--();   // Prefix decrement
        rational operator--(int); // Postfix decrement

        // Unary operators
        rational operator-() const; // Unary minus (negation)
        rational operator+() const; // Unary plus

    private:
        void reduce();
        int _numerator, _denominator;
    };

    rational operator+(int value, const rational &r);

    rational operator-(int value, const rational &r);

    rational operator*(int value, const rational &r);

    rational operator/(int value, const rational &r);

    std::istream &operator>>(std::istream &in, rational &r);

    ::std::ostream &operator<<(::std::ostream &out, const rational &r);
}

#include "rational.hpp"
#endif
