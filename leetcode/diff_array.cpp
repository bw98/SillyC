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

const int N = 1e5 + 10;
int a[N] = { 0 };  // 原数组
int b[N] = { 0 };  // 差分数组
int n;  // n 个整数
int m;  // m 个差分操作

void insert(int l, int r, int num) {
    b[l] += num;
    b[r + 1] -= num;
}

int main() {
    // Y 神模板题 前缀和 差分数组
    // TEST CASE
    // 参考 https://www.acwing.com/problem/content/799/
    //
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // 思路是, 先打标记, 再用前缀和得到最终累加的操作
    // 下面的 b 表示在 [1, 3] 区间加上了 -5, 同时 [4, 5] 区间不受影响，因为前缀和累加之后会抵消掉
    //
    // a      1  2  3  4  5
    // b     -5  0  0  5  0 
    // b_sum -5  -5 -5 0  0
    // a_now -4  -3 -2 4  5
    // 
    // l = 1, r = 3, num = -5
    //

    int l, r, num;
    while (m--) {
        cin >> l >> r >> num;
        insert(l, r, num);
    }

    for (int i = 1; i <= n; ++i) {
        b[i] += b[i - 1];
        a[i] += b[i];
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

