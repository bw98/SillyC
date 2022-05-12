#include"Base.h"

void Base::inputAndSolve() {  // 处理和求出First和Follow集
    string s;
    cout << "输入的产生式的个数：" << endl;
    cin >> T;
    cout << "输入的产生式：" << endl;
    for (int index = 0; index < T; index++) {  // 处理每一个产生式
        cin >> s;
        string temp = "";  // 存储去掉空格的产生式
        for (int i = 0; i < s.length(); i++) {  // 去掉产生式中的' '
            if (s[i] != ' ')
                temp += s[i];
        }
        production[index].left = temp[0];  // 产生式的左部
        for (int i = 3; i<temp.length(); i++) // 产生式的右部
            production[index].right += temp[i];

        for (int i = 0; i < temp.length(); i++) {  // 存储所有终结符和非终结符
            if (i == 1 || i == 2) continue;  // 跳过产生符号->
            if (isNonterminal(temp[i])) {  //插入一个非终结符
                int flag = 0;
                for (int j = 0; j < nonterminal.size(); j++) {
                    if (nonterminal[j] == temp[i]) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) nonterminal.push_back(temp[i]);
            }
            else {                       //插入一个终结符
                int flag = 0;
                for (int j = 0; j < terminal.size(); j++) {
                    if (terminal[j] == temp[i]) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) terminal.push_back(temp[i]);
            }
        }
    }
    terminal.push_back('#');

    for (int i = 0; i < terminal.size(); i++) { // 存储没有$符号的终结符
        if (terminal[i] != '$')
            terminalNoEmpty.push_back(terminal[i]);
    }
    // 获得first集
    for (int i = 0; i < nonterminal.size(); i++) {
        getFirst(nonterminal[i]);
    }

    // 获得follow集
    for (int i = 0; i < nonterminal.size(); i++) {
        if (i == 0)  // 开始符号, 先加入结束符号
            followSet[0].insert('#');
        getFollow(nonterminal[i]);
    }
}

void Base::displayFirstAndFollow() {  // 输出First和Follow集
    cout << "FIRST集合" << endl;
    for (int i = 0; i<nonterminal.size(); i++) {
        cout << nonterminal[i] << ": ";
        set<char>::iterator it;
        for (it = firstSet[i].begin(); it != firstSet[i].end(); it++)
            cout << *it << "  ";
        cout << endl;
    }
    cout << endl;

    cout << "FOLLOW集合" << endl;
    for (int i = 0; i<nonterminal.size(); i++) {
        cout << nonterminal[i] << ": ";
        set<char>::iterator it;
        for (it = followSet[i].begin(); it != followSet[i].end(); it++)
            cout << *it << "  ";
        cout << endl;
    }
    cout << endl;
}

bool Base::isNoter(char target) {
    //为了简单，规定非终结符是A到Z
    if (target >= 'A'&& target <= 'Z') { 
        return true;
    }
    return false;
}

Production* Base::getProds() {
    if (prods != null) { 
        return prods;
    }
    return NULL;
}

int Base::getTerIndex(char target) {
    int i = 0;
    for (auto it = ter.begin(); it != ter.end(); ++it) {
        if (target != *it) {
            i++;
            continue;
        }
        else return i;
    }
    return -1; //表示未找到
}

int Base::getNoterIndex(char target) {
    int i = 0;
    for (auto it = noter.begin(); it != noter.end(); ++it) {
        if (target != *it) {
            i++;
            continue;
        }
        else return i;
    }
    return -1;
}

set<char> Base::getFirstSet(char target) {
    if (!isNoter(target)) {
        char arr[1] = {target};
        set<char> mySet(arr, arr+1);
        return mySet;
    }
    else{
        int tarIdx = getNoterIndex(target);
        return this->firstSet[tarIdx];
    }
}


void Base::setFirstSet(char target) {
    int countEmpty = 0;  // 用于最后判断是否有空
    int isEmpty = 0;
    int targetIndex = getNoterIndex(target);
    for (int i = 0; i < prods.size(); i++) {
        if (prods[i].left == target) {  // 匹配产生式左部
            if (!isNoter(prods[i].right[0])) {  // 对于终结符，直接加入first
                firstSet[targetIndex].insert(prods[i].right[0]);
            }
            else {
                for (int j = 0; j < prods[i].right.length(); j++) { // X->Y1..Yj..Yk是一个产生式
                    char cc = prods[i].right[j];
                    if (!isNoter(Yj)) {  // cc是终结符(不能产生空),FIRST(cc)=cc加入FIRST(X),不能继续迭代,结束
                        firstSet[targetIndex].insert(cc);
                        break;
                    }
                    getFirst(cc);// cc是非终结符，递归 先求出FIRST(cc)

                    set<char>::iterator it;
                    int ccIndex = getNIndex(cc);
                    for (it = firstSet[ccIndex].begin(); it != firstSet[ccIndex].end(); it++) {
                        if (*it == '$')  // 遍历查看FIRST(Yj)中是否含有'$'(能产生空)
                            isEmpty = 1;
                        else
                            firstSet[targetIndex].insert(*it);//将FIRST(Yj)中的非$就加入FIRST(X)
                    }
                    if (isEmpty == 0)  // Yj不能产生空, 迭代结束
                        break;
                    else {   //  Yj能产生空
                        countEmpty += isEmpty;
                        isEmpty = 0;
                    }
                }
                if (countEmpty == prods[i].right.length())//所有右部first(Y)都有$(空),将$加入FIRST(X)中
                    firstSet[getTerIndex(target)].insert('$');
            }
        }
    }
}

set<char> Base::getFollowSet(char target) {
    if (!isNoter(target)) {
        return null;
    }
    else {
        int tarIdx = getNoterIndex(target);
        retur this->followSet[tarIdx];
    }
}

void Base::setFollowSet(char target) {
    
}

void Base::display() {
    cout << "First 集合如下:" << endl;
    for (int i = 0; i < noter.size(); i++) {
        cout << noter[i] << ": ";
        set<char>::iterator it;
        int j = getNoterIndex(noter[i]);
        for (it = firstSet[j].begin(); it != firstSet[j].end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
    //不求终结符的First集合了，因为没有意义
        
    cout << "Follow 集合如下:" << endl;
    for (int i = 0; i < noter.size(); i++) {
        cout << noter[i] << ": ";
        set<char>::iterator it;
        int j = getNoterIndex(noter[i]);
        for (it = firstSet[j].begin(); it != firstSet[j].end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
}



