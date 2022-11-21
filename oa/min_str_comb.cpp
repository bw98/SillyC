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

// 给一个 string, 它最多只包含 abc 三种字母。其中相邻的 a 和 b 可以互换，b 和 c 相邻可以互换。求互换后最小的 string。
// 解法: b 可以随便换位置，所以把所有 b 怼到第一个 c 之前。没有 c 就放最后
// Example: "bbbaacb"换完后最小是"aabbbbc"
string getMinStr(const string& s) {
    size_t first_c_idx = -1;
    int cnt[3] = { 0 };
    for (size_t i = 0; i < s.size(); ++i) {
        if (first_c_idx == -1 && s[i] == 'c') {
            first_c_idx = i;
        }

        cnt[s[i] - 'a'] += 1;
    }

    string res;
    if (first_c_idx == -1) {
        res.reserve(cnt[0] + cnt[1]);
        res.append(cnt[0], 'a');
        res.append(cnt[1], 'b');
    } else {
        res.reserve(s.size());
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] != 'b') {
                if (i == first_c_idx) {
                    res.append(cnt[1], 'b');
                }

                res.push_back(s[i]);
            }
        }
    }

    return res;
}

int main() {
    string a = "bbaccbbacb";
    cout << a << endl;
    // Expected answer: "abbbbbccac"
    cout << getMinStr(a) << endl;

    return 0;
}

