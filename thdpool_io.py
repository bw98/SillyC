from concurrent.futures import ThreadPoolExecutor
import time

def task():
    print('Run task and sleep 5 sec')
    time.sleep(5)


executor = ThreadPoolExecutor(max_workers=100)
for i in range(0, 1000):
    executor.submit(task)

