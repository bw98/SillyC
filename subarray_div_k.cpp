#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include<list>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<memory>
#include<random>

using namespace std;


class Solution {
public:
    int subarraysDivByK(const vector<int>& A, int K) {
        unordered_map<int, int> m;
        int preSum = 0;
        int res = 0;
        m[0] = 1;
        for (int a : A) {
            preSum = (preSum + a) % K;
            if (preSum < 0) preSum += K;
            res += m[preSum]++;
        }
        return res;
    }
};


int main () {
    //vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8};
    //auto low_it = std::lower_bound(vec.cbegin(), vec.cend(), 6);
    //cout << *low_it << "  ";
    //cout << (low_it - vec.begin()) << endl;
    
    //int i = 2147483647, j = -2147483647;  // -1e9 ~ 1e9 可能导致大数问题
    //printf("%d %d %d %lld\n", i, j, j - 2147483647, (long long) j - 2147483647);
    //printf("%d %d %lld %lld\n", i, i + i, (long long)0 + i + i + i, (long long)0 + 3*i);
    
    //int i = 5, j = 6;
    //int* p1 = &i, p2 = &j;
    //printf("%d, %d\n", *p1, *p2);
    

    //int a = 10000000, b = -10000000;
    //printf("%d  %d  %d\n", a + a, a - b, b - a);
    long long right = (long long)2147483647 + 1;
    printf("%lld\n", right);

    return 0;
}
