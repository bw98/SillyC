#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <utility>
#include <memory>
#include <random>

using namespace std;

class Solution {
public:
    //
    // valid tree: 
    // 1. no circle; -> solved by union find
    // 2. The number of nodes is equal to the number of edges plus 1 -> which means only one tree
    // 3. One parent node only has 3 son nodes;  -> binary tree
    //
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if (!edges.size()) return false;
        if (n != edges.size() + 1) return false;

        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i].first, b = edges[i].second;
            roots_[a] = a;
            roots_[b] = b;
        }

        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i].first, b = edges[i].second;
            edge_cnt_[a] += 1;
            edge_cnt_[b] += 1;
            if (edge_cnt_[a] > 3) return false;
            if (edge_cnt_[b] > 3) return false;
            int roota = findRoot(a);
            int rootb = findRoot(b);
            if (roota == rootb) return false;
            roots_[a] = rootb;
        }

        return true;
    }

private:
    int findRoot(int id) {
        while (id != roots_[id]) id = roots_[id];
        return id;
    }

private:
    unordered_map<int, int> roots_;
    unordered_map<int, int> edge_cnt_;
};

int main() {
    // Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
    // Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
    // Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
    int n = 5;  // total nunmber of nodes
    vector<pair<int, int>> edges;  // edge from node to another node
    edges.emplace_back(0, 1);
    edges.emplace_back(0, 2);
    edges.emplace_back(0, 3);
    edges.emplace_back(1, 4);

    Solution solution;
    cout << solution.validTree(n, edges) << endl;

    return 0;
}

