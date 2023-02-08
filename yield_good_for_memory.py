"""
简单测试了一下没有使用以及使用 yield 时, 计算平方数代码的运行时间以及内存使用情况

总论:
当生成数字的个数为十万到千万时, 对于执行速度, 非 yield 并且存储中间结果的版本代码(test0)是 yield 版本代码(test2)的 1.5 倍 (快一半),
非 yield 不存储中间结果的版本(test1)比 yield 版本(test2)快了 14.75%;
对于内存占用来说, test0 从 kb 暴涨到 mb 级别, 而 test1 和 yield 版本代码(test2)一直都是 byte 级别

Addition by 02/04/2023:
It's not a good example to analyze the pros/cons of 'yield'.
Just look at test1 and test2, if we don't use 'yield', it can still run in just a small piece of memory like bytes,
because we don't save the intermediate data in a list or other data structures.
But we can still assume that 'yield' can save usage rate of memory. Just think about scenario, in an AI project, a function can
generate very large data and we can't get all the resullt at once. So we have to use 'yield' to get data in batches.


"""

import tracemalloc
import time
import numpy as np

N = 10000000
tracemalloc.start()

def get_squre_numbers_test0(num_len):
    start_time = time.time()

    s = 0
    random_list = np.random.rand(num_len)  # Store intermediate result
    for i in range(N):
        s += random_list[i] ** 2

    end_time = time.time()
    print('[Disable yield but store intermediate result] Calculated sum of squre numbers, which is {}'.format(s))
    print('Time cost is {} second'.format(end_time - start_time))
    snapshot = tracemalloc.take_snapshot()
    top_stats = snapshot.statistics('lineno')
    for stat in top_stats[:5]:
        print(stat)


def get_random_squre_number():
    return np.random.random() ** 2


def get_squre_numbers_test1(num_len):
    start_time = time.time()

    s = 0
    for i in range(N):
        s += get_random_squre_number()

    end_time = time.time()
    print('[Disable yield and not store intermediate result] Calculated sum of squre numbers, which is {}'.format(s))
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
    print("Test disabled 'yield' and store intermediate data Start...")
    get_squre_numbers_test0(N)
    print('Test End...\n\n')

    print("Test disabled 'yield' and not store intermediate data Start...")
    get_squre_numbers_test1(N)
    print('Test End...\n\n')

    print("Test enabled 'yield' Start...")
    get_squre_numbers_test2(N)  # 执行该测试时需要注释其他测试，否则内存测试会不准确
    print('Test End...\n\n')

