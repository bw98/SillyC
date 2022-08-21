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
using namespace std::placeholders;

// Functionality of callback: class A composed the function `add` from B

class B {
public:
    int add(int64_t x, int64_t y) {
        int64_t sum = x + y;
        if (cb_func_) {
            cb_func_(sum);
        }
        return sum;
    }

    void set_add_cb(const std::function<void(int64_t)>& cb_func) {
        cb_func_ = cb_func;
    }

private:
    std::function<void(int64_t)> cb_func_;
};

class A {
public:
    A() : cnt_(0) {}

    static void printResult(int64_t res, bool do_format) {
        if (do_format) {
            std::cout << "[A::printResult] print result, res = " << res << std::endl;
        } else {
            std::cout << "res = " << res << std::endl;
        }
    }

    void IncrPrintFuncCallCnt() {
        ++cnt_;
        std::cout << "[A::IncrPrintCnt] cnt = " << cnt_ << std::endl;
    }

    void doBigTask() {
        // Do part of B:add
        B b;

        b.set_add_cb(std::bind(&A::printResult, std::placeholders::_1, false));
        b.add(1, 2);
        IncrPrintFuncCallCnt();

        b.set_add_cb(std::bind(&A::printResult, std::placeholders::_1, true));
        b.add(4, 6);
        IncrPrintFuncCallCnt();

        // ...
    }

private:
    int64_t cnt_;
};

int main() {
    B b;
    // b.set_add_cb(print);
    int sum = b.add(0, 1);
    std::cout << "[main] sum = " << sum << std::endl;

    A a;
    a.doBigTask();

    return 0;
}

