
class A:
    def __init__(self):
        self.avar = 0

class B:
    def __init__(self, a):
        self.bvar = 5
        self.a = a
        self.a.avar = 666

if __name__ == "__main__":
    a = A()
    b = B(a)
    b.a.avar = 999
    print("[shallow copy]  a.avar = {}".format(a.avar))
    print("[shallow copy]  b.a.avar = {}".format(b.a.avar))
 
