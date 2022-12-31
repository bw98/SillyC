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

const int N = 100001;

int n, k;
int q[N];

//
// Y 神模板快排, 左闭右闭, 然后当成左开右开往中间遍历. 每轮排序后判断 k 在左半边还是在右半边
// l 和 r 所在的区间是 topk 元素所在的区间
//
int quick_select(int l, int r, int k) {
    if (l == r) return q[l];

    int i = l - 1, j = r + 1, x = q[l];
    while (i < j) {
        while (q[++i] < x);
        while (q[--j] > x);
        if (i < j) std::swap(q[i], q[j]);
    }

    int lsize = j - l + 1;
    if (lsize >= k) return quick_select(l, j, k);

    return quick_select(j + 1, r, k - lsize);
}

int main() {
    // n = number of n
    // k = The top k smallest element in array
    // test case
    // INPUT: 
    //  5 3
    //  2 4 1 5 3
    //
    // OUTPUT: 
    //  3
    cin >> n >> k;
    for(int i = 0; i < n; ++i) cin >> q[i];
    cout << quick_select(0, n - 1, k) << endl;

    return 0;
}

