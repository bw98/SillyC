"""
简单测试了一下没有使用以及使用 yield 时, 计算平方数代码的运行时间以及内存使用情况

For yield-disabled code:

    Test disabled 'yield' Start...
    [Disable yield] Calculated sum of squre numbers, which is 33395.189080753276
    Time cost is 0.08385491371154785 second
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:12: size=781 KiB, count=2, average=391 KiB
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:13: size=28 B, count=1, average=28 B
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:14: size=24 B, count=1, average=24 B
    Test End...

For yield-enabled code:
    Test enabled 'yield' Start...
    [Enable yield] Calculated sum of squre numbers, which is 33367.23246257554
    Time cost is 0.11679911613464355 second
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:35: size=112 B, count=1, average=112 B
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:27: size=79 B, count=2, average=40 B
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:26: size=76 B, count=2, average=38 B
    /Users/weifeng.lai/SillyCodeCollection/yield_good_for_memory.py:36: size=28 B, count=1, average=28 B
    Test End...

总论: 当生成数字的个数为十万到千万时, 对于执行速度, 非 yield 版本代码是 yield 版本代码的 1.5 倍 (快一半),
但是对于内存占用来说, yield 版本代码一直都是 byte 级别, 而非 yield 版本代码占用的代码从 kb 暴涨到 mb 级别

"""

import tracemalloc
import time
import numpy as np

N = 10000000
tracemalloc.start()

def get_squre_numbers_test(num_len):
    start_time = time.time()

    s = 0
    random_list = np.random.rand(num_len)
    for i in range(N):
        s += random_list[i] ** 2

    end_time = time.time()
    print('[Disable yield] Calculated sum of squre numbers, which is {}'.format(s))
    print('Time cost is {} second'.format(end_time - start_time))
    snapshot = tracemalloc.take_snapshot()
    top_stats = snapshot.statistics('lineno')
    for stat in top_stats[:5]:
        print(stat)


def yield_random_number(num_len):
    for i in range(num_len):
        yield np.random.random()

def get_squre_numbers_test2(num_len):
    start_time = time.time()

    s = 0
    # random_list = list()
    random_sq_gen = yield_random_number(num_len)
    for i in range(num_len):
        s += next(random_sq_gen) ** 2  # 当然这步也可以将 yield 的元素存入一个 list 然后再 sum, 但是这样就没必要用 yield 了
        # random_list.append(next(random_sq_gen))

    end_time = time.time()
    print('[Enable yield] Calculated sum of squre numbers, which is {}'.format(s))
    print('Time cost is {} second'.format(end_time - start_time))
    snapshot = tracemalloc.take_snapshot()
    top_stats = snapshot.statistics('lineno')
    for stat in top_stats[:5]:
        print(stat)


if __name__ == '__main__':
    print("Test disabled 'yield' Start...")
    get_squre_numbers_test(N)
    print('Test End...\n\n')

    print("Test enabled 'yield' Start...")
    get_squre_numbers_test2(N)  # 执行该测试时需要注释其他测试，否则内存测试会不准确
    print('Test End...\n\n')

