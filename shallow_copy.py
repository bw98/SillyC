
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
    print("[shallow copy] id of a.avar is {}, a.avar = {}".format(id(a.avar), a.avar))
    print("[shallow copy] id of b.avar is {}, b.a.avar = {}".format(id(b.a.avar), b.a.avar))
 
