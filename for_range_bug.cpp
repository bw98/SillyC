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

int main() {
    vector<int> vec{1, 2, 3};
    for (int x : vec) {
        vec[0] = 0;
        printf("vec[0] %p %d\n", &vec[0], vec[0]);
        printf("x %p %d\n", &x, x);
    }

    // vector<int> vec{1};
    // for (int i = 0; i < vec.size(); ++i) {
    //     int x = vec[i];
    //     vec[i] = 0;
    //     printf("%p %d\n", &vec[i], vec[i]);
    //     printf("%p %d\n", &x, x);
    // }

    return 0;
}

