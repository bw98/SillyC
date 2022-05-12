
# Description
-------

Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.


Example 1:
```
Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
```

Note:
- 1 <= A.length <= 30000
- -10000 <= A[i] <= 10000
- 2 <= K <= 10000



<br></br>
# 思路
--------

## 解法一

暴力解法，不多说明了。

时间复杂度：O(n^3)
空间复杂度：O(1)


<br></br>
## 解法二

前缀和取模，然后进行排列组合，坑点是负数取模的处理，以及取模后为 0 时的处理。

时间复杂度：O(n)
空间复杂度：O(n)

耗时 96 ms, faster than 54 %, Memory 30.3 MB

```cpp
class Solution {
public:
    int subarraysDivByK(const vector<int> &A, int K) {
        // idea from: https://www.youtube.com/watch?v=pkx6SowjL7M

        int k_cnt = 0;
        vector<int> mod_array(K);

        // A =       [8, 9, 7, 8, 9], K = 8
        // i                      4
        // sum     41
        // mod_arr  3 2 0 0 0 0 0 0
        // k_cnt 4                   7

        for (int i = 0, sum = 0; i < A.size(); ++i) {
            sum += A[i];
            if (sum < 0) {  // deal with negative mod, like "-3 % 5 = -3"
                mod_array[(sum % K + K) % K] += 1;
            } else {
                mod_array[sum % K] += 1;
            }
        }

        mod_array[0] += 1;  // handle the case where the mod prefix sum is 0
        for (int i = 0; i < mod_array.size(); ++i) {
            if (mod_array[i] > 1) {
                k_cnt += mod_array[i] * (mod_array[i] - 1) / 2;
            }
        }

        return k_cnt;
    }
};
```



<br></br>
# 参考
--------
- [米开：LeetCode 974. Subarray Sums Divisible by K](https://www.youtube.com/watch?v=pkx6SowjL7M)


<br></br>
