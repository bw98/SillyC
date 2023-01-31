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
#include <chrono>

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

bool bufferFileLoader() {
    // Load file data and return true when it completed
    size_t bytes = 0;
    while (bytes < 20000) {
        std::cout << "[Test2] Loading file..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        bytes += 1024;
    }
    return true;
}

int main() {
    //
    // Test1: create aysnc function and try to get the result of it immediately
    //
    std::future<int> async_func = std::async([](int x)->int { return x * x; },
                                             10);
    int res = async_func.get();
    std::cout << "[Test1] " << res << std::endl;

    //
    // Test2: Background loads file data
    //
    std::future<bool> bg_thd = std::async(std::launch::async,
                                          bufferFileLoader);
    std::future_status status;
    std::cout << "[Test2] Aysnc task is ready to run" << std::endl;
    // Main loop
    while (true) {
        std::cout << "[Test2] Main Loop is running" << std::endl;
        // mimic IO
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        status = bg_thd.wait_for(std::chrono::milliseconds(1));
        // Check If data is ready
        if (status == std::future_status::ready) {
            std::cout << "[Test2] file data is all loaded..." << std::endl;
            break;
        }
    }

    return 0;
}

