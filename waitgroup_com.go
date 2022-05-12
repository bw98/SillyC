package main

import (
    "fmt"
    "time"
    "sync"
)

func produce(ch chan int) {
    for {
        time.Sleep(1 * time.Second)
        ch <- 1
    }
}

func produce3(ch chan int) {
    for {
        time.Sleep(3 * time.Second)
        ch <- 3
    }
}

func stop(ch chan bool) {
    time.Sleep(10 * time.Second)
    ch <- true
}

func main() {
    // ch := make(chan int)
    // stopCh := make(chan bool)
    // go produce(ch)
    // go produce3(ch)
    // go stop(stopCh)

    // for {
    //     select {
    //         case x := <- ch:
    //             fmt.Println(x)
    //         case <- stopCh:
    //             fmt.Println("End")
    //             return
    //     }
    // }

    taskNum := 10
    var wg sync.WaitGroup
    wg.Add(taskNum)

    for  task := 0; task < taskNum; task++ {
        t := task
        go func () {
            fmt.Println(t)
            wg.Done()
        }()
    }
    
    wg.Wait()

    return
}

