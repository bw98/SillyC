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

int SHARED_VALUE = 0;

void incre_shared_value() {
    SHARED_VALUE += 1;
}

int main() {
    std::vector<std::thread> thd_vec;
    thd_vec.reserve(10);

    // 编译链接时加入 sanitizer, 然后就可以在运行时检测 data race
    // g++ -std=c++20 multi_thread_write_bug.cpp -fsanitize=thread -lpthread
	for (size_t i = 0; i < 100; ++i) {
        thd_vec.push_back(std::thread(&incre_shared_value));
	}

    for (size_t i = 0; i < 100; ++i) {
        thd_vec[i].join();
    }

    std::cout << "Current SHARED_VALUE is " << SHARED_VALUE << std::endl;

    return 0;
}

