package main

import (
	"fmt"
	"context"
	"time"
)

func main() {
	ctx, cancel := context.WithCancel(context.Background())

    fmt.Println("start 1")
	go func(ctx context.Context) {
		for {
			select {
			case <-ctx.Done():
				fmt.Println("stop 1...")
				return
			default:
				fmt.Println("111111111111111111...")
				time.Sleep(2 * time.Second)
			}
		}
	}(ctx)

    fmt.Println("start 2")
	go func(ctx context.Context) {
		for {
			select {
			case <-ctx.Done():
				fmt.Println("stop 2...")
				return
			default:
				fmt.Println("2222222222222222...")
				time.Sleep(3 * time.Second)
			}
		}
	}(ctx)

	time.Sleep(10 * time.Second)
	fmt.Println("可以了，通知停止")
	cancel()

    fmt.Println("start 3 after cancel()")
	go func(ctx context.Context) {
		for {
			select {
			case <-ctx.Done():
				fmt.Println("stop 3...")
				return
			default:
				fmt.Println("3333333333333...")
				time.Sleep(3 * time.Second)
			}
		}
	}(ctx)

	time.Sleep(20 * time.Second)
	fmt.Println("程序退出")
}

