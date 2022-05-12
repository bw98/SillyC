#coding:utf-8
import threading
import time
import numpy as np
import queue 

threads = queue.Queue()
threadLock = threading.Lock()


def thread_quick_sort(arr, p, r):
    if p < r:
        q = partition(arr, p, r)

        ## the origin version
        # thread_quick_sort(arr, p, q-1)
        # thread_quick_sort(arr, q+1, r)

        # multi-thd version, probably it gets False Sharing problem
        threads.put(threading.Thread(target=thread_quick_sort, args=(arr, p, q-1)))
        threads.put(threading.Thread(target=thread_quick_sort, args=(arr, q+1, r)))
        thd1 = threads.get()
        thd2 = threads.get()
        thd1.start()
        thd2.start()
        thd1.join()
        thd2.join()

def partition(arr, p, r):
    x = arr[r] # choose last element as pivot element
    i = p - 1 # A[p...i] is seq which is smaller than pivot element, if i < p then seq is empty

    for j in range(p, r):
        if arr[j] <= x:
            i = i + 1
            arr[i], arr[j] = arr[j], arr[i]
    
    arr[i+1], arr[r] = arr[r], arr[i+1]

    return i+1
    

if __name__ == "__main__":
    # arr = np.random.randn(1000000)
    arr = [1, 2, 3, 1, 5, 4, 6, 8]
    print("before sort arr is:{}\n".format(arr))
    thread_quick_sort(arr, 0, len(arr)-1)
    print("after sort arr is:{}\n".format(arr))

