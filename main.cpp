#include <iostream>
#include "rational/rational.h"
#include <type_traits>
#include <chrono>

/**
 * @brief Construct a line separator between CLI arguments and results.
 * @param none
 */

#define LINE                            \
    {                                   \
        for (size_t i = 0; i < 80; i++) \
            std::cout << '-';           \
        std::cout << std::endl;         \
    }

/**
 * @brief TEST function that prints the expression and its value.
 * @param expression
 */

#define TEST(expression)                                                        \
    {                                                                           \
        std::cout << std::boolalpha;                                            \
        if (typeid(expression) == typeid(bool))                                 \
            std::cout << "(" #expression ") --> " << (expression) << std::endl; \
        else                                                                    \
            std::cout << "(" #expression ") --> " << (expression) << std::endl; \
    }

/**
 * @brief main fuction: entry point to the program.
 * @return (0) for successful build and any interger for failure.
 */
int main()
{
    LINE;
    ::numbers::rational a = 1.5;
    ::numbers::rational b = 0.3;
    TEST(a + b);
    TEST(true and false);
    return 0;
}