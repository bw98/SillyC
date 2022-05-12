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

class CInterator {
 public:
     CInterator(const string& data) : ss(data) {
         // data:  [1, [2, 3], [[4, 5, 6]], 7]
         hasNext();
         next();
     }

     string getVal() const {
         return next_val;
     }

     const string next() {
         bool has_next = hasNext();
         if (has_next) {
             return next_val;
         } else {
             return "";
         }
     }

     bool hasNext() {
         string t;
         if (getline(ss, t, ',')) {
             string num("0123456789");
             auto pos = t.find_first_of(num);
             if (pos != t.npos) {
                int start = pos;
                while (start + 1 < t.size() && t[start + 1] >= '0' && t[start + 1] <= '9') ++start;
                // cout << endl;
                // cout << t << endl;
                // cout << pos << "    "  << start << endl;
                // cout << endl;
                next_val = t.substr(pos, start - pos + 1);
                return true;
             } else {
                 return false;
             }
         } else {
             return false;
         }
     }

public:
     string next_val;

 private:
     stringstream ss;
     // string cur_val;
};

int main() {
    string obj_str("[1,[2],[[3]]]");
    cout << obj_str << endl;
    CInterator it(obj_str);
    cout << it.getVal() << endl;
    cout << it.hasNext() << endl;
    cout << it.next() << endl;
    cout << it.getVal() << endl;
    cout << it.hasNext() << endl;
    cout << it.next() << endl;
    cout << it.getVal() << endl;
    cout << it.hasNext() << endl;
    cout << it.next() << endl;

    return 0;
}


