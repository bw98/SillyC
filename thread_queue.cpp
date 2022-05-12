#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <numeric>
#include <chrono>
#include <cassert>

/*
 * 自己写着玩的，可以对比下面的资料, 进一步完善
 * 参考资料: http://dengzuoheng.github.io/cpp-concurrency-pattern-8-blocking-queue
 */

template<typename T>
class ConcurrentQueue {
public:
    ConcurrentQueue() : max_sz_(1), sz_(0) {}
    ConcurrentQueue(size_t max_size) : max_sz_(max_size), sz_(0) {}
    
    size_t size() const {
        return sz_;
    }

    size_t dq_size() const {
        return dq_.size();
    }

    void enqueue(T t) {
        std::scoped_lock lock(mtx_);
        if (sz_ >= max_sz_) return;

        dq_.push_back(t);
        ++sz_;
    }

    std::pair<bool, T> dequeue() {
        std::scoped_lock lock(mtx_);
        if (sz_ > 0) {
            T front = dq_.front();
            dq_.pop_front();
            --sz_;
            return {true, front};
        }

        return {false, T()};
    }

    T& operator [] (size_t index) {
        std::scoped_lock lock(mtx_);
        assert(index < sz_);
        return dq_[index];
    }

private:
    std::deque<T> dq_;
    std::mutex mtx_;
    std::atomic<uint64_t> sz_;
    size_t max_sz_;
};

template<typename T>
void in_test(const std::vector<T>& data, ConcurrentQueue<T>& cq) {
    for (const T& x : data) {
        cq.enqueue(x);
    }
}

template<typename T>
void out_test(size_t cnt, ConcurrentQueue<T>& cq) {
    for (size_t i = 0; i < cnt; ++i) {
        auto p = cq.dequeue();
    }
}

int main() {
    ConcurrentQueue<int> cq(15);
    std::vector<int> data(100000);
    std::iota(data.begin(), data.end(), 0);
    auto in_thd = std::thread(in_test<int>, std::ref(data), std::ref(cq));
    auto out_thd = std::thread(out_test<int>, data.size(), std::ref(cq));
    in_thd.join();
    out_thd.join();

    // Check output
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << cq.size() << std::endl;
    std::cout << cq.dq_size() << std::endl;
    size_t sz = cq.size();
    for (size_t i = 0; i < sz + 10; ++i) {
        auto p = cq.dequeue();
        std::cout << "dequeue status: " << p.first << ", value: " << p.second << std::endl;
        // std::cout << "cq[i]: " << cq[i] << std::endl;
        std::cout << "size: " << cq.size() << std::endl;
    }
}

