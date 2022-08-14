#include <iostream>
#include <memory>

// std::shared_ptr<int> SP;
std::shared_ptr<int> SPTR = std::make_shared<int>(666);
std::weak_ptr<int> WPTR(SPTR);
std::weak_ptr<int> WPTR2;

std::shared_ptr<int> get() {
    std::shared_ptr<int> t = WPTR.lock();
    return t;
}

int main () {

    std::shared_ptr<int> a = std::move(get());
    std::cout << a.use_count() << std::endl;
    // std::shared_ptr<int> a = get();
    // std::cout << a.use_count() << std::endl;
    if (a) {
        std::cout << "Not nullptr" << std::endl;
    } else {
        std::cout << "Nullptr" << std::endl;
    }

    WPTR2 = SPTR;
    if (WPTR2.lock()) {
        std::cout << "Not nullptr" << std::endl;
        std::cout << WPTR2.use_count() << std::endl;
    } else {
        std::cout << "Nullptr" << std::endl;
    }

    return 0;
}

