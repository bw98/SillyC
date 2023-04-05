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

class Solution {
public:
    // Move all zeros in vector to the most right, and keep other numbers in the original order
    // Space complexity should be O1
    
    // 方法一: 套了一层循环, 挪动次数过多
    void moveZeroRight_2(vector<int>& nums) {
        int n = nums.size();
        // two pointer i j
        // j points to the postion which will be filled by next 0
        // 模拟将数列往前“挪”并将0放最后的过程, After each round, [i, j) means a seq without 0
        for (int i = n - 1, j = n - 1; i >= 0; --i) {
            if (!nums[i]) {
                for (int k = i; k < j; ++k) {
                    nums[k] = nums[k + 1];
                }
                nums[j--] = 0;
            }
        }
    }

    // 方法二: 也是双指针, 不过 j 的作用不再是指向 0 要填充的位置, 而是非0数要填充的位置
    void moveZeroRight(vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = 0;
        for (; i < n; ++i) {
            if (!nums[i]) {
                continue;
            } else {
                nums[j++] = nums[i];
            }
        }

        while (j < n) {
            nums[j++] = 0;
        }
    }
    

};

int main() {
    vector<int> nums = {3, 0, 7, 6, 5, 0, 2};
    // vector<int> nums = {3, 0, 7, 6, 0, 0};
    cout << "INPUT:" << endl;
    std::for_each(nums.begin(), nums.end(),
            [](const int a)->void {
                cout << a << " ";
            });
    cout << endl;

    Solution solution;
    solution.moveZeroRight(nums);

    cout << "OUTPUT:" << endl;
    std::for_each(nums.begin(), nums.end(),
            [](const int a)->void {
                cout << a << " ";
            });
    cout << endl;

    return 0;
}

