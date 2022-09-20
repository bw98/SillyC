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

class Solution {
public:
    // 很容易想到时滑动窗口，但是在求子数组的最小最大值的时候就卡住了
    // 如何快速地求数组区间 max() 和 min()，即滑动窗口的最大值和最小值? 
    // 方法:
    //   - map，保存出现次数，可自动排序 key. 当一个数字的次数为0的时候，要erase掉
    //   - 使用两个优先级队列找最大和最小
    //   - 使用二分维护一个排序数组
    //   - 使用 multiset，它可以允许出现重复元素, 并且自动排序
    int longestSubarray(std::vector<int>& nums, int limit) {
        size_t n = nums.size(), left = 0, right = 0;
        int res = 0;
        map<int, int> freq;
        while (right < n) {
            freq[nums[right]] += 1;
            auto min_iter = freq.begin(),  // stop using std::min_element, coz it's time complexity is O(n)
                 max_iter = std::prev(freq.end());
            int diff = max_iter->first - min_iter->first;
            while (diff > limit && left < right) {
                auto rm_iter = freq.find(nums[left]);
                if (rm_iter->second == 1) freq.erase(rm_iter);
                else rm_iter->second -= 1;
                ++left;
                
                min_iter = freq.begin(),
                max_iter = std::prev(freq.end());
                diff = max_iter->first - min_iter->first;
            }
                 
            res = std::max(res, (int)(right - left + 1));
            ++right;
        }
        
        return res;
    }
};

int main() {
    vector<int> input = {
        10, 1, 2, 4, 7, 2
    };

    int limit = 5;

    Solution s;
    int res = s.longestSubarray(input, limit);
    std::cout << res << std::endl;

    return 0;
}

