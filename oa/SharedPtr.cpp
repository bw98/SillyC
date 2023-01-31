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

template<typename T>
class SharedPtr {
public:
    SharedPtr(T* ptr=nullptr) : ptr_(ptr), refCnt_(new int(1)), mtx_(new std::mutex) {
    }

    SharedPtr(const SharedPtr<T>& sptr) : ptr_(sptr.ptr_), refCnt_(sptr.refCnt_), mtx_(sptr.mtx_) {
        IncRefCount();
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& sptr) {
        // 注意防止自赋值
        if (ptr_ != sptr.ptr_) {
            // 减少引用次数，如果引用为 0, 彻底释放旧资源
            Release();

            // 共同管理新资源
            ptr_ = sptr.ptr_;
            refCnt_ = sptr.refCnt_;
            mtx_ = sptr.mtx_;
            IncRefCount();
        }
        
        return *this;
    }

    ~SharedPtr() {
        // std::cout << "Call SharedPtr deconstructor" << std::endl;
        // 引用为 0 的话, 彻底释放资源
        Release();
    }

    SharedPtr<T>& operator*() {
        return *this;
    }
    
    SharedPtr<T>& operator->() {
        return *this;
    }

    int RefCount() {
        int refCnt;
        mtx_->lock();
        refCnt = *refCnt_;
        mtx_->unlock();

        return refCnt;
    }

private:
    void IncRefCount() {
        mtx_->lock();
        ++(*refCnt_);
        mtx_->unlock();
    }

    void Release() {
        bool delete_flag = false;
        mtx_->lock();
        --(*refCnt_);
        if (*refCnt_ == 0) {
            delete ptr_;
            delete refCnt_;
            delete_flag = true;
        }
        mtx_->unlock();
        if (delete_flag) {
            delete mtx_;
            // std::cout << "Delete resources, including reference Count, mutex, object which pointers point to" << std::endl;
        }
    }

private:
    T* ptr_;
    int* refCnt_;
    std::mutex* mtx_;
};

class MyTest {
public:
    MyTest()=default;
    MyTest(int value, const std::string& str) : val_(value), str_(str) {
    }
    ~MyTest()=default;
    MyTest(const MyTest&)=default;
    MyTest(MyTest&&)=default;

private:
    int val_;
    std::string str_;
};

int main() {
    {
        SharedPtr<MyTest> sp1(new MyTest(666, "666"));  // 当然也可以实现一个 make_shared, 基于不定参模板和转发, 只是 oa 时间不够用了
        cout << "[Just Created] Reference Count: " << sp1.RefCount() << endl;
        {
            SharedPtr<MyTest> sp2 = sp1;
            cout << "[Used copy operator] Reference Count: " << sp1.RefCount() << endl;
            SharedPtr<MyTest> sp3(sp1);
            cout << "[Used copy constructor] Reference Count: " << sp3.RefCount() << endl;
        }
        cout << "[After sp2 and sp3 dead] Reference Count: " << sp1.RefCount() << endl;
    }

    return 0;
}

