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

void qsort(vector<int>& nums, int l, int r) {
    if (l >= r) return;

    int i = l - 1, j = r + 1;
    int mid = l + (r - l) / 2, x = nums[mid];

    while (i < j) {
        do {
            ++i;
        } while (nums[i] < x);

        do {
            --j;
        } while (nums[j] > x);

        if (i < j) std::swap(nums[i], nums[j]);
    }

    qsort(nums, l, j);
    qsort(nums, j + 1, r);
}

int main() {

    // vector<int> nums { 3, 1, 4, 6, 12,5 };
    // vector<int> nums { 1, 3, 5, 7, 25 };
    vector<int> nums { 49, 59, 88, 37, 3, 97, 68, 54, 31, 98 };
    
    int n = nums.size();
    qsort(nums, 0, n - 1);

    std::for_each(nums.begin(), nums.end(),
                  [](int& x) {
                        cout << x << ", ";
                  });
    cout << endl;

    return 0;
}

