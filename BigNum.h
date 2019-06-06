//
// Created by shiruixin on 2019-06-05.
//

#ifndef LAB4_LARGENUMBER_H
#define LAB4_LARGENUMBER_H
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
using namespace std;
class BigNum{
public:
    BigNum();
    BigNum(long int s);
    BigNum(string str);
    BigNum(const BigNum& a);
    BigNum operator+(const BigNum&) const ;
    BigNum operator-(const BigNum&) const ;
    BigNum operator*(const BigNum&) const ;
    friend ostream& operator<<(ostream& out, BigNum& a);
    friend istream& operator>>(istream& in, BigNum& a);
    BigNum operator=(BigNum a);
    friend int SizeJudge(BigNum a, BigNum b);
    vector<int> vec;
    int negative; //0正，1负
};
#endif //LAB4_LARGENUMBER_H
