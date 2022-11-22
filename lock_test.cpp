#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>

using std::vector;
using std::thread;
using std::mutex;
using std::atomic;
 
class SpinLock {
 public:
    SpinLock() = default;
    SpinLock(const SpinLock&) = delete;
    SpinLock& operator= (const SpinLock&) = delete;

 public:
    void lock() {
        // CAS, 原子比较(读) + 原子交换(写)
        // 如果 atmoic 对象 flag_ 没有达到预期值就一直进行循环等待，当预期值相等的时候，进行交换
        bool expected = false;
        while (!flag_.compare_exchange_strong(expected, true)) {
            expected = false;
        }
    }

    void unlock() {
        flag_.store(false);
    }

 private: 
    std::atomic<bool> flag_ = ATOMIC_VAR_INIT(false);
    // std::atomic<bool> flag_;  // 默认初始化同上
};
 
const int size = 100000;
int total = 0;
std::atomic_long total2(0);
std::mutex mtx;
SpinLock spin_lock;
 
void thread_click() {
    for (int i = 0; i < size; ++i) {
        ++total;
    }
}
 
void mutex_click() {
    for (int i = 0; i < size; ++i) {
        mtx.lock();
        ++total;
        mtx.unlock();
    }
}
 
void atomic_click() {
    for (int i = 0; i < size; ++i) {
        ++total2;
    }
}
 
void spin_lock_click() {
    for (int i = 0; i < size; ++i) {
        spin_lock.lock();
        ++total;
        spin_lock.unlock();
    }
}
 
int main() {
    int thd_num = 100;
    std::vector<std::thread> threads(thd_num);
    clock_t start, end;
 
    // single thread
    total = 0;
    start = clock();
    for (int i = 0; i < size * thd_num; i++) {
        ++total;
    }
    end = clock();
    std::cout << "single thread result: " << total << std::endl;
    std::cout << "single thread time: " << end - start << std::endl;
 
    // multi thread without mutex
    // Data race!
    total = 0;
    start = clock();
    for (int i = 0; i < thd_num; ++i) {
        threads[i] = std::thread(thread_click);
    }
    for (int i = 0; i < thd_num; ++i) {
        threads[i].join();
    }
    end = clock();
    std::cout << "multi thread no mutex result: " << total << std::endl;
    std::cout << "multi thread no mutex time: " << end - start << std::endl;
 
    // multi thread with atomic
    total = 0;
    start = clock();
    for (int i = 0; i < thd_num; ++i) {
        threads[i] = std::thread(atomic_click);
    }
    for (int i = 0; i < thd_num; ++i) {
        threads[i].join();
    }
    end = clock();
    std::cout << "multi thread atomic result: " << total2 << std::endl;
    std::cout << "multi thread atomic time: " << end - start << std::endl;
 
    // multi thread with mutex
    total = 0;
    start = clock();
    for (int i = 0; i < thd_num; ++i) {
        threads[i] = std::thread(mutex_click);
    }
    for (int i = 0; i < thd_num; ++i) {
        threads[i].join();
    }
    end = clock();
    std::cout << "multi thread mutex result: " << total << std::endl;
    std::cout << "multi thread mutex time: " << end - start << std::endl;
 
    // multi thread with spnning lock (implemented by C++11 atomic + while)
    total = 0;
    start = clock();
    for (int i = 0; i < thd_num; ++i) {
        threads[i] = std::thread(spin_lock_click);
    }
    for (int i = 0; i < thd_num; ++i) {
        threads[i].join();
    }
    end = clock();
    std::cout << "spin lock result: " << total << std::endl;
    std::cout << "spin lock time: " << end - start << std::endl;

    return 0;
}

