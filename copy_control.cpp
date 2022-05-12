#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<map>
#include<unordered_map>
#include<set>
#include<memory>

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
using std::make_pair;
using std::unordered_map;
using std::multimap;
using std::multiset;
using std::shared_ptr;
using std::make_shared;
using std::allocator;


// 实现行为类似值的类（深拷贝）
// 不过在 C++ 中，不一定需要深拷贝，还可以“移动”
class HasObj {

    public:
        HasObj (const string &s = string()) : ps(new string(s)), i(0) {
        }

        HasObj (const HasObj &obj) : ps(new string(*(obj.ps))), i(0) {
        }

        HasObj& operator = (const HasObj & obj2) {
            
            auto *newp = new string(*obj2.ps);
            delete this->ps;
            this->ps = newp;
            newp = nullptr;
            this->i = obj2.i;
            return *this;
        }

        ~HasObj () {
            delete ps;
        }

        void printPS () {
            cout << *ps << endl;
        }


    //private:
        string *ps;
        int i;
};


//定义行为类似指针的类（浅拷贝）
class HasPtr {
    public:
        
        HasPtr(const string &s = string()) : sp(make_shared<string>(s)), i(0) {
        } 

        HasPtr(const HasPtr &obj) : sp(obj.sp), i(0) {
        }

        void swap (HasPtr &lobj, HasPtr &robj) {
            lobj.sp.swap (robj.sp);
            std::swap (lobj.i, robj.i);
        }

        //HasPtr& operator = (const HasPtr &obj) {
        //
        //    this->sp = obj.sp;
        //    this->i = obj.i;
        //    return *this;
        //}

        HasPtr& operator = (HasPtr obj) {
        
            swap (*this, obj);
            return *this;
        }

        ~HasPtr() {
        }

        void printSp () {
            cout << *sp << endl;
        }

    //private:
        shared_ptr<string> sp;
        int i;

};


// 深拷贝的测试函数
void value_copy_test () {

    HasObj obj(string(3, '6'));
    HasObj obj2 = obj;
    HasObj obj3 (obj);
    cout << "obj地址是：" << obj.ps << "值是：";
    obj.printPS();
    cout << "obj2地址是：" << obj2.ps << "值是：";
    obj2.printPS();
    cout << "obj3地址是：" << obj3.ps << "值是：";
    obj3.printPS();
    
}

// 浅拷贝、传引用的测试函数
void subfunction_of_reference_copy_test (HasPtr &obj, HasPtr &obj2) {

    HasPtr obj3 (obj);
    obj3 = obj2;

    cout << "obj地址是：" << obj.sp << "值是：";
    obj.printSp();
    cout << "obj2地址是：" << obj2.sp << "值是：";
    obj2.printSp();
    cout << "obj3地址是：" << obj3.sp << "值是：";
    obj3.printSp();

    cout << "函数返回前，销毁了 obj2 和 obj3 前，obj 的引用为：" << obj.sp.use_count() << endl;
    cout << "函数返回前，销毁了 obj2 和 obj3 前，obj2 的引用为：" << obj2.sp.use_count() << endl;
}

void reference_copy_test () {

    HasPtr obj(string(3, '6'));
    HasPtr obj2 ("999999999");
    subfunction_of_reference_copy_test(obj, obj2);
    cout << "函数返回后，销毁了 obj2 和 obj3 后，obj 的引用为：" << obj.sp.use_count() << endl;
    cout << "函数返回前，销毁了 obj2 和 obj3 前，obj2 的引用为：" << obj2.sp.use_count() << endl;

}


int main() {

    //reference_copy_test();

    return 0;
}

