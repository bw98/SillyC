#
# Learn more multiprocessing of Python in Python Official Guide
# https://docs.python.org/3/library/multiprocessing.html
#

import os
from multiprocessing import Pool
from multiprocessing import Process


def f(x):
    return x * x

def info(title):
    print(title)
    print('module name:', __name__)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())

if __name__ == '__main__':
    # Using Pool
    print ("Using Pool")
    with Pool(5) as p:
        print(p.map(f, [ 1,2, 3, ]))

    # Using Process class
    print ("Using Process class")
    p1 = Process(target=info, args=('hey Jude',))
    p1.start()
    p2 = Process(target=info, args=('Press F',))
    p2.start()
    p1.join()
    p2.join()

