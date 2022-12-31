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

const int N = 100;

int n, m;  // n 行 m 列
int quary;  // q 个 query
int a1, b1, a2, b2;  // 查询的坐标
int q[N][N];
int sum[N+1][N+1] = { 0 };

// 预先计算前缀和
void get_matrix_presum() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + q[i][j];
        }
    }

    // // debug
    // cout << "\npresum: " << endl;
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         cout << sum[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
}

// 通过两点坐标计算该矩阵的和
int get_submatrix_sum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

int main() {
    // 
    // Y 神基础课模板题
    // Test Case
    //
    // INPUT
    // 3 4 3
    // 1 7 2 4
    // 3 6 2 8
    // 2 1 2 3
    // 1 1 2 2
    // 2 1 3 4
    // 1 3 3 4
    //
    // OUTPUT
    // 17
    // 27
    // 21
    //
    cin >> n >> m >> quary;
    for(int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> q[i][j];
        }
    }

    // // debug
    // cout << "\nq array: " << endl;
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         cout << q[i][j] << ", ";
    //     }
    //     cout << endl;
    // }

    get_matrix_presum();

    for (int i = 0; i < quary; ++i) {
        cin >> a1 >> b1 >> a2 >> b2;
        cout << get_submatrix_sum(a1, b1, a2, b2) << endl;
    }

    return 0;
}

