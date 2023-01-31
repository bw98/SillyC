// Milvus 源码 ThreadSafeVector
// https://github.com/milvus-io/milvus/blob/21a1311f664e83da2e8b18bc088786cb5131f6c0/internal/core/src/segcore/ConcurrentVector.h

template <typename Type>
class ThreadSafeVector {
 public:
    template <typename... Args>
    void
    emplace_to_at_least(int64_t size, Args... args) {
        if (size <= size_) {
            return;
        }
        std::lock_guard lck(mutex_);
        while (vec_.size() < size) {
            vec_.emplace_back(std::forward<Args...>(args...));
            ++size_;
        }
    }
    const Type&
    operator[](int64_t index) const {
        Assert(index < size_);
        std::shared_lock lck(mutex_);
        return vec_[index];
    }

    Type&
    operator[](int64_t index) {
        Assert(index < size_);
        std::shared_lock lck(mutex_);
        return vec_[index];
    }

    int64_t
    size() const {
        return size_;
    }

    void
    clear() {
        std::lock_guard lck(mutex_);
        size_ = 0;
        vec_.clear();
    }

 private:
    std::atomic<int64_t> size_ = 0;
    std::deque<Type> vec_;
    mutable std::shared_mutex mutex_;
};

