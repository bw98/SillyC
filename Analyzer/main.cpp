#include<cstdio>
#include<iostream> 
#include<fstream>
#include<string.h>
#include<unistd.h>
using namespace std;

char prog[80],token[30];
char ch;
int syn, p, m = 0, n, row = 1, sum = 0;  // syn:单词种类码, token:存放单词自身字符串, sum:整形常数
char *rwtab[6] = {"begin", "if", "then", "while", "do", "end"};
 
void readByChar(string &s) {
    char c;
    fstream inFile;
    inFile.unsetf(ios_base::skipws); // 清除跳过空白字符的标志
    inFile.open("in.txt",ios::in);
    while(!inFile.eof()) {
        inFile >> c;
        s += c;
    }
    s += '`';
    inFile.close();
}

void readByLine(string &s) {
    char buffer[256];
    fstream inFile;
    inFile.open("in.txt",ios::in);
    while(!inFile.eof())
    {
        inFile.getline(buffer,256,'\n'); //getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
        s += buffer;
    }
    s += '~';
    inFile.close();
}

void scaner() {
    /*
        共分为三大块，分别是标示符、数字、符号，对应下面的 if   else if  和 else 
    */ 
    for(n = 0; n < 8; n++) { 
        token[n] = NULL;
    }
    ch = prog[p++];
    while(ch==' ') {
        ch = prog[p];
        p++;
    }

    if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z'))  //可能是标示符或者变量名 
    {
        m = 0;
        while( (ch>='0'&&ch<='9') || (ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z') )
        {
            token[m++] = ch;
            ch = prog[p++];
        }
        token[m++] = '\0';
        p--;
        syn = 10;
        for(n=0; n<6; n++)  //将识别出来的字符和已定义的标示符作比较， 
            if(strcmp(token,rwtab[n]) == 0)
            {
                syn = n + 1;
                break;
            }
    }

    else if((ch>='0') && (ch<='9')) {  //数字
        {
            sum = 0;
            while((ch>='0') && (ch<='9'))
            {
                sum = sum * 10 + ch - '0';
                ch = prog[p++];
            }
        }
        p--;
        syn = 11;
        if(sum>32767)
            syn = -1;
    }

    else {
        switch(ch) {  //其他字符 
            case'<':
                m = 0;
                token[m++] = ch;
                ch = prog[p++];
                if(ch=='>') {
                    syn = 21;
                    token[m++] = ch;
                }
                else if(ch=='=') {
                    syn = 22;
                    token[m++] = ch;
                }
                else {
                    syn = 23;
                    p--;
                }
                break;

            case'>':
                m = 0; 
                token[m++] = ch;
                ch = prog[p++];
                if(ch=='=') {
                    syn = 24;
                    token[m++] = ch;
                }
                else {
                    syn = 20;
                    p--;
                }
                break;
            
            case'%':
                m = 0;
                token[m++] = ch;
                ch = prog[p++];
                if(ch == 'd') {
                    syn = 77;
                    token[m++] = ch;
                }
                else if (ch == 's') {
                    syn = 78;
                    token[m++] = ch;
                }
                else{
                    p--;
                }
                break;

            case':': 
                m = 0; 
                token[m++] = ch;
                ch = prog[p++];
                if (ch=='=') {
                    syn = 18;
                    token[m++] = ch;
                }
                else {
                    syn = 17;
                    p--;
                }
                break;
            
            // 处理 '\' + 'n' 的情况
            case'\\':
                m = 0;
                token[m++] = ch;
                ch = prog[p++];
                if(ch == 'n') {
                    syn = 81;
                    token[m++] = ch;
                }
                else{
                    syn = 82;
                    p--;
                }
                break;

            // 处理 # 以及头文件的情况
            case'#':
                m = 0;
                token[m++] = ch;
                ch = prog[p++];
                if (ch == 'i') {
                    token[m++] = ch;
                    ch = prog[p++];
                    while ((ch=='<') || (ch>='a' && ch<='z') || (ch=='.')
                        || (ch>='A' && ch<='Z') || (ch=='>')) {
                        token[m++] = ch;
                        ch = prog[p++];
                    }

                    p--;
                    syn = 91;
                }
                else {
                    syn = 92;
                    p--;
                }
                break;

            case'*':
                syn = 13; token[0] = ch; break;
            case'/':
                syn = 14; token[0] = ch; break;
            case'+':
                syn = 15; token[0] = ch; break;
            case'-':
                syn = 16; token[0] = ch; break;
            case'=':
                syn = 25; token[0] = ch; break;
            case';':
                syn = 26; token[0] = ch; break;
            case'(':
                syn = 27; token[0] = ch; break;
            case')':
                syn = 28; token[0] = ch; break;
            case'{':
                syn = 29; token[0] = ch; break;
            case'}':
                syn = 30; token[0] = ch; break;
            case'"':
                syn = 50; token[0] = ch; break;
            case',':
                syn = 51; token[0] = ch; break;
            // 处理 复制文本时每行末尾'\n' 的情况  
            case'`':
                syn = 0; token[0] = ch; break;
            case 10:
                syn = -2; token[0] = ch; break;
            default: 
                syn = -1; break;
        }
    }
}

int main(void) {
    p = 0;
    row = 1;
    
    // 从文本读入
    string s = "";
    cout << "Input string from in.txt:" << endl;
    readByChar(s);
     for (int i = 0; i < s.length(); i++) {
        prog[p] = s[i];
        p++;
     }
     
    // // 终端输入
    // cout << "Input string from tty: ('`' must input at end)" << endl;
    // do {
    //    cin.get(ch);
    //    prog[p++]=ch;
    // }while(ch!='');

    // 检查输入的字符的 ASCII
    for (int i = 0; i < p; i++) {
        printf("%d\n", prog[i]);
    }

    p = 0;
    do {
        scaner();
        printf("syn=%d\n", syn);
        // sleep(3);
        switch(syn) {
        case 11: cout<< "(" << syn << "," << sum << ")" << endl; break;  
        case -1: cout << "Error in row " << row << " !" << endl; break;
        case -2: row = row + 1; break;
        default: cout << "(" << syn << "," << token << ")" << endl; break;
        }
    }while (syn!=0);

    return 0;
}
