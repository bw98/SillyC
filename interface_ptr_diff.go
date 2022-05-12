package main

import (
    "fmt"
)

type MyClass struct {
    data int
}

func test1(o MyClass) {
    fmt.Printf("%p\n", &o);
}

func test2(o *MyClass) {
    fmt.Printf("%p\n", o);
}

func test3(o interface{}) {
    fmt.Printf("%p\n", o);
    test4(o);
}

func test4(o interface{}) {
    fmt.Printf("%p\n", o);
    o.(*MyClass).data = 6;
}

func main() {
    // o := MyClass{data: 5}
    // fmt.Printf("%p\n", &o);
    // test1(o);
    // test2(&o);
    // test3(&o);
    // fmt.Printf("%d\n", o.data);

    o1 := MyClass{data: 5}
    o2 := MyClass{data: 6}
    o3 := MyClass{data: 7}
    var a []*MyClass
    a = append(a, &o1, &o2, &o3)
    var e []*MyClass
    e = a[5:]
    fmt.Printf("%v %p\n", a[1], &a[1]);
    fmt.Printf("%v %p\n", e[0], &e[0]);
    
    return
}

