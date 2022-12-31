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
#include <future>

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
using std::future;
using std::async;

int n;  // n 次操作
int m;  // m 次 query

int main() {
    // 在一个数轴上给出一些整数, 求出在区间 [l,r] 之间的所有数的和
    // 整数离散化模板题
    //
    // 不过用 前缀和 就能直接做了, 开一个大数组对值域做一一映射, 然后用 sum[r] - sum[l-1] 得到区间和
    // 或者, 不再讲值域一一映射而是用 binary search 去找第一个大等于 l/r 的数, 并使用 sum[r] - sum[l-1] 得到区间和
    //
    // 参考: https://www.acwing.com/problem/content/description/804/

    return 0;
}

