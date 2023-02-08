
def consumer():
    r = "Just wanna go into loop, return, and wait to be continued at code line 'n = yield' "
    while True:
        n = yield r
        if not n:
            return
        print('[CONSUMER] Consuming %s...' % n)
        r = '%d00 OK' % n


def produce(c):
    res = c.send(None)
    print('[DEBUG line 14] res = ', res)
    n = 0
    while n < 5:
        n = n + 1
        print('[PRODUCER] Producing %s...' % n)
        r = c.send(n)
        print('[PRODUCER] Consumer return: %s' % r)
    c.close()

c = consumer()
produce(c)

