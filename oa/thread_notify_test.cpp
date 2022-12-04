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

std::atomic_flag flag = ATOMIC_FLAG_INIT;

bool iotask() {
    cout << "[iotask] do an io task..." << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return true;
}

bool task1() {
    int64_t cnt1 = 0;

    while (true) {
        // cout << "[task1] do count" << endl;
        ++cnt1;
        if (cnt1 % 1000 == 0) cout << "[task1] cur cnt1 = " << cnt1 << endl;

        // 做了个测试, 这么写的话当前线程还是会阻塞执行 io 任务
        // if (cnt1 % 123 == 0) {
        //     cout << "[task1] gonna do an io task" << endl;
        //     // iotask();
        //     std::future<bool> io_thd = std::async(std::launch::async,
        //                                           iotask);
        // }

        if (cnt1 == 10000) {
            // Notify thread holding task2, but must be in non-blocking way
            cout << "[task1] gonna notify task2" << endl;
            flag.test_and_set();
            break;
        }

        // if (task1Finish()) break;
    }

    return true;
}

bool task2() {
    int64_t cnt2 = 0;

    while (true) {
        // cout << "[task2] do count" << endl;
        ++cnt2;
        if (cnt2 % 1000 == 0) cout << "[task2] cur cnt2 = " << cnt2 << endl;

        // 做了个测试, 这么写的话当前线程还是会阻塞执行 io 任务
        if (cnt2 % 3000 == 0) {
            cout << "[task2] gonna do an io task" << endl;
            // iotask();
            std::future<bool> io_thd = std::async(std::launch::async,
                                                  iotask);
        }
    
        // Thread is waiting to be notified by the thread holding task1, 
        // but must run in non-blocking way, sort of like `Channel` in Go
        if (flag.test()) {
            cout << "[task2] being notified" << endl;
            break;
        }

        // if (task2Finish()) break;
    }

    return true;
}

// 线程通知问题（xuezhang说和同步还有点不太一样，但是我感觉还是同步问题）
// 两线程线程 A 有一个变量 alpha，一旦变化就通知 (Notify) 线程 B
// 不想让线程 B 一直阻塞等待

int main() {
    vector<thread> threads;
    std::future<bool> thd1 = std::async(std::launch::async,
                                        task1);
    std::future<bool> thd2 = std::async(std::launch::async,
                                        task2);

    return 0;
}

