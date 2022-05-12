#coding:utf-8
import threading
import time
import queue

threads = queue.Queue()
threadLock = threading.Lock()

# custom thread class for recording the return value of thread
class MyThread(threading.Thread):
    def __init__(self,func,args=()):
        super(MyThread,self).__init__()
        self.func = func
        self.args = args
    def run(self):
        self.result = self.func(*self.args)
    def get_result(self):
        try:
            return self.result # if child-thread does not use join method, here may cast None self.result Exp
        except Exception:
            return None


def merge(left, right):
    # prerequisite: both left and right is sorted list
    ret = []
    i = 0
    j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            ret.append(left[i])
            i += 1
        else:
            ret.append(right[j])
            j += 1

    if i == len(left):
        for it in right[j:]:
            ret.append(it)
    else:
        for it in left[i:]:
            ret.append(it)
    print("after merge, left is {}, right is {}, ret is {}".format(left, right, ret))

    return ret

def mergeSort(arr):
    print("current arr is:{}".format(arr))
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2

    # # original version
    # left  = mergeSort(arr[:mid])
    # right = mergeSort(arr[mid:])

    # # multi-thd version, maybe Flase Sharing problem
    threads.put(MyThread(mergeSort, [arr[:mid]]))
    threads.put(MyThread(mergeSort, [arr[mid:]]))
    thread1 = threads.get()  # return first item of threads queue
    thread2 = threads.get()
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()
    right = thread1.get_result();
    left = thread2.get_result();
    print("threads' len is:{}".format(threads.qsize()))
    return merge(left, right)


if __name__ == "__main__":
    arr = [1, 5, 4, 8 ,7, 6]
    print('Before sort, arr is:{}\n'.format(arr))
    arr = mergeSort(arr)
    print('After sort, arr is:{}\n'.format(arr))

