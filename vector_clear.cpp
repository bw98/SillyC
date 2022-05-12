#include<iostream>
#include<vector>

using namespace std;

int main() {
    vector<int> v {1,2,3,4,5};

    cout << "size:" << v.size() << endl;
    cout << "capacity:" << v.capacity() << endl;

    v.clear();
    cout << "after clear, size:" << v.size() << endl;
    cout << "after clear, capacity:" << v.capacity() << endl;

    cout << "v[0] = " << *v.data() << endl;
    cout << "v[2] = " << v[2] << endl;

    v.shrink_to_fit();
    cout << "after shrink_to_fit, size:" << v.size() << endl;
    cout << "after shrink_to_fit, capacity:" << v.capacity() << endl;
    cout << "v[0] = " << *v.data() << endl;
    cout << "v[2] = " << v[2] << endl;

    return 0;
}

