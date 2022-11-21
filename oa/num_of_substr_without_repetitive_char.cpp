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
#include <mutex>
#include <shared_mutex>
#include <atomic>

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
using std::weak_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::allocator;
using std::stringstream;
using std::thread;
using std::mutex;
using std::shared_mutex;
using std::lock_guard;
using std::unique_lock;
using std::shared_lock;

//
// 给一个 string, 求没有重复字符的 substring 的个数
//
// 和 leetcode Q3 不是完全一样的题 (不过可能还可以试试 sliding window?)
//
// Input: ababc
//
// 该串的子串一共有 15 个
// 子串    个数
//  a       2 
//  b       2
//  c       1
// ab       2
// aba      1
// abab     1
// ababc    1
// ba       1
// bab      1
// babc     1
// abc      1
// bc       1
//
// 其中, 不重复字符的子串有 a, b, c, ab, ba, abc, bc 七种, 总个数为 10 个
//
// Output: 10
//
int func(const string& s) {
    int res = 0;

    // 暂时只想到了暴力

    return res;
}

int main() {
    string s = "ababc";
    cout << s << endl;
    cout << func(s) << endl;

    return 0;
}

