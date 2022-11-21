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


int main() {
    vector<bool> vec { false, true, false };
    bool a = vec[0];
    auto b = vec[0];  // The type of object b is std::vector<bool>::reference
    b = true;  // Warning, vec[0] got changed!

    for (size_t i = 0; i < vec.size(); ++i) {
        cout << "i: " << i << ", vec[i]: " << vec[i] << endl;
    }
    cout << endl;

    vec.clear();
    // delete vec[0];  // 执行这条代码的话 gcc 会报错, 因为该 proxy ref 无法被析构, 可以跑一下做个实验
    b = false;  // Obj b is still binded with mem of vec[0], so it's an undefined behavior..

    return 0;
}

