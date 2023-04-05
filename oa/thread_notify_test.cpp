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
using std::deque;
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

bool iotask(int sec) {
    cout << "[iotask] do an io task on thread " << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sec *1000));
    return true;
}

bool task1() {
    cout << "[task1] task1 on thread " << std::this_thread::get_id() << endl;
    int64_t cnt = 0;
    while (true) {
        ++cnt;
        if (cnt % 10 == 0) cout << "[task1] Go into task1 main loop " << cnt  << " times" << endl;

        // Fake an time-cost task on current thread
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Notify thread holding task2, but must be in non-blocking way
        if (cnt == 100) {
            cout << "[task1] gonna notify task2 because flag will be changed" << endl;
            flag.test_and_set();
            break;
        }

        // if (task1Finish()) break;
    }

    return true;
}

bool task2() {
    cout << "[task2] task2 on thread " << std::this_thread::get_id() << endl;
    int64_t cnt = 0;
    int future_task_num = 0;
    int future_task_done = 0;
    // 想在线程 B 异步执行 io task 的话，必须要保证 future 对象不在 main loop 中被析构,
    // 否则其会转成同步对象并阻塞线程B 
    // 详情参考 stackoverflow.com/questions/44654548/stdasync-doesnt-work-asynchronously
    list<future<bool>> future_tasks;
    while (true) {
        ++cnt;
        if (cnt % 1000000 == 0) cout << "[task2] Go into task2 main loop " << cnt  << " times" << endl;

        // Async run io task
        if (cnt % 50000 == 0 && future_task_num < 3) {
            cout << "[task2] gonna do an io task" << endl;
            ++future_task_num;
            std::future<bool> f = std::async(std::launch::async, iotask, future_task_num);
            future_tasks.push_back(std::move(f));
        }

        for (auto iter = future_tasks.begin(); iter != future_tasks.end(); ) {
            auto status = iter->wait_for(std::chrono::milliseconds(0));
            if(status == std::future_status::ready) {
                ++future_task_done;
                cout << "[task2] " << future_task_done << " IO tasks get done" << endl;
                iter = future_tasks.erase(iter);
            } else {
                ++iter;
            }
        }
    
        // Check 线程 A 的通知
        if (flag.test()) {
            cout << "[task2] being notified" << endl;
            break;
        }

        // if (task2Finish()) break;
    }

    return true;
}

// niu学长出的线程通知问题
// 两线程线程 A 有一个变量 flag，一旦变化就通知 (Notify) 线程 B, 不想让线程 B 一直阻塞等待

int main() {
    vector<thread> threads;
    std::future<bool> thd1 = std::async(std::launch::async,
                                        task1);
    std::future<bool> thd2 = std::async(std::launch::async,
                                        task2);

    return 0;
}

