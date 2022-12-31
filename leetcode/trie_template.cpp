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
using std::iota;
using std::to_string;
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

struct Node {
    Node() : isWord(false) {
        for (int i = 0; i < 26; ++i) son[i] = nullptr;
    }

    Node* son[26];
    bool isWord;
};

class Trie {
public:
    Trie() {
        root = new Node();
    }

    void insert(const string& word) {
        Node* node = root;
        for (char c : word) {
            if (node->son[c - 'a'] == nullptr) {
                node->son[c - 'a'] = new Node();
            }

            node = node->son[c - 'a'];
        }

        node->isWord = true;
    }

    bool search(const string& word) {
        Node* node = root;
        for (char c : word) {
            if (node->son[c - 'a'] == nullptr) {
                return false;
            }

            node = node->son[c - 'a'];
        }

        return node->isWord;
    }

    bool startsWith(const string& prefix) {
        Node* node = root;
        for (char c : prefix) {
            if (node->son[c - 'a'] == nullptr) return false;
            node = node->son[c - 'a'];
        }

        return true;
    }

private:
    Node* root;
};

int main() {
    Trie trie;

    trie.insert("apple");
    cout << trie.search("apple") << endl;
    cout << trie.search("app") << endl;
    cout << trie.startsWith("app") << endl;
    trie.insert("app");
    cout << trie.search("apple") << endl;

    return 0;
}

