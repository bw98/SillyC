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


// 1444 题 切披萨

class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        kmod = 1e9 + 7;
        m = pizza.size();  // 行
        n = pizza[0].size();  // 列

        // 求二维矩阵前缀和, 从而找到某个矩阵, 矩阵左上和右下的坐标为 (0, 0) 与 (y, x),
        // 快速该矩阵内有没有值, 和 leetcode 304 题一样的
        sum = vector<vector<int>> (m + 1, vector<int>(n + 1));
        for (int y = 0; y < m; ++y) {
            for (int x = 0; x < n; ++x) {
                sum[y + 1][x + 1] = sum[y + 1][x] + sum[y][x + 1] + (pizza[y][x] == 'A') - sum[y][x];
            }
        }

        cache = vector<vector<vector<int>>> (m, vector<vector<int>> (n, vector<int>(k, -1)));

        // dp(m, n, k) 是一共有多少种办法，用 k 次机会去切 pizza[i:m][j:n]
        return dp(0, 0, k - 1);  // 题目中给的 k 是披萨的块数, 这里需要转换到切割次数, 即为 k-1
    }

private:
    // 检查以 (x1, y1) 到 (x2, y2) 为对角线的矩形有没有苹果
    // 范围是 (0, 0) 到 (m-1, n-1) 整个大矩形
    bool hasApple(int x1, int y1, int x2, int y2) {
        return (sum[y2 + 1][x2 + 1] - sum[y2 + 1][x1] - sum[y1][x2 + 1] + sum[y1][x1]) > 0;
    }

    // (mm, nn) 是切割点的坐标, kk 是当前还能切多少次
    int dp(int mm, int nn, int kk) {
        if (!kk) return hasApple(nn, mm, n-1, m-1);  // base case 当不能再切时，检查右下角区间还有没有苹果, 如果有的话就是1种，没有就是0

        int& ans = cache[mm][nn][kk];
        if (ans != -1) return ans;  // 非 -1 说明已求解过
        
        ans = 0;

        // 横着切
        for (int y = mm; y < m - 1; ++y) {
            ans = (ans + hasApple(nn, mm, n - 1, y) * dp(y + 1, nn, kk - 1)) % kmod;  // 切完如果上面部分有苹果, 则试着去切下面部分
        }

        // 竖着切
        for (int x = nn; x < n - 1; ++x) {
            ans = (ans + hasApple(nn, mm, x, m - 1) * dp(mm, x + 1, kk - 1)) % kmod;  // 切完如果左边部分有苹果，则试着去切右边部分
        }

        return ans;
    }

    int kmod;
    int m;  // 行
    int n;  // 列
    vector<vector<int>> sum;
    vector<vector<vector<int>>> cache;
};

int main() {
    vector<string> pizza = {
        "A..",
        "AAA",
        "..."
    };
    int k = 3;

    Solution solu;
    int res = solu.ways(pizza, k);
    std::cout << res << std::endl;

    return 0;
}

