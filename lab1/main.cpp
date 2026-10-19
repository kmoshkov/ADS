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
        Polynomial<int> p_int(2);
        p_int.Set(0, 1);
        p_int.Set(1, -4);
        p_int.Set(2, 2);

        Point result_int = FindExtremum(p_int);
        std::cout << "int: " << result_int.x << ", "
                  << result_int.y << '\n';

        Polynomial<float> p_float(2);
        p_float.Set(0, 1.0f);
        p_float.Set(1, -4.0f);
        p_float.Set(2, 2.0f);

        Point result_float = FindExtremum(p_float);
        std::cout << "float: " << result_float.x << ", "
                  << result_float.y << '\n';

        Polynomial<double> p_double(2);
        p_double.Set(0, 1.0);
        p_double.Set(1, -4.0);
        p_double.Set(2, 2.0);

        Point result_double = FindExtremum(p_double);
        std::cout << "double: " << result_double.x << ", "
                  << result_double.y << '\n';

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}