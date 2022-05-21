package main

import (
    "fmt"
    "time"
    "sync"
    // "runtime"
)

var MU sync.Mutex
var GVAR int

func test1() {
	// runtime.GOMAXPROCS(1)  // 指定最大 P 为 1，从而管理协程最多的线程为 1 个

    task_num := 10
	wg := sync.WaitGroup{}  // 控制等待所有协程都执行完再退出 main goroutine
	wg.Add(task_num)
    MU.Lock()
    
    GVAR = 0
    
    for i := 0; i < task_num; i++ {
        GVAR += 1
	    fmt.Printf("[main goroutine] i = %d, GVAR = %d\n", i, GVAR)

	    go func(i int) {
            MU.Lock()
            GVAR -= 1
            cur_gvar := GVAR
            MU.Unlock()
	    	
            fmt.Printf("[new goroutine] i = %d, cur_gvar = %d\n", i, cur_gvar)

	    	time.Sleep(time.Second * 3)
	    	wg.Done()
	    }(i)
    }
	
    MU.Unlock()
    wg.Wait()
}

func main() {
    test1()

    return
}

