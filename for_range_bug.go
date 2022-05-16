package main

import (
    "fmt"
)

type Person struct {
    name string
}

func test() {
    arr := []Person {
        Person{"小明"},
        Person{"小刚"},
    }
	
    // 想要把 arr 中的 Person 都存入 res 中, 并且为了节省内存使用了指针
    var res []*Person
    for _, v := range arr {
        res = append(res, &v)  // for range 设计, 存入的内存地址是同一个
    }
    
    // 遍历查看结果集
    for _, person := range res {
        fmt.Println("person.name: ", person.name)  // 输出是两个小刚
    }

    // 正确做法，使用下标形式的引用/指针
    res = make([]*Person, len(arr))
    for idx := range arr {
        res[idx] = &arr[idx]
    }

    for _, person := range res {
        fmt.Println("person.name: ", person.name)  // 输出是小明, 小刚
    }
    
}

func main() {
    test()

    return
}

