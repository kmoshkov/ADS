#pragma once


#include <ostream>
#include <cstddef>
#include <stdexcept>

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





    std::size_t Size() const { return size_; }

private:
    T* data_;
    std::size_t size_;
};