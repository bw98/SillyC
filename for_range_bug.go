package main

import (
    "fmt"
)

type Person struct {
    Name string
}

func test() {
    arr := []Person {
        Person{"小明"},
        Person{"小刚"},
    }

    fmt.Printf("%v    %p\n", arr[0], &arr[0])
    fmt.Printf("%v    %p\n", arr[1], &arr[1])
	
    // 想要把 arr 中的 Person 都存入 res 中, 并且为了节省内存使用了指针
    var res []*Person
    for _, v := range arr {
        res = append(res, &v)  // for range 设计, 存入的内存地址是同一个
    }

    fmt.Printf("%v    %p\n", *res[0], res[0])
    fmt.Printf("%v    %p\n", *res[1], res[1])
    
    // 遍历查看结果集
    for _, person := range res {
        fmt.Println("person.Name: ", person.Name)  // 输出是两个小刚
    }

    // 正确做法，使用下标形式的引用/指针
    res = make([]*Person, len(arr))

    for idx := range res {
        res[idx] = &arr[idx]
        fmt.Printf("%v    %p\n", *res[idx], res[idx])
    }

    for idx:= 0; idx < len(res); idx++ {
        res[idx] = &arr[idx]
        fmt.Printf("%v    %p\n", *res[idx], res[idx])
    }

    for _, person := range res {
        fmt.Println("person.Name: ", person.Name)  // 输出是小明, 小刚
    }
    
}

func main() {
    test()

    return
}

