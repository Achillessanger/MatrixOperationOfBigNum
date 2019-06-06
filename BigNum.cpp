//
// Created by shiruixin on 2019-06-05.
//
#include "BigNum.h"
using namespace std;

BigNum::BigNum() {
    vec.push_back(0);
    negative = 0;
}
BigNum::BigNum(long int s) {
    if(s < 0){
        negative = 1;
        s = -s;
    } else{
        negative = 0;
    }
    int i;
    while (s > 9){
        i = s % 10;
        vec.push_back(i);
        s /= 10;
    }
    vec.push_back(s);
}
BigNum::BigNum(string str) {
    if(str[0] == '-'){
        negative = 1;
        str = str.substr(1); ///////
    } else{
        negative = 0;
    }
    for(int i = str.size()-1; i >= 0; i--){
        vec.push_back(str[i]-'0'); //从个位到最高位
    }
}
BigNum::BigNum(const BigNum &a) {
    vec = a.vec;
    negative = a.negative;
}
BigNum BigNum::operator=(BigNum a) {
    vec = a.vec;
    negative = a.negative;
    return *this;
}
ostream& operator<<(ostream& out, BigNum& a){
    string str = "";
//    int judge = 0;
//    if((a.vec[a.vec.size()-1] + '0') == '-') //可删
//        judge = 1;
    if((a.negative == 1)){ // && judge == 0
        str += '-';
    }
    for(int i = a.vec.size()-1; i>=0; i--){
        str += (a.vec[i]+'0');
    }
    out<<str;
    return out;
}
istream& operator>>(istream& in, BigNum& a){
    string str = "";
    in>>str;
    a.vec.clear();
    if(str[0] == '-'){
        a.negative = 1;
        str = str.substr(1);
    } else{
        a.negative = 0;
    }
    for(int i = str.size() - 1; i >=0; i--){
        a.vec.push_back(str[i] - '0');
    }
    return in;
}

BigNum BigNum::operator+(const BigNum &b) const {
    int new_negative = 0;
    if(negative ^ b.negative){
        BigNum tmp = (negative == 1)? *this : b;
        tmp.negative = 0;
        return (negative == 1)? (b - tmp) : (*this - tmp);
    } else{
        new_negative = negative;
    }
    BigNum c, tmp;
    int alen,blen,min,max,i;
    alen = vec.size();
    blen = b.vec.size();
    if(alen > blen){
        c.vec = vec;
        tmp.vec = b.vec;
        min = blen;
        max = alen;
    } else{
        c.vec = b.vec;
        tmp.vec = vec;
        min = alen;
        max = blen;
    }
    for(i = 0; i < min -1; i++){
        c.vec[i] += tmp.vec[i];
        if(c.vec[i] > 9){
            c.vec[i] -= 10;
            c.vec[i+1] += 1;
        }
    }
    c.vec[i] += tmp.vec[i];
    if(c.vec[i] > 9){
        c.vec[i] -= 10;
        if(min == max)
            c.vec.push_back(1);
        else
            c.vec[i+1] += 1;
    }
    for(i = min; i < max - 1; i++){
        if(c.vec[i] > 9){
            c.vec[i] -= 10;
            c.vec[i+1] += 1;
        }
    }
    if(c.vec[max - 1] > 9){
        c.vec[max -1] -= 10;
        c.vec.push_back(1);
    }
    i = c.vec.size() - 1;
    while (c.vec[i] == 0 && i != 0){
        c.vec.pop_back();
        i--;
    }
    c.negative = new_negative;
    return c;


}

BigNum BigNum::operator-(const BigNum &num) const { //this - b
    BigNum a = *this;
    BigNum b = num;
    int new_negative = 0;
    if(a.negative == 1 && b.negative == 1){
        a.negative = 0;
        b.negative = 0;
        return (b - a);
    }
    if(a.negative == 0 && b.negative == 0){
        new_negative = 0;
    }
    if(a.negative == 0 && b.negative == 1){
        b.negative = 0;
        return (a + b);
    }
    if(a.negative == 1 && b.negative == 0){
        b.negative = 1;
        return (a + b);
    }
    BigNum c, tmp;
    int alen, blen,min,max,i,judge = 0;
    alen = a.vec.size();
    blen = b.vec.size();
    if(alen > blen){
        c.vec = a.vec;
        tmp.vec = b.vec;
        min = blen;
        max = alen;
        judge = 1;
    } else if(alen == blen){
        for(i = alen - 1; i >= 0; i--){
            if(a.vec[i] > b.vec[i]){
                c.vec = a.vec;
                tmp.vec = b.vec;
                min = blen;
                max = alen;
                judge = 1;
                break;
            } else if(a.vec[i] < b.vec[i]){
                c.vec = b.vec;
                tmp.vec = a.vec;
                min = alen;
                max = blen;
                judge = 2;
                break;
            }
        }
        if(i == -1)
            return (BigNum)0;
    } else{
        c.vec = b.vec;
        tmp.vec = a.vec;
        min = alen;
        max = blen;
        judge = 2;
    }
    for(i = 0; i < min; i++){
        c.vec[i] -= tmp.vec[i];
        if(c.vec[i] < 0){
            c.vec[i] += 10;
            c.vec[i+1] -= 1;
        }
    }
    if(min < max){
        for(i = min; i < max; i++){
            if(c.vec[i] < 0){
                c.vec[i] += 10;
                c.vec[i+1] -=1;
            }
        }
    }
    if(judge == 2){
        c.negative = 1;
    } else{
        c.negative = 0;
    }
    i = c.vec.size() - 1;
    while (c.vec[i] == 0 && i != 0){
        c.vec.pop_back();
        i--;
    }
    return c;
}
BigNum BigNum::operator*(const BigNum &num) const {
    BigNum a = *this;
    BigNum b = num;
    BigNum c;
    int alen,blen,i,j,max,tmp;
    alen = a.vec.size();
    blen = b.vec.size();
    max = alen + blen;
    c.vec.clear();
    for(i = 0; i < max; i++){
        c.vec.push_back(0);
    }
    for(i = 0; i < alen; i++){
        for(j = 0; j < blen; j++){
            tmp = c.vec[i+j] + a.vec[i]*b.vec[j];
            if(tmp > 9){
                if(i+j+1 < max){
                    c.vec[i+j+1] += tmp/10;
                    tmp %= 10;
                } else{
                    c.vec.push_back(tmp/10);
                    tmp %= 10;
                }
            }
            c.vec[i+j] = tmp;
        }
    }
    i = c.vec.size() - 1;
    while (c.vec[i] == 0 && i != 0){
        c.vec.pop_back();
        i--;
    }
    if((a.negative == 0 && b.negative == 1) || (a.negative == 1 && b.negative == 0)){
        c.negative = 1;
    } else{
        c.negative = 0;
    }
    return c;
}

