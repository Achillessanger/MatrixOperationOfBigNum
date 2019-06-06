#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include "BigNum.h"
#include "Matrix.h"
#include <vector>
#include <map>
#include "stdio.h"
#include <string>
#include <regex>
#include <stdlib.h>
using namespace std;
vector<string> infix2postfix(string infix);
int priority(string str);
Matrix cal(vector<string> postfix);
//int ary(string str);
Matrix operate(string op, Matrix matrix1, Matrix matrix2);

map<string,Matrix> map_M;

int main() {
    string matrix_in_path = "../matrix.in";
    string expression_in_path = "../expression.in";
    string result_out_path = "../result.out";

    ifstream fin(matrix_in_path,ios::in);
    string line = "";
    fin >> line;
    int num = atoi(line.c_str());
    for(int i = 0; i < num; i++){
        string matrix_name = "";
        fin >> matrix_name;
        vector<vector<BigNum>> vvec;
        vvec.clear();
        for(int j = 0; j < 3; j++){
            string string1 = "";
            string string2 = "";
            string string3 = "";
            fin >> string1;
            fin >> string2;
            fin >> string3;
            vector<BigNum> vector = {BigNum(string1),BigNum(string2),BigNum(string3)};
            vvec.push_back(vector);
        }
        map_M[matrix_name] = Matrix(vvec);
    }


    ifstream fin_e(expression_in_path,ios::in);
    ofstream ou(result_out_path,ios::out);
//    char line2[2000] = "";
    string line2 = "";
    while (getline(fin_e,line2)){//fin_e.getline(line2, sizeof(line2))
        Matrix re = cal(infix2postfix(line2));
        cout<<re<<endl;
        ou<<re;
    }


    return 0;
}

vector<string> infix2postfix(string infix){
    infix = regex_replace(infix,regex(" "),"");
    if(infix[0] == '-' && !isdigit(infix[1])){
        infix = infix.substr(1);
        infix = "-1*"+infix;
    }

    vector<string> symbol;
    vector<string> postfix;
    symbol.clear();
    postfix.clear();
    string tmp = "";
    if(infix[0] == '-'){
        tmp += infix[0];
        infix = infix.substr(1);
        while (!(infix[0] == '+' || infix[0] == '-' || infix[0] == '*' || infix[0] == '~')){
            tmp += infix[0];
            infix = infix.substr(1);
        }
    }
    if(tmp != "")
        postfix.push_back(tmp);
    string tmp_num = "";
    while (infix.length() != 0){
        if(infix[0] == '+' || infix[0] == '-' || infix[0] == '*' || infix[0] == '~'){
            if(!(tmp_num == "")){
                postfix.push_back(tmp_num);
                tmp_num = "";
            }
            if(symbol.size() == 0){
                string tmp = "";
                tmp += infix[0];
                symbol.push_back(tmp);
            } else{
                string tmp = "";
                tmp += infix[0];
                while (priority(tmp) >= priority(symbol.back())){ //优先级不高
                    string tmp2 = symbol.back();
                    postfix.push_back(tmp2);
                    symbol.pop_back();
                    if(symbol.size() == 0)
                        break;
                }
                symbol.push_back(tmp);

            }
        } else{
            tmp_num += infix[0];
        }
        infix = infix.substr(1);
    }
    if(!(tmp_num == "")){
        postfix.push_back(tmp_num);
        tmp_num = "";
    }
    while (symbol.size() != 0){
        postfix.push_back(symbol.back());
        symbol.pop_back();
    }

    return postfix;
}

int priority(string str){
    if(str == "~")
        return 0;
    if(str == "*" || str == "/")
        return  1;
    if(str == "+" || str == "-")
        return 2;
}


Matrix cal(vector<string> postfix){
    vector<string> args;
    args.clear();
    Matrix top;
    for(int i = 0; i < postfix.size(); i++){
        if(!(postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "~")){
            args.push_back(postfix[i]);
        } else{
            string tmp_name = "DUR";
            tmp_name += to_string(i);
            if(postfix[i] == "~"){
                Matrix tmp = map_M.find(args.back())->second;
                top = ~tmp;
                args.pop_back();
                map_M[tmp_name] = top;
                args.push_back(tmp_name);

            } else if(postfix[i] == "+" || postfix[i] == "-"){
                string second = args.back();
                args.pop_back();
                string first = args.back();
                args.pop_back();
                top = operate(postfix[i],map_M.find(first)->second,map_M.find(second)->second);
                map_M[tmp_name] = top;
                args.push_back(tmp_name);
            } else if(postfix[i] == "*"){
                string second = args.back();
                args.pop_back();
                string first = args.back();
                args.pop_back();
                if(regex_match(first,regex(".*[a-zA-Z]+.*"))){ //矩阵*矩阵
                    Matrix m1 = map_M.find(first)->second;
                    Matrix m2 = map_M.find(second)->second;
                    top = m1 * m2;
                    map_M[tmp_name] = top;
                    args.push_back(tmp_name);
                } else{
                    BigNum bn = BigNum(first);
                    Matrix m2 = map_M.find(second)->second;
                    top = bn * m2;
                    map_M[tmp_name] = top;
                    args.push_back(tmp_name);
                }
            }
        }
    }
    return map_M[args.back()];
}

Matrix operate(string op, Matrix matrix1, Matrix matrix2){
    if(op == "+")
        return matrix1 + matrix2;
    if(op == "-")
        return matrix1 - matrix2;
}
