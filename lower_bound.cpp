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

int my_lower_bound(const vector<int>& vec, int target) {
    int left = 0, right = vec.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return vec[left];
}

int my_upper_bound(const vector<int>& vec, int target) {
    int left = 0, right = vec.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return vec[left];
}

int main() {
    // 实现一个 std::lower_bound()
    vector<int> vec{1, 4, 4, 5, 6, 11, 19, 20};
    int res = my_lower_bound(vec, 4);
    cout << res << endl;
    
    auto it = std::lower_bound(vec.begin(), vec.end(), 4);
    cout << *it << endl;

    // 实现一个 std::upper_bound()
    res = my_upper_bound(vec, 4);
    cout << res << endl;
    
    it = std::upper_bound(vec.begin(), vec.end(), 4);
    cout << *it << endl;

    return 0;
}

