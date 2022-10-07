

def f(data):
    a = "".join(data[0].split())
    b = "".join(data[1].split())
    print("a: ", a)
    print("b: ", b)

    if len(a) != len(b):
        return False

    for i in range(0, len(a)):
        if ord(a[i]) - ord(b[i]) > 1:
            return False

    return True



# Q: 输入2个 string 数组 a = 4 2 3 4 0, b = 1 2 3 4 5, 具体操作就是去空格 转int ，排序 逐位比较差值是否大于一


data = [ "4 2 3 4 0 ", "4 3 2 3 0  " ]
print("Input: " + str(data))

res = f(data)
print("Ouput: " + str(res))


