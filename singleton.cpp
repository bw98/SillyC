#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <memory>
#include <functional>
#include <utility>
#include <random>
#include <unistd.h>
#include <thread>

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
using std::unordered_set;
using std::multimap;
using std::multiset;
using std::shared_ptr;
using std::make_shared;
using std::allocator;
using std::stringstream;

class Test {
 public:
     static Test& GetInstance() {
         static Test t;

         return t;
     }

     // Test() = default;
     Test() {
         cout << "constructor..." << endl;
     }
     // ~Test() = default;
     ~Test() {
         cout << "destructor..." << endl;
     }
     Test(const Test&) = delete;
     Test& operator = (const Test&) = delete;

 private:
     string buffer_;
};

int main() {
    Test& t = Test::GetInstance();

    {
        Test& t2 = t;
    }

    cout << "t2 has been dead......" << endl;

    return 0;
}

