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
int a[N];
int cnt[10];
int n;  // n 个数
int res;

int main() {
    // AcWing 799. 最长连续不重复子序列
    // 双指针 (其实就是滑动窗口)
    // 参考 https://www.acwing.com/problem/content/801/
    // 元素全是数字
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0, j = 0; i < n; ++i) {
       cnt[a[i]] += 1;
       while (j <= i && cnt[a[i]] > 1) {
           cnt[a[j++]] -= 1;
       }

       res = std::max(res, i - j + 1);
    }

    cout << res << endl;

    return 0;
}

