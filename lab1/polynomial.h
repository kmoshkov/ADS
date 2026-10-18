#pragma once

#include <cstddef>

template <typename T>
class Polynomial {
public:
    static constexpr double kEpsilon = 1e-9;

private:
    T* data_;
    std::size_t size_;
};
