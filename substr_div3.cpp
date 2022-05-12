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
#include <memory>
#include <random>

using namespace std;

int div3Num(string s) {
    // 给定一个str，例如‘456’，找出有多少个 substring 可以 divisible by 3
    // str[0:2], str[0:3], str[2] 都可以被3整除，所以return 3
    // 如果是以 0 开头的 substring 是不合法的，比如‘03’的话是不可以的
    
    if (s.empty() || s[0] == '0') return 0;

    int res = 0;
    vector<int> pre(1 + s.size(), 0);

    //
    //  s        4  5  6
    // pre    0  4  9  15
    //

    for (int i = 0; i < s.size(); ++i) {
        pre[i + 1] = s[i] - '0' + pre[i];
    }

    for (int i = 0; i < s.size(); ++i) {
        for (int j = i; j < s.size(); ++j) {
            if (s[i] == '0') continue;

            if (i == j) {
                res += (pre[i + 1] - pre[i]) % 3 == 0 ? 1 : 0;
            } else {
                res += (pre[j + 1] - pre[i]) % 3 == 0 ? 1 : 0;
            }
        }
    }

    return res;
}

int main() {
    string s("456");
    cout << div3Num(s) << endl;

    return 0;
}

