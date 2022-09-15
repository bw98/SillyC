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

class Solution {
public:
    //
    // 参考 labuladong 刷题笔记
    // 对于任意一个节点，它怎么才能知道自己是不是 p 和 q 的最近公共祖先?
    // 如果一个节点能够在它的左右子树中分别找到 p 和 q，则该节点为 LCA 节点
    //
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        find_left_ = false;
        find_right_ = false;
        TreeNode* res = find(root, p->val, q->val);
        if (!find_left_ || !find_right_) {
            return nullptr;
        }
        
        return res;
    }
    
private:
    // 查找 val1 和 val2 的最近公共祖先
    // 递归思路是找 val1 和 val2 等于当前的节点, 如果不等于的话，就进一步去查找子树
    // （疑问）如果是纯前序遍历不带全局变量的话，能实现吗？（应该不能
    TreeNode* find(TreeNode* root, int val1, int val2) {
        if (!root) return nullptr;
        
        TreeNode* left = find(root->left, val1, val2);
        TreeNode* right = find(root->right, val1, val2);
        
        if (left && right) {
            return root;
        }
        if (root->val == val1 || root->val == val2) {
            if (root->val == val1) find_left_ = true;
            if (root->val == val2) find_right_ = true;
            return root;
        }
        
        return left ? left : right;
    }
};

