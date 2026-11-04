#ifndef TMATRIX_H
#define TMATRIX_H

#include <iostream>
#include <stdexcept>
#include "TMathVector.h"

template <typename ValType>
class TMatrix : public Vector<TMathVector<ValType>> {
protected:
    size_t rows;
    size_t cols;

public:
    TMatrix(size_t r = 0, size_t c = 0) : Vector<TMathVector<ValType>>(), rows(r), cols(c) {
        for (size_t i = 0; i < rows; i++) {
            this->push_back(TMathVector<ValType>(cols));
        }
    }

    TMatrix(const TMatrix& mt) : Vector<TMathVector<ValType>>(mt), rows(mt.rows), cols(mt.cols) {}

    TMatrix(TMatrix&& mt) noexcept : Vector<TMathVector<ValType>>(std::move(mt)), rows(mt.rows), cols(mt.cols) {
        mt.rows = 0;
        mt.cols = 0;
    }

    virtual ~TMatrix() = default;

    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }

    TMatrix& operator=(const TMatrix& mt) {
        if (this != &mt) {
            Vector<TMathVector<ValType>>::operator=(mt);
            rows = mt.rows;
            cols = mt.cols;
        }
        return *this;
    }

    TMatrix& operator=(TMatrix&& mt) noexcept {
        if (this != &mt) {
            Vector<TMathVector<ValType>>::operator=(std::move(mt));
            rows = mt.rows;
            cols = mt.cols;
            mt.rows = 0;
            mt.cols = 0;
        }
        return *this;
    }

    TMathVector<ValType>& operator[](size_t pos) {
        return Vector<TMathVector<ValType>>::operator[](pos);
    }

    const TMathVector<ValType>& operator[](size_t pos) const {
        return Vector<TMathVector<ValType>>::operator[](pos);
    }

    //cложение матриц
    TMatrix operator+(const TMatrix& mt) const {
        if (rows != mt.rows || cols != mt.cols) {
            throw std::invalid_argument("Error: razmer matrix ne sovpadaet");
        }
        TMatrix res(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                res[i][j] = (*this)[i][j] + mt[i][j];
            }
        }
        return res;
    }

    //вычитание матриц
    TMatrix operator-(const TMatrix& mt) const {
        if (rows != mt.rows || cols != mt.cols) {
            throw std::invalid_argument("Error: razmer matrix ne sovpadaet");
        }
        TMatrix res(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                res[i][j] = (*this)[i][j] - mt[i][j];
            }
        }
        return res;
    }

    //умножение матрицы на скаляр (число)
    TMatrix operator*(const ValType& val) const {
        TMatrix res(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                res[i][j] = (*this)[i][j] * val;
            }
        }
        return res;
    }

    //умножение матриц
    TMatrix operator*(const TMatrix& mt) const {
        if (cols != mt.rows) {
            throw std::invalid_argument("Error: razmer matrix ne sovpadaet s drygoy");
        }
        TMatrix res(rows, mt.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < mt.cols; j++) {
                ValType sum = 0;
                for (size_t k = 0; k < cols; k++) {
                    sum += (*this)[i][k] * mt[k][j];
                }
                res[i][j] = sum;
            }
        }
        return res;
    }

    //cравнение матриц
    bool operator==(const TMatrix& mt) const {
        if (rows != mt.rows || cols != mt.cols) return false;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if ((*this)[i][j] != mt[i][j]) return false;
            }
        }
        return true;
    }

    bool operator!=(const TMatrix& mt) const {
        return !(*this == mt);
    }//потоковый ввод вывод
    template <typename T>
    friend std::ostream& operator<<(std::ostream& out, const TMatrix<T>& mt);

    template <typename T>
    friend std::istream& operator>>(std::istream& in, TMatrix<T>& mt);
};

//pеализация операторов вводавывода
template <typename ValType>
std::ostream& operator<<(std::ostream& out, const TMatrix<ValType>& mt) {
    out << mt.rows << " " << mt.cols << "\n";
    for (size_t i = 0; i < mt.rows; i++) {
        for (size_t j = 0; j < mt.cols; j++) {
            out << mt[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

template <typename ValType>
std::istream& operator>>(std::istream& in, TMatrix<ValType>& mt) {
    size_t r, c;
    in >> r >> c;
    mt = TMatrix<ValType>(r, c);
    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < c; j++) {
            in >> mt[i][j];
        }
    }
    return in;
}

#endif