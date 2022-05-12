#ifndef _TABLE_H
#define _TABLE_H
#include<Base.h>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#include<set>
#include<stdlib>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;

class Table : Base {
private:
    vector<char> analyStack; // 分析栈
    vector<char> leftExpr;  // 剩余输入串
    int tableMap[100][100];  // 预测表

public:
    Table() {
    
    }
     void getTable(); // 生成预测表
    void analyExpression(string s);  // 分析输入语句s
    void printPredictTable();  // 输出预测表
    void getResult(); // 综合处理
};

#endif
