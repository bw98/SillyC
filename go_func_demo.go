package main

import (
    "fmt"
    "time"
    "sync"
    "runtime"
)

func test1() {
	runtime.GOMAXPROCS(1)  // 指定最大 P 为 1，从而管理协程最多的线程为 1 个
	wg := sync.WaitGroup{}  // 控制等待所有协程都执行完再退出程序
	wg.Add(2)
	
    // 运行一个协程
	go func() {
		fmt.Println(1)
		fmt.Println(2)
		fmt.Println(3)
		wg.Done()
	}()

	// 运行第二个协程
	go func() {
		fmt.Println(65)
		fmt.Println(66)
		// 设置个睡眠，让该协程执行超时而被挂起，引起超时调度
		time.Sleep(time.Second)
		fmt.Println(67)
		wg.Done()
	}()
	
    wg.Wait()
}

func test2() {
    runtime.GOMAXPROCS(1)
	wg := sync.WaitGroup{}
	wg.Add(20)

    // go func 传参 bug
	for i := 0; i < 10; i++ {
		go func() {
			fmt.Println("A: ", i)
			wg.Done()
		} ()
	}

    for i := 0; i < 10; i++ {
		go func(i int) {
			fmt.Println("B: ", i)
			wg.Done()
		} (i)
	}

	wg.Wait()
}

func main() {
    // test1()
    test2()

    return
}

