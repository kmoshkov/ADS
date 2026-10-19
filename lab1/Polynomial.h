#pragma once


#include <ostream>
#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <complex>

struct Point {
    double x;
    double y;
};

template <typename T>
class Polynomial {
public:
    static constexpr double kEpsilon = 1e-9;

    explicit Polynomial(std::size_t max_degree) : data_(nullptr), size_(0) {
        data_ = new T[max_degree + 1]();
        size_ = max_degree + 1;
    }


    Polynomial(const T* coefficients, std::size_t count): data_(nullptr), size_(0) {
        if (coefficients == nullptr || count == 0) {
            throw std::invalid_argument("Coefficients array is empty");
        }
        data_ = new T[count];
        size_ = count;
        for (std::size_t i = 0; i < count; ++i) {
            data_[i] = coefficients[i];
        }
    }

    ~Polynomial() { delete[] data_; }

    Polynomial(const Polynomial& other) : data_(new T[other.size_]), size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    std::size_t Size() const { return size_; }

    Polynomial& operator=(const Polynomial& other) {
        if (this == &other) {
            return *this;
        }
        T* new_data = new T[other.size_];
        for (std::size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        return *this;
    }

    void Expand(std::size_t max_degree) {
        if (max_degree < size_ - 1) {
            return;
        }

        T* new_data = new T[max_degree + 1]();
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = max_degree + 1;
    }

    T operator[](std::size_t degree) const {
        if (degree >= size_) {
            return T();
        }
        return data_[degree];
    }

    void Set(std::size_t degree, const T& value) {
        Expand(degree);
        data_[degree] = value;
    }

    void ShrinkToFit() {
        std::size_t new_size = size_;
        while (new_size > 1 && IsZero(data_[new_size - 1])) {
            --new_size;
        }
        if (new_size == size_) {
            return;
        }
        T* new_data = new T[new_size];
        for (std::size_t i = 0; i < new_size; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = new_size;
    }

    bool operator==(const Polynomial& other) const {
        std::size_t max_size = size_ > other.size_ ? size_ : other.size_;
        for (std::size_t i = 0; i < max_size; ++i) {
            if (!IsZero((*this)[i] - other[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Polynomial& other) const { return !(*this == other); }

    Polynomial& operator+=(const Polynomial& other) {
        if (other.size_ > size_) {
            Expand(other.size_ - 1);
        }

        for (std::size_t i = 0; i < other.size_; ++i) {
            data_[i] += other.data_[i];
        }

        return *this;
    }

    Polynomial& operator-=(const Polynomial& other) {
        if (other.size_ > size_) {
            Expand(other.size_ - 1);
        }
        for (std::size_t i = 0; i < other.size_; ++i) {
            data_[i] -= other.data_[i];
        }
        return *this;
    }

    Polynomial& operator*=(const T& scalar) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] *= scalar;
        }
        return *this;
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result(*this);
        result += other;
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial result(*this);
        result -= other;
        return result;
    }

    Polynomial operator*(const T& scalar) const {
        Polynomial result(*this);
        result *= scalar;
        return result;
    }

    T Evaluate(const T& x) const {
        T result = T();
        T power = T(1);

        for (std::size_t i = 0; i < size_; ++i) {
            result += data_[i] * power;
            power *= x;
        }

        return result;
    }


private:
    T* data_;
    std::size_t size_;

    static bool IsZero(const T& value) {
        return static_cast<double>(std::abs(value)) <= kEpsilon;
    }
};

template <typename T>
Polynomial<T> operator*(const T& scalar, const Polynomial<T>& polynomial) {
    return polynomial * scalar;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynomial) {
    for (std::size_t i = 0; i < polynomial.Size(); ++i) {
        if (i > 0) {
            out << " + ";
        }

        out << polynomial[i];

        if (i > 0) {
            out << "*x";
        }

        if (i > 1) {
            out << '^' << i;
        }
    }

    return out;
}

template <typename T>
Point FindExtremum(Polynomial<T> polynomial) {
    polynomial.ShrinkToFit();

    if (polynomial.Size() != 3) {
        throw std::invalid_argument("Polynomial must have degree 2");
    }

    const double c = static_cast<double>(polynomial[0]);
    const double b = static_cast<double>(polynomial[1]);
    const double a = static_cast<double>(polynomial[2]);

    const double x = -b / (2.0 * a);
    const double y = (a * x + b) * x + c;

    return {x, y};
}