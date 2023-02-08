from collections import deque

# 实现 Actor 协程版本
# 关键点在于收集消息的队列。本质上，调度器在有需要发送的消息时会一直运行着。计数生成器会给自己发送消息并在一个递归循环中结束

class ActorScheduler:
    def __init__(self):
        self.actors_ = {}          # Mapping of names to actors
        self.msg_queue_ = deque()   # Message queue

    def new_actor(self, name, actor):
        '''
        Admit a newly started actor to the scheduler and give it a name
        '''
        self.msg_queue_.append((actor,None))
        self.actors_[name] = actor

    def send(self, name, msg):
        '''
        Send a message to a named actor
        '''
        print('debug line 22 in send, name = {}, msg = {}'.format(name, msg))
        actor = self.actors_.get(name)
        if actor:
            self.msg_queue_.append((actor,msg))

    def run(self):
        '''
        Run as long as there are pending messages.
        '''
        while self.msg_queue_:
            actor, msg = self.msg_queue_.popleft()
            try:
                print('debug line 34 before send, actor = {}, msg = {}'.format(actor, msg))
                actor.send(msg)  # 重点在这里, send() 是生成器自带的方法，相当于可传参版本的 next(), 传给 yield 左边的变量
            except StopIteration:
                pass


# Example use
if __name__ == '__main__':
    def printer():
        while True:
            print('debug 44 line in printer()')
            msg = yield
            print('Got:', msg)

    def counter(sched):
        while True:
            # Receive the current count
            print('debug 51 line in counter(), sched = {}'.format(sched))
            n = yield
            if n == 0:
                break
            # Send to the printer task
            sched.send('printer', n)
            # Send the next count to the counter task (recursive)
            sched.send('counter', n-1)

    sched = ActorScheduler()
    # Create the initial actors
    sched.new_actor('printer', printer())
    print('debug 63 line create generator printer ', sched.actors_['printer'])
    sched.new_actor('counter', counter(sched))
    print('debug 65 line create generator counter ', sched.actors_['counter'])

    # Send an initial message to the counter to initiate
    print('debug 68 line send counter with msg 10')
    sched.send('counter', 10)
    print('debug 70 line scheduler starts to run')
    sched.run()

