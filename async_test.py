import asyncio
import time

async def others(sec: int):
    print('[others] start, sleep second is ', sec)
    await asyncio.sleep(sec)
    print('[others] start, sleep second is ', sec)
    return '[others response] 返回值: ' + str(sec)

async def func():
    print('[func] 执行协程函数 func 内部代码')
    # 遇到IO操作挂起当前协程（任务），等IO操作完成之后再继续往下执行。当前协程挂起时，事件循环可以去执行其他协程（任务）。
    response = await others(3)
    print('[func] IO请求结束，结果为: ', response)

async def func2():
    print('[func2] 执行协程函数 func2 内部代码')
    # 遇到IO操作挂起当前协程（任务），等IO操作完成之后再继续往下执行。当前协程挂起时，事件循环可以去执行其他协程（任务）。
    response = await others(5)
    print('[func2] IO请求结束，结果为: ', response)

async def func3():
    print('[func3] 执行协程函数 func3 内部代码')
    for i in range(1, 4):
        await asyncio.sleep(i)
        print("[func3] sleep second = ", i)

async def main():
    # 将协程对象封装成task对象，并将协程立即加入事件循环，同时追踪协程的状态
    # task1 = asyncio.create_task(func())
    # task2 = asyncio.create_task(func2())
    task1 = asyncio.ensure_future(func())
    task2 = asyncio.ensure_future(func2())
    task3 = asyncio.ensure_future(func3())
    await task1
    await task2  # (存疑) 好像这句话不用写也会执行 func2 func3
    await task3


# 执行主线程
loop = asyncio.get_event_loop()

# 不能直接这么跑, 相当于同步了
# loop.run_until_complete(func())
# loop.run_until_complete(func2())

# 执行 main 将协程都加入 loop
loop.run_until_complete(main())

