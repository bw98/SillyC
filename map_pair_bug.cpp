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
    // map pair 的key 是 const
    unordered_map<string, int> hash;
    hash.emplace("1", 2);
    hash.emplace("3", 4);
    hash.emplace("5", 6);
    for (auto& kv : hash) {
        printf("%p\n", &kv);
    }
    for (pair<string, int>& kv : hash) {  // 拷贝浪费
        printf("%p\n", &kv);
    }

    return 0;
}

