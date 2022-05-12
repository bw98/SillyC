

def f(data, maxspan):
    res = list()
    kv = dict()  # id -> time + action
    for s in data:
        user_id, time_stamp, _ = s.split()
        if user_id in kv:
            span = abs(int(time_stamp) - int(kv[user_id]))
            if span < maxspan:
                res.append(user_id)
        else:
            kv[user_id] = time_stamp

    res.sort()
    return res


# 给了一个string array和maxspan。string包含id,时间，行为（sign-in / sign-out），要求最后的输出是登出时间与登入时间之差小于maxspan的所有id,并按升序排列。重点在于处理string，且sign-in和sign-out的出现顺序并不固定，需要处理

data = ["30 99 sign-in", "30 105 sign-out", "12 100 sign-in", "20 80 sign-in", "12 120 sign-out", "20 101 sign-out", 
        "21 110 sign-in"]
maxspan = 20
print("\ndata = \n" + str(data))
print("\nmaxspan = \n" + str(maxspan))
res = f(data, maxspan)
print("\nres = \n" + str(res))


