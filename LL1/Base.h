#ifndef _BASE_H
#define _BASE_H
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;

#define MAXNUM 100

//产生式类
class Production {
    //LL1 基于上下文无关文法
    char left;
    string right;
};

//Base类
class Base {
private:
    vector<Production> prods;
    set<char> firstSet[MAXNUM];
    set<char> followSet[MAXNUM];

protected:
    vector<char> ter;  //终结符号集
    vector<char> noter; //非终结符号集

public:
    Base(){
    
    }
    ~Base() {
        delete[] firstSet;
        delete[] followSet;
        ter.clear();
        noter.clear();
    }

    bool isNoter(char target);
    Production* getProds();
    int getTerIndex(char target);
    int getNoterIndex(char target);
    bool getFirstSet(char target);
    bool getFollowSet(char target);
    void setFirstSet(char target);
    void setFollowSet(char target);
    void Base::display();
};
#endif
