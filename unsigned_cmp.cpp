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
    // uint64_t -1 和 0 判断会有问题
    uint64_t i = 0;
    uint64_t j = i - 1;
    if (j < 0) {
        std::cout << "j < 0" << std::endl;
    } else {
        std::cout << "Count Wrong, j ?< 0" << std::endl;
    }
    
    // uin64_t 与 i = 0 遍历的隐藏 BUG
    std::vector<int> vec;
    for (std::vector<int>::size_type i = 0; i < vec.size() - 1; ++i) {
        std::cout << "Count Wrong, i < vec.size() - 1" << std::endl;
    }

    return 0;
}

