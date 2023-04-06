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
#include <deque>
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
using std::iota;
using std::to_string;
using std::vector;
using std::string;
using std::array;
using std::list;
using std::forward_list;
using std::queue;
using std::priority_queue;
using std::stack;
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
using std::condition_variable;
using std::atomic;
using std::future;
using std::async;

/*
读写锁基本思想: 写者之间互斥, 写者和读者之间互斥, 而读者之间并不需要互斥
读写锁分为两种: 读者优先和写者优先;
    读者优先, 即当前只要可读, 就是可进入的;
    写者优先, 读者需要看看当前是否有写者要读, 如果有, 则等待至没有写者正在写或者需要写的情况

读写锁的两种方式，都会存在饥饿(starvation)现象
*/

class ReadWriteLock {
public:
    ReadWriteLock(bool writerFirst = false) : writerFirst_(writerFirst) {

    }

    void
    readLock() {
        unique_lock lck(mtx_);
        ++read_wait_;
        cv_.wait(lck, [&]() { return writing_ <= 0 && (!writerFirst_ || write_wait_ <= 0); });
        --read_wait_;
        ++reading_;
    }

    void
    readUnlock() {
        unique_lock lck(mtx_);
        --reading_;
        // 如果没有读者了，才唤醒写者
        if (reading_ <= 0) {
            cv_.notify_one();
        }
    }

    void
    writeLock() {
        unique_lock lck(mtx_);
        ++write_wait_;
        cv_.wait(lck, [&]() { return writing_ <= 0 && reading_ <= 0; });
        --write_wait_;
        ++writing_;
    }

    void
    writeUnlock() {
        unique_lock lck(mtx_);
        --writing_;
        cv_.notify_all();
    }

private:
    bool writerFirst_;
    atomic<int> reading_;
    atomic<int> writing_;
    atomic<int> read_wait_;
    atomic<int> write_wait_;
    mutex mtx_;
    condition_variable cv_;
};

ReadWriteLock LCK(true);

void
reader() {
	LCK.readLock();
	cout << "reader" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
	LCK.readUnlock();
}

void
writer() {
	LCK.writeLock();
	cout << "writer" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
	LCK.writeUnlock();
}

int
main() {
    vector<thread> thds;
	for (int i = 0; i < 5; ++i) {
		thds.push_back(thread(reader));
		thds.push_back(thread(writer));
	}
    for (auto& thd : thds) {
        thd.join();
    }

    return 0;
}

