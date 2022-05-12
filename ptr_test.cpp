#include <iostream>
#include <memory>

// std::shared_ptr<int> sp;
std::shared_ptr<int> sp = std::make_shared<int>(666);
std::weak_ptr<int> wp(sp);
std::weak_ptr<int> wp222;

std::shared_ptr<int> get() {
    std::shared_ptr<int> t = wp.lock();
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

    wp222 = sp;
    if (wp222.lock()) {
        std::cout << "Not nullptr" << std::endl;
    } else {
        std::cout << "Nullptr" << std::endl;
    }

    return 0;
}

