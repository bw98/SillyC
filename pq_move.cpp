#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include<forward_list>
#include<queue>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<map>
#include<unordered_map>
#include<set>
#include<memory>
#include<functional>
#include<utility>
#include<random>
#include<unistd.h>

// 实际编程中，为了避免命名空间污染，可以将 using xxx 写在函数作用域里面
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
using std::array;
using std::list;
using std::forward_list;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::multimap;
using std::multiset;
using std::shared_ptr;
using std::make_shared;
using std::allocator;


struct Money {

    Money (int zz, float dd) : z(zz), d(dd) {
        cout << "调用了 Money 的普通构造函数！" << endl;
    }

    Money (const Money &m) : z(m.z), d(m.d) {
        cout << "麻蛋 调用 Money 的拷贝构造了！" << endl;
    }

    Money (Money &&m) noexcept
        : z(m.z), d(m.d) {
            cout << "Good 调用了 Money 的移动构造函数！" << endl;
    }

    Money & operator = (const Money &robj) {

        cout << "调用了 Money 的运算符 =  ！" << endl;
        (*this).z = robj.z;
        (*this).d = robj.d;
        return *this;
    }

    Money & operator = (Money &&robj) {

        cout << "调用了 Money （穿右值引用）的运算符 =  ！" << endl;
        (*this).z = robj.z;
        (*this).d = robj.d;
        return *this;
    }

    int z;
    float d;

};

bool operator < (Money &lobj, Money &robj) {

    return (lobj.z + lobj.d) < (robj.z + robj.d);
}

struct pq_cmp_money {

    bool operator () (Money lobj, Money robj) {

        sleep(10);
        cout << "优先队列的元素正在排序, 睡眠了10秒..." << endl;
        return (lobj.z + lobj.d) > (robj.z + robj.d);
    }
};

int main () {

    Money m (2, 3.5);
    Money m2 (1, 3.5);

    std::priority_queue <Money, vector<Money>, pq_cmp_money> pq;
    pq.push (m);
    pq.push (m2);
    // 上面两行代码解释如下
    // 1. push (m)    pq创建一个 Money 匿名对象 obj1，调用拷贝构造函数初始化 obj1
    // 2. push (m2)   pq 创建一个 Money 匿名对象 obj2, 调用拷贝构造函数初始化 obj2
    // 3. 此时 pq 中出现了两个对象，利用序关系去调整顺序，调用函数对象 pq_cmp_money， 
    //          其参数1 lobj 和 参数2 robj 调用拷贝构造函数并利用 obj1 obj2 初始化 lobj, robj
    // 4. 比较得到了两个匿名对象的序关系，使用移动构造函数与移动赋值运算符将匿名对象 obj1 与 obj2 移动到对应的位置
    // 大致的思路是这样，最后两步的细节操作会有所不同
    //
    //vector<Money> vec;
    //vec.push_back(m);
    //vec.push_back(m2);

    //auto e = pq.top();
    //pq.pop();
    //cout << e.z << " " << e.d << endl; 

    //e.z = 55;
    //e.d = 1.2;

    //cout << e2.z << " " << e2.d << endl; 
    //cout << m.z << " " << m.d << endl; 
    //cout << m2.z << " " << m2.d << endl; 

    return 0;
}



