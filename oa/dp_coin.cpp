#include <iostream>
#include <vector>

// using namespace std;

// 有 n 种硬币，每种硬币的面值不同，每种硬币有无限个,
// 问如果需要的金钱数为 k, 最少需要几个硬币能正好 cover，不能的话就 return - 1
// Follow up: 如果 每种硬币只能拿特定的个数呢?
// Follow up: 如果问的是有多少种组合凑成这个金额呢?
//
//
// 如果是无限拿任意种类的硬币, 就用DP: 参考背包九讲 - 完全背包
//
// 贪心: 贪心是有条件的, 这里的贪心条件是大额硬币必须是所有面值小于它的硬币的面值倍数
// 原因: http://blog.csdn.net/hwdopra/article/details/6318746
//
// 相关链接
// 原题解析  https://blog.csdn.net/qq_39559641/article/details/117172758
// 求能凑成该金钱数的组合个数  https://mp.weixin.qq.com/s/zGJZpsGVMlk-Vc2PEY4RPw
    
class Solution {
public:
    int getMinCoinNumByDP(const std::vector<int>& coins, const std::vector<int>& nums, int k) {
        // dp[i][j] 表示使用 i 种硬币, 达到 j 金额的最小硬币数
        // 状态转移是, 如果使用第 i 种硬币, 则最小硬币数为
        //     min(dp[i][j], dp[i-1][j - 第i种硬币个数 * 对应面值] + 第i种硬币个数)
        //其中第i种的硬币个数可以有多种情况, 从 0 到 j / coins[i-1]
        
        int n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, INT_MAX));

        for (int j = 0; j <= k ; ++j) {
            dp[0][j] = INT_MAX - k;
        }

        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        
        for (int  i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                for (int cnt = 0; cnt <= j / coins[i - 1]; ++cnt) {
                    dp[i][j] = std::min(dp[i][j], dp[i-1][j - cnt * coins[i - 1]] + cnt);
                }
            }

        }

        int res = dp[n][k];
        if (res == INT_MAX || res == INT_MAX - k) return -1;
        return res;
    }

    int getMinCoinNumByDP2(const std::vector<int>& coins, const std::vector<int>& nums, int k) {
        // 进一步优化, 优化时间
        // 其实最内层的 for loop, 即第 i 种硬币个数，这个维度可以忽略
        //
        // 此时状态转移为
        //     dp[i][j] = min(dp[i - 1][j], dp[i][j - 第i种硬币对应的面值] + 1)
        // 其中前一个式子表示不使用第 i 种硬币凑成零钱 j 的硬币数;
        // 第二个式子表示最少有一枚硬币凑成零钱 j 的硬币数
        //
        
        int n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, INT_MAX));

        for (int j = 0; j <=k ; ++j) {
            dp[0][j] = INT_MAX - k;
        }

        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        
        for (int  i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                if (j  < coins[i - 1])  {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = std::min(dp[i-1][j], dp[i][j - coins[i - 1]] + 1);
                }
            }
        }

        int res = dp[n][k];
        if (res == INT_MAX || res == INT_MAX - k) return -1;
        return res;
    }
    
    int getMinCoinNumByDP3(const std::vector<int>& coins, const std::vector<int>& nums, int k) {
        // 再进一步优化
        // 压缩空间到一维(滚动数组)
        // dp[i][j] 只和 dp[i-1] 和 dp[i] 有关, 可以从右边往左打表, 节约第一维
        //
        
        int n = coins.size();
        std::vector<int> dp(k + 1, INT_MAX - k);
        dp[0] = 0;
        
        for (int  i = 1; i <= n; ++i) {
            for (int j = coins[i-1]; j <= k; ++j) {
                dp[j] = std::min(dp[j], dp[j - coins[i - 1]] + 1);
            }
        }

        int res = dp[k];
        if (res == INT_MAX || res == INT_MAX - k) return -1;
        return res;
    }

    // int getMinCoinNumByGreedy(const vector<int>& coins, const vector<int>& cnts, int k) {
    //     return -1;
    // }
};

int main() {
    std::vector<int> coins = { 1, 2, 5, 6, 11 };
    std::vector<int> cnts = { INT_MAX, INT_MAX, INT_MAX };
    int k = 22;

    Solution solution;
    // int res = solution.getMinCoinNumByDP(coins, cnts, k);
    // int res = solution.getMinCoinNumByDP2(coins, cnts, k);
    int res = solution.getMinCoinNumByDP3(coins, cnts, k);
    // int res = getMinCoinNumByGreedy(coins, cnts, k);
    std::cout << res << std::endl;

    return 0;
}

