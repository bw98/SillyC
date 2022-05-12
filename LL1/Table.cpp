#include"Table.h"

Table::Table() {
    memset(tableMap, -1, sizeof(tableMap));
}

void Table::getTable() {
    for (int index = 0; index < prods.size(); index++) {                          // 对于每个产生式(编号index):A->α
        int row = getNoterIndex(prods[index].left);
        int emptyCount = 0;
        for (int i = 0; i < prods[index].right.size(); i++) { // 1) 对FIRST(α)中的每个终结符号a,将index加入(A, a)中
            char tmp = prods[index].right[i];
            if (!isNoter(tmp)) { // tmp是终结符
                if (tmp != '$')
                    tableMap[row][getTerIndex(tmp)] = index;
                if (tmp == '$') {
                    emptyCount++;
                }
                break;
            }
            else {  // tmp是非终结符
                set<char>::iterator it;
                int tmpIndex = getNoterIndex(tmp);
                // 对FIRST(tmp)中的每个终结符号a,将i加入(A, a)中
                for (it = firstSet[tmpIndex].begin(); it != firstSet[tmpIndex].end(); it++) {
                    tableMap[row][getTerIndex(*it)] = index;
                }
                if (firstSet[tmpIndex].count('$') != 0) {      //如果空$在FIRST(tmp)中,继续看α中的下一个符号
                    emptyCount++;
                }
                else {
                    break;
                }
            }
        }

        //如果空$在FIRST(α)中,对FOLLOW(A)中的每个终结符或结束符b,将i加入(A,b)中
        if (emptyCount == prods[index].right.size()) {
            set<char>::iterator  it;
            for (it = followSet[row].begin(); it != followSet[row].end(); it++) {
                tableMap[row][getTerIndex(*it)] = index;
            }
        }
    }
}

void Table::analyExpression(string s) {
    for (int i = 0; i < s.size(); i++)
        leftExpr.push_back(s[i]);
    leftExpr.push_back('#');

    analyStack.push_back('#');
    analyStack.push_back(nonterminal[0]);  // 加入开始符号

    while (analyStack.size() > 0) {
        //cout<<"分析栈：";
        string outs = "";
        for (int i = 0; i < analyStack.size(); i++)
            outs += analyStack[i];
        cout << setw(15) << outs;

        //cout<<"剩余输入串：";
        outs = "";
        for (int i = 0; i < leftExpr.size(); i++)
            outs += leftExpr[i];
        cout << setw(15) << outs;

        // 匹配
        char char1 = analyStack.back();
        char char2 = leftExpr.front();
        if (char1 == char2 && char1 == '#') {
            cout << setw(15) << "Accepted!" << endl;
            return;
        }
        if (char1 == char2) {
            analyStack.pop_back();
            leftExpr.erase(leftExpr.begin());
            cout << setw(15) << "匹配：" << char1 << endl;
        }
        else if (tableMap[getNIndex(char1)][getIndex(char2)] != -1) {  // 预测表中有推倒项，可进行推导
            int tg = tableMap[getNIndex(char1)][getIndex(char2)];
            analyStack.pop_back();

            if (production[tg].right != "$") {
                for (int i = production[tg].right.length() - 1; i >= 0; i--) // 注意这里是反向的
                    analyStack.push_back(production[tg].right[i]);
            }

            cout << setw(15) << "推导：" << production[tg].left << "->" << production[tg].right << endl;
        }
        else {  // 错误
            cout << setw(15) << "error!" << endl;
            return;
        }
    }
}

void prods::printPredictTable() {
    // 表头

    for (int i = 0; i < terminalNoEmpty.size(); i++) {
        cout << setw(10) << terminalNoEmpty[i];
    }
    cout << endl;
    for (int i = 0; i < nonterminal.size(); i++) {
        cout << nonterminal[i] << ": ";
        for (int j = 0; j < terminalNoEmpty.size(); j++) {
            if (tableMap[i][j] == -1)
                cout << setw(10) << "   ";
            else
                cout << setw(10) << production[tableMap[i][j]].right;
        }
        cout << endl;
    }
    cout << endl;
}

void Table::getResult() {
    inputAndSolve();
    displayFirstAndFollow();
    getTable();
    printPredictTable();
    //栈匹配
    string ss;
    cout << "请输入符号串：" << endl;
    cin >> ss;
    cout << setw(15) << "分析栈" << setw(15) << "剩余输入串" << setw(15) << "推导式" << endl;
    analyExpression(ss);

}

