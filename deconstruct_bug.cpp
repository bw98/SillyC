#include <iostream>
#include <deque>
#include <vector>
// #include <string.h>

class A {                                                                                                          
public:                                                                                                          
    A() : p_(NULL) {
        p_ = new char[20];
        char buf[] = "Construct!";
        memcpy(p_, buf, sizeof(buf));
        std::cout << buf << std::endl;
    }

    // A(const A& a) : p_(new char[20]) {
    //     std::cout << "Copy construct!" << std::endl;
    //     memcpy(p_, a.get_p(), sizeof(a.get_p()));
    // }
                                                                                                                 
    ~A() {
        std::cout << "Deconstruct!" << std::endl;
        delete []p_;
        p_ = nullptr;
    };                                                                                                           

    char* get_p() const {
        return p_;
    }

    void print() const {
        std::cout << p_ << std::endl;
    }

private:
    char* p_;
};                                                                                                               
                                                                                                                 
std::deque<A> g_dq;
                                                                                                                 
void func(const A& a) {
    g_dq.push_back(a);
}

int main() {
    int* test = new int(10);
    delete test;
    delete test;
    A a;

    // // bug 0
    // std::vector<A> vec;
    // vec.push_back(a);
    
    // vec.clear();
    // std::cout << "after clear, vec.size() " << vec.size() << std::endl;
    // std::cout << "after clear, vec.capacity() " << vec.capacity() << std::endl;
    
    // vec.erase(vec.begin());
    // std::cout << "after erase, vec.size() " << vec.size() << std::endl;
    // std::cout << "after erase, vec.capacity() " << vec.capacity() << std::endl;

    // bug 1
    g_dq.push_back(a);

    // A& a_ref = g_dq.front();
    // g_dq.pop_front();
    // a_ref.print();
    // std::cout << "after pop_front, g_dq.size() " << g_dq.size() << std::endl;

    // g_dq.erase(g_dq.begin());
    // std::cout << "after erase, g_dq.size() " << g_dq.size() << std::endl;
    
    // g_dq.clear();
    // std::cout << "after clear, g_dq.size() " << g_dq.size() << std::endl;

    // // bug 2
    // func(a);
    
    // bug 总结: 
    // 没有 copy constructor, 导致 push_back 和函数传参出问题, 只能通过默构构造函数来构造一个对象,
    // 结果该对象的 p_ 没有被正确初始化, 最终析构时出错

    return 0;
}

