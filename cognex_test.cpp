#include <iostream>
#include <math.h>

using namespace std;

void test1() {
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {6, 7, 8, 9, 10};
    
    // int* p = &a[0];
    // int* q = &b[0];
    int* p = a;
    int* q = b;
    printf("%d\n", *p);
    printf("%d\n", *q);
    *p++ = *q++;
    printf("%d\n", a[0]);
    printf("%d\n", b[0]);
    printf("%d\n", *p);
    printf("%d\n", *q);

    p = NULL;
    q = NULL;
}

void test2() {
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {6, 7, 8, 9, 10};
    
    // int* p = &a[0];
    // int* q = &b[0];
    int* p = a;
    int* q = b;
    printf("%d\n", *p);
    printf("%d\n", *q);
    ++*p = ++*q;
    printf("%d\n", a[0]);
    printf("%d\n", b[0]);
    printf("%d\n", *p);
    printf("%d\n", *q);

    p = NULL;
    q = NULL;
}

int main() {
    test1();
    test2();

    return 0;
}
