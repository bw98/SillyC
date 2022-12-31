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

const int N = 1e2 + 10;
int a[N + 1][N + 1] = { 0 };  // 原数组
int b[N + 1][N + 1] = { 0 };  // 差分数组
int n;  // n 行
int m;  // m 列
int q;  // q 个差分操作

void insert(int x1, int y1, int x2, int y2, int num) {
    // 对 b 数组执行插入操作，等价于对 a 数组中的 (x1,y1) 到 (x2,y2) 之间的元素都加上了 num
    b[x1][y1] += num;
    b[x2 + 1][y1] -= num;
    b[x1][y2 + 1] -= num;
    b[x2 + 1][y2 + 1] += num;
}

int main() {
    // Y 神模板题 前缀和 差分矩阵 (2D数组)
    // 和差分数组是一个思路，然后再额外使用了求矩阵前缀和的算法
    // TEST CASE
    // 参考 https://www.acwing.com/problem/content/800/
    //
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    int x1, y1, x2, y2, num;
    while (q--) {
        cin >> x1 >> y1 >> x2 >> y2 >> num;
        insert(x1, y1, x2, y2, num);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            b[i][j] = b[i][j] + b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            a[i][j] += b[i][j];
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}

