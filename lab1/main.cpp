#include <iostream>

#include <random>

#include "Polynomial.h"

template <typename T>
Polynomial<T> GenerateRandomPolynomial(std::size_t max_degree) {
    
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<int> distr(-5, 5);

    Polynomial<T> polynomial(max_degree);

    for (std::size_t i = 0; i <= max_degree; ++i) {
        polynomial.Set(i, static_cast<T>(distr(gen)));
    }

    while (polynomial[max_degree] == T{}) {
        polynomial.Set(
            max_degree,
            static_cast<T>(distr(gen))
        );
    }

    return polynomial;
}

int main() {
    try {
        Polynomial<int> pInt(2);
        pInt.Set(0, 1);
        pInt.Set(1, -4);
        pInt.Set(2, 2);

        auto resultInt = FindExtremum(pInt);
        std::cout << "int: " << resultInt.first << ", "
                  << resultInt.second << '\n';

        Polynomial<float> pFloat(2);
        pFloat.Set(0, 1.0f);
        pFloat.Set(1, -4.0f);
        pFloat.Set(2, 2.0f);

        auto resultFloat = FindExtremum(pFloat);
        std::cout << "float: " << resultFloat.first << ", "
                  << resultFloat.second << '\n';

        Polynomial<double> pDouble(2);
        pDouble.Set(0, 1.0);
        pDouble.Set(1, -4.0);
        pDouble.Set(2, 2.0);

        auto resultDouble = FindExtremum(pDouble);
        std::cout << "double: " << resultDouble.first << ", "
                  << resultDouble.second << '\n';

        Polynomial<std::complex<float>> pComplexFloat(2);
        pComplexFloat.Set(0, {1.0f, 2.0f});
        pComplexFloat.Set(1, {-4.0f, 1.0f});
        pComplexFloat.Set(2, {2.0f, 0.0f});

        Polynomial<std::complex<double>> pComplexDouble(2);
        pComplexDouble.Set(0, {1.0, 2.0});
        pComplexDouble.Set(1, {-4.0, 1.0});
        pComplexDouble.Set(2, {2.0, 0.0});

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}