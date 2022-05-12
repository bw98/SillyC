#coding:utf-8
import threading
import time

res = 0
def sum(start, end, step=1):
    global res
    for it in range(int(start), int(end+1), step):
        res += it

def threadSum(start, end, step=1, thread_num=1):
    global res

    start = int(start)
    end = int(end)
    thread_num = int(thread_num)
    if thread_num <= 0 :
        thread_num = 1
    i = 0
    d = int((end - start) / thread_num)
    threads = [] # define a thread pool

    while start + i*d < end:
        if start + (i+1)*d < end:
            e = start + (i+1)*d - step
        else:
            e = end
        
        threads.append(threading.Thread(target=sum,args=(start +i*d, e, step)))
        i += 1

    for thr in threads:
        thr.start()
        print("CURRENT TIME: {}".format(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))
    for thr in threads:
        thr.join()

    return res


if __name__ == "__main__":
    threadSum(start=0, end=50, step=1, thread_num=5)
    print(res)

