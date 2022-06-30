#include <iostream>
#include <string>

template<typename T>
void print(T& t){
    std::cout << "l value" << std::endl;
}

template<typename T>
void print(T&& t){
    std::cout << "r value" << std::endl;
}

template<typename T>
void testForward(T&& v){  // 虽然参数 v 是右值类型的, 但此时 v 在内存中已经有了位置, 所以 v 其实是个左值
    print(v);
    print(std::forward<T>(v));
    print(std::move(v));
}

int main() {
    std::cout << "======================" << std::endl;

    testForward(1);

    std::cout << "======================" << std::endl;

    int x = 1;
    testForward(x);
    // testForward(std::move(x));  // 也就是 testForward(static_cast<int&&>(x))

    std::cout << "======================" << std::endl;

    std::string str("test obj");
    testForward(str);

    std::cout << "======================" << std::endl;

    return 0;
}

