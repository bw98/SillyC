#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

class T {
 public:
    T(int x, string t) : num_(x), s_(t) {
        cout << "1" << endl;
    }
    T(const T& o) : num_(o.num_), s_(o.s_) {
        cout << "2" << endl;
    }
    T(T&& o) noexcept : num_(o.num_), s_(std::move(o.s_)) {
        cout << "3" << endl;
    }
    T& operator=(const T& o) {
        num_ = o.num_;
        s_ = o.s_;
        cout << "4" << endl;
        return *this;
    }
    T& operator=(T&& o) {
        num_ = o.num_;
        s_ = std::move(o.s_);
        cout << "5" << endl;
        return *this;
    }

 private:
    int num_;
    string s_;
};

int main () {
    T t(666, string(10000, 'c'));
    vector<T> vec;
    vec.push_back(std::move(t));
    // vec.insert(vec.end(), T(666));
    // vec.emplace(vec.end(), 666);

    return 0;
}

