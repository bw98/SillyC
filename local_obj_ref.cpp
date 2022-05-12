#include <iostream>

class Person {
public:
    Person(int age) : age(age) {
    }
    
    ~Person() {
      std::cout << "Delete Person" << std::endl;
    }

public:
  int age;
};

const Person& test() {
  const Person&p = Person(666);
  // std::cout << "address1: " << &p << std::endl;
  return p;
}

int main(int argc, char const *argv[]) {
  const Person& p = test();
  // 去掉注释后，输出结果就不一样了！
  // std::cout << "address2: " << &p << std::endl;
  std::cout << p.age << std::endl;
  return 0;
}

