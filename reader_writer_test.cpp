#include <iostream>
#include <mutex>    //unique_lock
#include <shared_mutex> //shared_mutex shared_lock
#include <thread>

using namespace std;

// 基于 mutex 自己实现的读写锁
class shared_mutex {
public:
    shared_mutex() : m_shared_count(0) {
    }

    void lock() {
        m_mutex_write.lock();
    }

    void unlock() {
        m_mutex_write.unlock();
    }

    void lock_shared() {
        m_mutex_count.lock();
        m_shared_count++;
        if (m_shared_count == 1) {
            m_mutex_write.lock();
        }
        m_mutex_count.unlock();
    }
    void unlock_shared() {
        m_mutex_count.lock();
        m_shared_count--;
        if (m_shared_count == 0) {
            m_mutex_write.unlock();
        }
        m_mutex_count.unlock();
    }

private:
    int m_shared_count;
    std::mutex m_mutex_count;
    std::mutex m_mutex_write;
};

class ThreadSaferCounter {
 private:
    mutable std::shared_mutex mutex_;
    int64_t value_ = 0;

 public:
    ThreadSaferCounter() = default;
    ~ThreadSaferCounter() = default;
    
    int64_t get() const {
        // 读者, 获取共享锁, 使用shared_lock
        // (读者优先) 当数据被线程 A 读取时，其他线程仍可以进行读取却不能写入
        // 也就是当线程 A 获得共享锁时，其他线程仍可以获得共享锁但不能获得独占锁
        std::shared_lock<std::shared_mutex> lck(mutex_);//执行mutex_.lock_shared();
        return value_;  //lck 析构, 执行mutex_.unlock_shared();
    }

    int64_t increment() {
        // 写者, 获取独占锁, 使用unique_lock
        // (读者优先) 当 data 被线程 A 写入时，其他线程既不能读取也不能写入
        // 当线程 A 获得独占锁时，其他线程既不能获得共享锁也不能获得独占锁
        std::unique_lock<std::shared_mutex> lck(mutex_);//执行mutex_.lock();
        ++value_;   //lck 析构, 执行mutex_.unlock();
        return value_;
    }

    void reset() {
        //写者, 获取独占锁, 使用unique_lock
        std::unique_lock<std::shared_mutex> lck(mutex_);//执行mutex_.lock();
        value_ = 0;   //lck 析构, 执行mutex_.unlock();
    }
};

ThreadSaferCounter g_counter;

// 实际测试要把这两个注释掉，一次就一个 reader / writer 在跑, 该怎么拿到 reader writer 的值?
std::mutex g_mtx_r;
std::mutex g_mtx_w;


void reader(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::this_thread::yield();
        std::unique_lock<std::mutex> ulck(g_mtx_r);//cout也需要锁去保护, 否则输出乱序
        std::cout << "reader #" << id << " get value " << g_counter.get() << "\n";
    }    
}

void writer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::this_thread::yield();
        std::unique_lock<std::mutex> ulck(g_mtx_w);//cout也需要锁去保护, 否则输出乱序
        std::cout << "writer #" << id << " write value " << g_counter.increment() << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main() {
    ssize_t size = 10;
    std::thread reader_thds[size];
    std::thread writer_thds[size];
    for(int i = 0; i < size; ++i) {
        reader_thds[i] = std::thread(reader, i);
    }
    for(int i = 0; i < size; ++i) {
        writer_thds[i] = std::thread(writer, i);
    }

    for(int i = 0; i < size; ++i) {
        reader_thds[i].join();
    }
    for(int i = 0; i < size; ++i) {
        writer_thds[i].join();
    }

    return 0;
}

