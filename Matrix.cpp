//
// Created by shiruixin on 2019-06-05.
//
#include "Matrix.h"

Matrix::Matrix() {
    m.clear();
}
Matrix::Matrix(vector<vector<BigNum>> vec) {
    m = vec;
}
Matrix Matrix::operator+(const Matrix &b) const {
    Matrix a = *this;
    Matrix c;
    for(int i = 0; i < a.m.size(); i++){
        vector<BigNum> raw;
        for(int j = 0; j < a.m[0].size(); j++){
            raw.push_back(a.m[i][j] + b.m[i][j]);
        }
        c.m.push_back(raw);
    }
    return c;
}
Matrix Matrix::operator-(const Matrix &b) const {
    Matrix a = *this;
    Matrix c;
    for(int i = 0; i < a.m.size(); i++){
        vector<BigNum> raw;
        for(int j = 0; j < a.m[0].size(); j++){
            raw.push_back(a.m[i][j] - b.m[i][j]);
        }
        c.m.push_back(raw);
    }
    return c;
}
Matrix Matrix::operator*(const Matrix &b) const {
    Matrix a = *this;
    Matrix c;

//    vector<BigNum> raw;
//    for(int i = 0; i < a.m[0].size(); i++){
//        BigNum tmp = BigNum(0);
//        for(int j = 0; j < b.m.size(); j++){
//
//        }
//        c.m.push_back(raw);
//    }

    for(int q = 0; q < a.m.size(); q++){ //a行数
        vector<BigNum> raw;

        for(int i = 0; i < b.m[0].size(); i++){ //b列数
            BigNum tmp = BigNum(0);
            for(int j = 0; j < a.m[0].size(); j++){
                tmp = tmp + (a.m[q][j] * b.m[j][i]);
            }
            raw.push_back(tmp);
        }
        c.m.push_back(raw);
    }
    return c;
}
Matrix Matrix::operator~() const{
    Matrix b;
    b.m.clear();
//    this->m.clear();
    for(int i = 0; i < this->m[0].size(); i++){
        vector<BigNum> raw;
        for(int j = 0; j < this->m.size(); j++){
            raw.push_back(this->m[j][i]);
        }
        b.m.push_back(raw);
    }
    return b;
}
ostream& operator<<(ostream& out, Matrix& a){
    for(int i = 0; i < a.m.size(); i++){
        for(int j = 0; j < a.m[0].size(); j++){
            out<<a.m[i][j];
            out<<" ";
        }
        out<<"\n";
    }
    return out;
}

const Matrix operator*(const BigNum& bn, Matrix& matrix){
    Matrix c;
    for(int i = 0; i < matrix.m.size(); i++){
        vector<BigNum> raw;
        for(int j = 0; j < matrix.m[0].size(); j++){
            raw.push_back(matrix.m[i][j] * bn);
        }
        c.m.push_back(raw);
    }
    return c;
}
