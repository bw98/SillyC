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

class LRU {
 public:
     LRU(int capacity) : capacity_(capacity) {}

     int get(int key) {
         const auto it = m_.find(key);
         if (it == m_.end()) return -1;

         // find this key
         cache_.splice(cache_.begin(), cache_, it->second);
         return it->second->second;
     }

     void put(int key, int val) {
         auto it = m_.find(key);
         if (it != m_.end()) {
             cache_.splice(cache_.begin(), cache_, it->second);
             it->second->second = val;
             return;
         }

         // cannot find this kv
         if (cache_.size() >= capacity_) {
            auto kv = cache_.back();
            m_.erase(kv.first);
            cache_.pop_back();
         }

         // auto iter = cache_.insert(cache_.begin(), {key, val});
         // m_[key] = iter;
         cache_.emplace_front(key, val);
         m_[key] = cache_.begin();
     }

     int getLen() {
         return cache_.size();
     }

 private:
     int capacity_;
     list<pair<int, int>> cache_;
     map<int, list<pair<int, int>>::iterator> m_;
};

int main() {
    LRU* lru = new LRU(2);
    lru->put(1, 3);
    lru->put(2, 2);
    lru->put(3, 1);  // 踢掉 1

    int res = lru->get(1);
    cout << res << endl;  // 预期结果：-1

    res = lru->get(2);
    cout << res << endl;  // 预期结果 2

    lru->put(4, 1);  // 踢掉 3
    res = lru->get(3);

    cout << res << endl;  // 预期结果：-1
    
    delete lru;
    
    return 0;
}

