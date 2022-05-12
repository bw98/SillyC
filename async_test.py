import asyncio

async def others(i: int):
    print("start")
    await asyncio.sleep(5)
    print('end')
    return '返回值: ' + str(i)

async def func():
    print("执行协程函数 func 内部代码")
    # 遇到IO操作挂起当前协程（任务），等IO操作完成之后再继续往下执行。当前协程挂起时，事件循环可以去执行其他协程（任务）。
    response = await others(1)
    print("IO请求结束，结果为: ", response)

async def func2():
    print("执行协程函数 func2 内部代码")
    # 遇到IO操作挂起当前协程（任务），等IO操作完成之后再继续往下执行。当前协程挂起时，事件循环可以去执行其他协程（任务）。
    response = await others(2)
    print("IO请求结束，结果为: ", response)

async def main():
    # 将协程对象封装成task对象，并将协程立即加入事件循环，同时追踪协程的状态
    # task1 = asyncio.create_task(func())
    # task2 = asyncio.create_task(func2())
    task1 = asyncio.ensure_future(func())
    task2 = asyncio.ensure_future(func2())
    await task1
    await task2

loop = asyncio.get_event_loop()

# 不能直接这么跑, 相当于同步了
# loop.run_until_complete(func())
# loop.run_until_complete(func2())

# 执行 main 将协程都加入 loop
loop.run_until_complete(main())

