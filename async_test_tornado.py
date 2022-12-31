import asyncio
import tornado.gen
import tornado.ioloop

async def others(sec: int):
    print("[others] start, sleep second is ", sec)
    await asyncio.sleep(sec)
    print('[others] end')
    return '函数 others 返回值是 ' + str(sec)

@tornado.gen.coroutine
def func():
    print("[func] 执行协程函数 func 内部代码")
    # 遇到IO操作挂起当前协程（任务），等IO操作完成之后再继续往下执行。当前协程挂起时，事件循环可以去执行其他协程（任务）。
    response = yield others(2)
    print("[func] IO请求结束, 结果为: ", response)

@tornado.gen.coroutine
def func2():
    print("[func2] 执行协程函数 func2 内部代码")
    # 遇到IO操作挂起当前协程（任务），等IO操作完成之后再继续往下执行。当前协程挂起时，事件循环可以去执行其他协程（任务）。
    response = yield others(5)
    print("[func2] IO请求结束, 结果为: ", response)

async def main():
    # task1 = asyncio.create_task(func())
    # task2 = asyncio.create_task(func2())
    task1 = asyncio.ensure_future(func())
    task2 = asyncio.ensure_future(func2())
    await task1
    await task2
    # yield task1
    # yield task2

import tornado.ioloop
loop = tornado.ioloop.IOLoop.current()
loop.run_sync(main)
# loop = asyncio.get_event_loop()
# loop.run_until_complete(func())
# loop.run_until_complete(func2())
# loop.run_until_complete(main())

