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

struct Item {
    int val;
    size_t idx;
};

int main() {
    vector<int> nums = { 1, 2, 5, 4, 3 };
    cout << "Original array is ";
    std::for_each(nums.begin(), nums.end(), [](int x) { cout << x << ", "; });
    cout << endl;
    // sort(nums.begin(), nums.end());
    // 此时如果需要输出最大元素在(原)数组中的位置, 就无能为力了

    vector<Item> items(nums.size());
    for (size_t i = 0; i < nums.size(); ++i) {
        items[i].val = nums[i];
        items[i].idx = i;
    }
    sort(items.begin(), items.end(),
         [](Item& a, Item& b) { return a.val < b.val; }
    );
    cout << "Max element is " << prev(items.end())->val << 
        ", its idx in original array is " << prev(items.end())->idx << endl;

    return 0;
}

