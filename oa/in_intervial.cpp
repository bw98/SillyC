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

//
// 题目要求:
// p 和 q 分别是两个数对, 比如 [[2, 3], [4, 5], [2, 6]] 与 [[4, 5], [2, 3], [6, 13]]
// 分析是否能在 p 和 q 中各找到两个数对, 坐标分别是 i 和 j, 使得 p[i][0] <= q[j][0] <= q[j][1] <= p[i][1]
// 相当于是 p 中的一个数对把另一个数对给包了起来。函数返回 i 和 j
//

// 只想到了一种优化方法, 对数对的首元素排序, 比如 xi[1] < yj[0] 说明区间 x 连 y 的左边界都包不住, 
// 那么对于比 y 左边界还大的区间也是包不住, 因此直接跳过后续 y
//
// 有一个坑点, 排序会打乱坐标的顺序, 而函数需要返回排序前的坐标, 因此需要额外保存原始坐标信息

struct Item {
    int first;
    int second;
    int idx;
};

vector<int> in_interval(vector<vector<int>> p, vector<vector<int>> q) {
    vector<Item> x(p.size()), y(q.size());
    for (int i = 0; i < p.size(); ++i) {
        x[i].first = p[i][0];
        x[i].second = p[i][1];
        x[i].idx = i;
    }
    for (int i = 0; i < q.size(); ++i) {
        y[i].first = q[i][0];
        y[i].second = q[i][1];
        y[i].idx = i;
    }

    auto sort_first = [](Item& a, Item& b) -> bool { return a.first < b.first; };

    sort(x.begin(), x.end(), sort_first);
    sort(y.begin(), y.end(), sort_first);

    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < y.size(); ++j) {
            if (x[i].second < y[j].first) {
                break;
            }

            if (x[i].first <= y[j].first && x[i].second >= y[j].second) {
                // cout << x[i].first << ", " << y[j].first << ", " << x[i].second << ", " << y[j].second << endl;;
                return { x[i].idx, y[j].idx };
            }
        }
    }

    return { -1, -1 };
}

int main() {
    vector<vector<int>> a, b;

    a.push_back( {4, 6} );
    a.push_back( {9, 14} );
    a.push_back( {7, 15} );

    b.push_back( {8, 10} );
    b.push_back( {3, 6} );
    b.push_back( {6, 17} );

    std::for_each(a.begin(), a.end(), [](const vector<int>& item) { cout << "[" << item[0] << ", " << item[1] << "], "; });
    cout << endl;
    std::for_each(b.begin(), b.end(), [](const vector<int>& item) { cout << "[" << item[0] << ", " << item[1] << "], "; });
    cout << endl;

    auto res = in_interval(a, b);
    cout << res[0] << ", " << res[1] << endl;

    return 0;
}

