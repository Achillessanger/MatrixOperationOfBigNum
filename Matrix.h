//
// Created by shiruixin on 2019-06-05.
//

#ifndef LAB4_MATRIX_H
#define LAB4_MATRIX_H

#include "BigNum.h"
#include <vector>
using namespace std;
class Matrix{
    vector<vector<BigNum>> m;
public:
    Matrix();
    Matrix(vector<vector<BigNum>> vec);
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix operator~() const;
    friend const Matrix operator*(const BigNum&, Matrix&);
    friend ostream& operator<<(ostream& out, Matrix& a);
//    friend istream& operator>>(istream& in, Matrix& a);
};

#endif //LAB4_MATRIX_H
