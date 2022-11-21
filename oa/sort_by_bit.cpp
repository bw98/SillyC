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

void sortByBit(vector<int>& nums) {
    sort(nums.begin(), nums.end(),
         [](int a, int b) -> bool {
             int a_bit_cnt = 0, b_bit_cnt = 0;
             while (a) {
                if (a & 1) a_bit_cnt += 1;
                a = a >> 1;
             }
             while (b) {
                if (b & 1) b_bit_cnt += 1;
                b = b >> 1;
             }
             return a_bit_cnt < b_bit_cnt;
         });
}

int main() {
    vector<int> array = { 1, 2, 5, 7, 8 };
    for (int x : array) {
        cout << x << ", ";
    }
    cout << endl;

    sortByBit(array);
    for (int x : array) {
        cout << x << ", ";
    }
    cout << endl;


    return 0;
}

