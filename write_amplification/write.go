package main

import (
    "fmt"
    "log"
    "os"
    "io"
    "unsafe"
    "github.com/ncw/directio"
)

const (
    AlignSize = 512
)
 
// 在 block 这个字节数组首地址，往后找，找到符合 AlignSize 对齐的地址，并返回
// 这里用到位操作，速度很快
func alignment(block []byte, AlignSize int) int {
   return int(uintptr(unsafe.Pointer(&block[0])) & uintptr(AlignSize - 1))
}
 
// 分配 BlockSize 大小的内存块
// 地址按照 512 对齐
// 缺点是为了对齐而浪费了多余空间
func AlignedBlock(BlockSize int) []byte {
   // 分配一个，分配大小比实际需要的稍大
   block := make([]byte, BlockSize + AlignSize)
 
   // 计算这个 block 内存块往后多少偏移，地址才能对齐到 512 
   diff := alignment(block, AlignSize)
   offset := 0
   if diff != 0 {
      offset = AlignSize - diff
   }
 
   // 偏移指定位置，生成一个新的 block，这个 block 将满足地址对齐 512；
   block = block[offset : offset + BlockSize]
   if BlockSize != 0 {
      // 最后做一次校验 
      a = alignment(block, AlignSize)
      if a != 0 {
         log.Fatal("Failed to align block")
      }
   }
   
   return block
}

func test1() {
    block := AlignedBlock(666)
    fmt.Printf("block: %v, address of block: %p\n", block, block)
}

func test2() {
    fp, err := directio.OpenFile("test.txt", os.O_RDONLY, 0660)
    fmt.Printf("err: %v, fp: %v\n", err, fp)

    // 创建地址按照 4k 对齐的内存块
    buffer := directio.AlignedBlock(directio.BlockSize)
    // 把文件数据读到内存块中
    _, err = io.ReadFull(fp, buffer)
    fmt.Printf("err: %v, address of data: %p, data: %v\n", err, buffer, buffer)
}

func main() {
    // test1()
    test2()

    return 
}

