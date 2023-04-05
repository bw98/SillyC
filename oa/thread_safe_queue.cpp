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
 * C++17, 自己写着玩的，可以对比下面的资料, 进一步完善
 * 参考资料: http://dengzuoheng.github.io/cpp-concurrency-pattern-8-blocking-queue
 */

template<typename T>
class ConcurrentQueue {
public:
    ConcurrentQueue() : max_size_(1), size_(0) {}
    ConcurrentQueue(size_t max_size) : max_size_(max_size), size_(0) {}
    
    size_t
    size() const {
        return size_;
    }

    size_t
    dq_size() const {
        return dq_.size();
    }

    template <typename... Args>
    void
    enqueue(Args&&... args) {
        std::scoped_lock lock(mtx_);
        if (size_ >= max_size_) return;

        dq_.emplace_back(std::forward<Args...>(args...));  // 支持使用多个变参 in place 构造新元素
        ++size_;
    }

    // template <typename... Args>
    // void
    // enqueue_blocking(Args&&... args) {
    //     std::unique_lock lock(mtx_);
    //     // if (size_ >= max_size_) return;

    //     dq_.emplace_back(std::forward<Args...>(args...));  // 支持使用多个变参 in place 构造新元素
    //     ++size_;
    //     lock.unlock();
    //     cv.notify_one();
    // }

    std::pair<bool, T>
    dequeue() {
        std::scoped_lock lock(mtx_);
        if (size_ > 0) {
            T front = dq_.front();
            dq_.pop_front();
            --size_;
            return {true, front};
        }

        return {false, T()};
    }

    // T
    // dequeue_blocking() {
    //     std::unique_lock lock(mtx_);
    //     while (!size_) {
    //         cv.wait(lock, ???);  // 原子性地释放锁，并阻塞线程
    //     }

    //     T front = dq_.front();
    //     dq_.pop_front();
    //     --size_;
    //     return front;
    // }

    T&
    operator [] (size_t index) {
        std::shared_lock lock(mtx_);
        assert(index < size_);
        return dq_[index];
    }

    const T&
    operator [] (size_t index) const {
        std::shared_lock lock(mtx_);
        assert(index < size_);
        return dq_[index];
    }

private:
    std::deque<T> dq_;
    std::atomic<uint64_t> size_;
    uint64_t max_size_;
    std::shared_mutex mtx_;
    // std::condition_variable cv;
};

template<typename T>
void
in_test(const std::vector<T>& data, ConcurrentQueue<T>& cq) {
    for (const T& x : data) {
        // std::cout << "enqueue" << std::endl;
        cq.enqueue(x);
        // cq.enqueue_blocking(x);
    }
}

template<typename T>
void out_test(size_t cnt, ConcurrentQueue<T>& cq) {
    for (size_t i = 0; i < cnt; ++i) {
        // std::cout << "dequeue" << std::endl;
        auto p = cq.dequeue();
        // auto p = cq.dequeue_blocking();
    }
}

int main() {
    // Init data structure
    ConcurrentQueue<int> cq(10);

    // Init and start threads for adding and deleting items
    std::vector<int> data(100);
    std::iota(data.begin(), data.end(), 0);
    auto in_thd = std::thread(in_test<int>, std::ref(data), std::ref(cq));
    auto out_thd = std::thread(out_test<int>, data.size(), std::ref(cq));
    std::vector<std::thread> thds;
    thds.push_back(std::move(in_thd));
    thds.push_back(std::move(out_thd));
    for (auto& thd : thds) {
        thd.join();
    }

    // TODO: 按当前测试方法, 由于 queue 的max size 限制以及 unblocking get item, 
    //       导致多线程执行相同次数的 enqueue 和 dequeue 后 queue 还有剩余。
    //       解决办法是 queue 的 maxsize 无上限并实现 dequeue_blocking
    // Check output
    // std::cout << "Sleep 3 sec and then check output" << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(3));  // Sleep
    std::cout << "cq.size(): " << cq.size() << std::endl;
    std::cout << "cq.dq_size(): " << cq.dq_size() << std::endl;
    std::cout << "Retrive 10 items from ConcurrentQueue" << std::endl;
    size_t sz = cq.size();
    for (size_t i = 0; i < 10; ++i) {
        auto p = cq.dequeue();
        // std::cout << "dequeue status: " << p.first << ", value: " << p.second << std::endl;
        // std::cout << "cq[i]: " << cq[i] << std::endl;
        std::cout << "cq size: " << cq.size() << std::endl;
    }
}

