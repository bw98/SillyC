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

const int N = 1e5;
int n, m;
int target;
int a[N], b[N];

int main() {
    // 数组元素的目标和
    // 两个升序数组, 各拿出一个元素，它们的和刚好等于某个值
    //
    // 双指针, 一个指小，一个指大，然后往中间夹
    // 参考: https://www.acwing.com/problem/content/802/
    cin >> n >> m >> target;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    // 6
    // 1 2 4 7
    // i
    // 3 4 6 8 9
    //   j
    //
    for (int i = 0, j = m - 1; i < n; ++i) {
        while (j >= 0 && a[i] + b[j] > target) {
            --j;
        }

        if (a[i] + b[j] == target) cout << i << " " << j << endl;
    }

    return 0;
}

