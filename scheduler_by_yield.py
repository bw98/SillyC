from collections import deque

# 实现简单任务调度器, 要求使用 yield 使任务挂起, 模拟 os 让出 cpu core 给其他任务执行

def countdown(n):
    n_backup = n
    while n > 0:
        print('T-minus', n)
        yield
        n -= 1

    print('count down end with ', n_backup)

def countup(n):
    x = 0
    while x < n:
        print('Counting up', x)
        yield
        x += 1

    print('count up end with ', n)

class TaskScheduler:
    def __init__(self):
        self._task_queue = deque()

    def new_task(self, task):
        '''
        Admit a newly started task to the scheduler
        '''
        self._task_queue.append(task)

    def run(self):
        '''
        Run until there are no more tasks
        '''
        while self._task_queue:
            task = self._task_queue.popleft()
            try:
                # Run until the next yield statement
                next(task)
                self._task_queue.append(task)
            except StopIteration:
                # Generator is no longer executing
                pass

# Example use
sched = TaskScheduler()
sched.new_task(countdown(10))  # 倒计时 15 sec
sched.new_task(countdown(5))
sched.new_task(countup(15))  # 计时 15 sec
sched.run()

