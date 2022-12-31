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

// 并查集模板,刷题用
//
// 有几个 follow up 可以思考:
//   Q1 经典优化方法是什么? 路径压缩; 按秩合并
//   Q2 存入的 id 如果不是顺序, 该怎么办? 改底层容器为 hashmap 或者增加映射方法
//
class UF {
public:
    UF(size_t n) : parent(n), siz(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int leader(int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    }

    int same(int p, int q) {
        return leader(p) == leader(q);
    }

    int getSize(int x) {
        return siz[parent[x]];
    }

    bool merge(int p, int q) {
        p = leader(p);
        q = leader(q);
        if(p == q) return false;

        parent[p] = q;
        siz[q] += siz[p];
        return true;
    }

private:
    vector<int> parent;
    vector<int> siz;
};

int main() {
    size_t n = 6;
    UF uf(n);

    uf.merge(0, 2);
    uf.merge(3, 5);
    uf.merge(5, 4);
    cout << "2, 5 are in same set? " << std::to_string(uf.same(2, 5)) << endl;
    cout << "4, 3 are in same set? " << std::to_string(uf.same(4, 3)) << endl;
    cout << "size of set which has 5? " << std::to_string(uf.getSize(5)) << endl;

    return 0;
}

