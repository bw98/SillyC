#
# Learn more multiprocessing of Python in Python Official Guide
# https://docs.python.org/3/library/multiprocessing.html
#

import os
from multiprocessing import Pool
from multiprocessing import Process


def f(x):
    print("In f function")
    return x * x

def info(title):
    print("In info function")
    print(title)
    print('module name:', __name__)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())

if __name__ == '__main__':
    # Using Pool
    print ("Using Pool")
    p_block = Pool(3)
    print(p_block.apply(f, [ 666 ]))  # 阻塞式执行
    print(p_block.apply_async(f, [ 666 ]))  # 非阻塞式执行
    # with Pool(5) as p:
        # print(p.map(f, [ 1,2, 3, ]))

    # Using Process class
    print ("Using Process class")
    p1 = Process(target=info, args=('hey Jude',))
    p1.start()
    p2 = Process(target=info, args=('Press F',))
    p2.start()
    p1.join()
    p2.join()

