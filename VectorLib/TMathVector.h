#ifndef T_MATH_VECTOR_H
#define T_MATH_VECTOR_H

#include "VectorLib.h"
#include <stdexcept>

template <typename ValType>
class TMathVector : public Vector<ValType> {
public:
    TMathVector(size_t size = 0, size_t startIndex = 0) : Vector<ValType>() {
        for (size_t i = 0; i < size; i++)
        {
            this->push_back(ValType(0));
        }
    }

    TMathVector(const Vector<ValType>& v) : Vector<ValType>(v) {}
    TMathVector(const TMathVector& v) : Vector<ValType>(v) {}
    ~TMathVector() = default;

    TMathVector& operator=(const TMathVector& v) {
        if (this != &v) {
            Vector<ValType>::operator=(v);
        }
        return *this;
    }

    bool operator==(const TMathVector& v) const {
        if (this->get_size() != v.get_size()) return false;
        for (size_t i = 0; i < this->get_size(); i++) {
            if ((*this)[i] != v[i]) return false;
        }
        return true;
    }

    TMathVector operator+(const TMathVector& v) const {
        if (this->get_size() != v.get_size()) {
            throw std::invalid_argument("Vector sizes must be equal for addition.");
        }
        TMathVector res(this->get_size());
        for (size_t i = 0; i < this->get_size(); i++) {
            res[i] = (*this)[i] + v[i];
        }
        return res;
    }

    TMathVector operator-(const TMathVector& v) const {
        if (this->get_size() != v.get_size()) {
            throw std::invalid_argument("Vector sizes must be equal for subtraction.");
        }
        TMathVector res(this->get_size());
        for (size_t i = 0; i < this->get_size(); i++) {
            res[i] = (*this)[i] - v[i];
        }
        return res;
    }

    ValType operator*(const TMathVector& v) const {
        if (this->get_size() != v.get_size()) {
            throw std::invalid_argument("Vector sizes must be equal for scalar product.");
        }
        ValType res = 0;
        for (size_t i = 0; i < this->get_size(); i++) {
            res += (*this)[i] * v[i];
        }
        return res;
    }

    TMathVector operator*(const ValType& val) const {
        TMathVector res(this->get_size());
        for (size_t i = 0; i < this->get_size(); i++) {
            res[i] = (*this)[i] * val;
        }
        return res;
    }

    template <typename T>
    friend std::istream& operator>>(std::istream& in, TMathVector<T>& v);

    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, const TMathVector<T>& v);
};

template <typename T>
std::istream& operator>>(std::istream& in, TMathVector<T>& v) {
    for (size_t i = 0; i < v.get_size(); i++) {
        in >> v[i];
    }
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const TMathVector<T>& v) {
    out << "{ ";
    for (size_t i = 0; i < v.get_size(); i++) {
        out << v[i];
        if (i + 1 < v.get_size()) out << ", ";
    }
    out << " }";
    return out;
}

#endif