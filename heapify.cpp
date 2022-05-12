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

void
heapify(vector<int>& vec, int start, int end) {
    int parent = start;
    int max_son = 2 * parent + 1;
    while (max_son <= end) {
        if (max_son + 1 <= end && vec[max_son] < vec[max_son + 1]) {
            max_son += 1;
        }

        if (vec[parent] < vec[max_son]) {
            std::swap(vec[parent], vec[max_son]);
            parent = max_son;
            max_son = 2 * parent + 1;
        } else {
            return;
        }
    }
}

int main() {
    // 建堆的过程
    vector<int> v{5, 1, 2, 4, 3};

    for (const int x : v) {
        cout << x << endl;
    }

    for (int i = v.size() / 2 - 1; i >= 0; --i) {
        heapify(v, i, v.size() - 1);
    }

    cout << "-----------------" << endl;

    for (const int x : v) {
        cout << x << endl;
    }

    return 0;
}
