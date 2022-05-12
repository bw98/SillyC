#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;
 
class spin_lock {
 public:
    spin_lock() = default;
    spin_lock(const spin_lock&) = delete;
    spin_lock& operator= (const spin_lock&) = delete;

 public:
    void lock() {
        bool expected = false;
        while (!flag.compare_exchange_strong(expected, true)) expected = false;
    }

    void unlock() {
        flag.store(false);
    }

 public: 
    std::atomic<bool> flag = ATOMIC_VAR_INIT(false);
};
 
long size = 100000;
long total = 0;
std::atomic_long total2(0);
std::mutex mtx;
spin_lock spin_lock;
 
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

