#include <string>
#include <iostream>

using namespace std;

class CIterator {
public:
    
    CIterator() : it(nullptr), index(0) {}
    CIterator(const std::string *sp) : it(sp), index(0) {}
    // CIterator(const CIterator &rhs) : it(rhs.it),index(0){} 
    // char operator* () {return *(it->data() + index); }

    const string next() {
        int idx = findSplit();
        int left = -1;
        int right = -1;
        if(idx != -1) {
            bool flag = false;
            if ((*it)[idx+1] == '[') {
                while(idx < (*it).size()) {
                    idx ++;
                    if((*it)[idx] == '[' && (*it)[idx+1] != '['){
                        left = idx+1;    
                        break;
                    }
                }

                while (idx < (*it).size()) {
                    idx ++;
                    if((*it)[idx] == ',' || (*it)[idx] == ']'){
                        right = idx-1;
                        break;
                    }
                }
            } else if((*it)[idx+1] != '[') {
                left = idx+1;
                index = left;
                while (idx < (*it).size()) {
                    idx ++;
                    if((*it)[idx] == ',' || (*it)[idx] == ']'){
                        right = idx-1;
                        break;
                    }
                }
            }
            
            // cout<<right<<" "<<left<<endl;
            if(left != -1 && right != -1) {
                // cout<<(*it)[right]<<endl
                index = left;
                return (*it).substr(left, right - left + 1);
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    bool hasNext() {
        if(findSplit() != -1){
            return true;
        }

        return false;
    }

private:
    int findSplit() {
        for(int i = index; i < (*it).size(); ++i) {
            if((*it)[i] == ',') {
                return i;
            }
        }

        return -1;
    }

private:
    const std::string* it;
    int index;
};

int main() {

    string a("[a,[[[b]],c],[[c]]]");
    // string a("[a,b,c],[[c]]]");
    // string a("[a]");
    CIterator it(&a);
    cout << it.hasNext() << endl;
    cout << it.next() << endl;
    cout << it.hasNext() << endl;
    cout << it.next() << endl;
    // cout << it.hasNext() << endl;
    // cout << it.next() << endl;

    return 0;
}

