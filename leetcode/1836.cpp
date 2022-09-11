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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        std::unordered_map<int, int> cnt;
        ListNode* cur = head;
        while (cur) {
            cnt[cur->val] += 1;
            cur = cur->next;
        }

        std::for_each(cnt.begin(), cnt.end(), [](const auto& t) { std::cout << t.first << ", "<< t.second << std::endl; } );

        cur = head;
        ListNode* dummy = new ListNode();
        ListNode* dummy_bk = dummy;
        while (cur) {
            auto iter = cnt.find(cur->val);
            if (iter != cnt.end()) {
                if (iter->second >= 2) {
                    dummy->next = cur->next;
                    delete(cur);
                    cur = dummy;
                }
            } else {
                throw -1;
            }

            dummy = cur;
            cur = cur->next;
        }

        ListNode* ans = dummy_bk->next;
        delete(dummy_bk);
        return ans;
    }
};

int main() {
    // 题目来源: https://github.com/doocs/leetcode/blob/main/solution/1800-1899/1836.Remove%20Duplicates%20From%20an%20Unsorted%20Linked%20List/README_EN.md
    ListNode* p1 = new ListNode(3);
    ListNode* p2 = new ListNode(2);
    ListNode* p3 = new ListNode(2);
    ListNode* p4 = new ListNode(1);
    ListNode* p5 = new ListNode(3);
    ListNode* p6 = new ListNode(2);
    ListNode* p7 = new ListNode(4);
    p1->next = p2;
    p2->next = p3;
    p3->next = p4;
    p4->next = p5;
    p5->next = p6;
    p6->next = p7;

    ListNode* t = p1;
    std::cout << "[";
    while (t) {
        std::cout << t->val << ",";
        t = t->next;
    }
    std::cout << "]" << std::endl;
    
    Solution s;
    t = s.deleteDuplicatesUnsorted(p1);

    std::cout << "[";
    while (t) {
        std::cout << t->val << ",";
        t = t->next;
    }
    std::cout << "]" << std::endl;

    // delete p1;
    // delete p2;
    // delete p3;
    // delete p4;

    return 0;
}

