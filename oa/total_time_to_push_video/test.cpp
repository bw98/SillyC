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

int getMaxTime() {
    int node_num;
    cin >> node_num;
    int src;
    cin >> src;
    int edge_num;
    cin >> edge_num;
    unordered_map<int, unordered_map<int, int>> data;
    unordered_map<int, bool> visited;
    int tmp1, tmp2, tmp3;
    while (cin >> tmp1 >> tmp2 >> tmp3) {
        cout << tmp1 << ", " << tmp2 << ", " << tmp3 << endl;
        data[tmp1].emplace(tmp2, tmp3);
        visited[tmp1] = false;
        visited[tmp2] = false;
    }

    unordered_map<int, int> target_min_time; // Min time cost from source to target
    target_min_time.emplace(src, 0);
    int total_max_time = INT_MIN;
    queue<int> q;
    q.push(src);
    while (q.size()) {
        int cur = q.front(); q.pop();
        visited[cur] = true;
        for (auto target_and_weight : data[cur]) {
            int target = target_and_weight.first;
            int weight = target_and_weight.second;
            visited[target] = true;
            if (target_min_time.find(target) == target_min_time.end()) {
                target_min_time[target] = target_min_time[cur] + weight;
            } else {
                target_min_time[target] = min(target_min_time[target], target_min_time[cur] + weight);
            }
            
            if (data.find(target) == data.end()) {
                total_max_time = max(total_max_time, target_min_time[target]);
            }
            
            q.push(target);
        }
    }
    for (auto kv : visited) {
        cout << "node: " << kv.first << ", visited: " << kv.second << endl;
        if (kv.second == false) return -1;
    }
    return  total_max_time;
}


int main() {
    cout << getMaxTime() << endl;
    return 0;
}

