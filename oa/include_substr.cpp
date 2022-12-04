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

// Get the number of repetitive and consecutive short_s in long_s
//
// Example:
//     string short_s("AB");
//     string long_s("ABCABCABAB");
//
// 1 "AB" found in the start of long_s
// 2 repetitive "AB" are found at the end of long_s and they are consecutive
// Therefore the max number of repetitive and consecutive short_s found in long_s is 2
//
int RepetitionNum(const string& short_s, const string& long_s) {
    int short_len = short_s.size(), long_len = long_s.size();
    int i = 0;
    int last_match_pos = INT_MIN;
    int cur_short_num = 0;
    int res = INT_MIN;
    while (i < long_len) {
        if (i + short_len <= long_len) {
            if (long_s[i] == short_s[0]) {
                bool match = true;
                int p = i, q = 0, dst = i + short_len;
                while (p < dst) {
                    if (long_s[p] == short_s[q]) {
                        ++p;
                        ++q;
                    } else {
                        match = false;
                    }
                }

                if (match) {
                    if (last_match_pos + short_len == i) {
                        cur_short_num += 1;
                    } else {
                        cur_short_num = 1;
                    }
                    last_match_pos = i;
                    res = std::max(res, cur_short_num);
                    i = i + short_len - 1;
                }
            }
        } else {
            break;
        }
        
        ++i;
    }

    return res;
}

int main() {
    string short_s("AB");
    // string long_s("ABABC");
    string long_s("ABCABCABAB");
    cout << RepetitionNum(short_s, long_s) << endl;

    return 0;
}

