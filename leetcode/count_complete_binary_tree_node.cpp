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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

count(TreeNode* t) {
    // 计算完全二叉树节点数的方法非常巧妙，因为是计算普通二叉树与慢二叉树的节点数的组合，能利用满二叉树直接算出某些子树的节点个数,
    // 平均时间复杂度能从 O(N * log(N)) 降低到 O(log(N) * log(N))
    TreeNode* l = root;
    TreeNode* r = root;

    int lh = 0, rh = 0;  // 左右子树的高度
    while (l) {
        ++lh;
        l = l->left;
    }
    while (r) {
        ++rh;
        r = r->right;
    }

    // 如果左右子树的高度相同, 则当前子树是一颗满二叉树, 直接套公式
    if (lh == rh) {
        return std::pow(2, lh) - 1;
    }

    return 1 + count(t->left) + count(t->right);
}

