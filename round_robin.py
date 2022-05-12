
PICK_NUM = 20
NODES = ['A', 'B', 'C']
WEIGHT = [3, 2, 1]

# basic Round Robin
def select():
    for i in range(PICK_NUM):
        node = NODES[i % len(NODES)]
        print(node)

# weighted RR
def select2():
    idx = 0
    cnt = 0
    for _ in range(PICK_NUM):
        cnt += 1
        if cnt > WEIGHT[idx]:
            cnt = 1
            idx += 1
            if idx >= len(NODES):
                idx = 0
        
        node = NODES[idx]
        print(node)

# Optmization of Round Robin
# smoothly weighted RR
# 算法核心: 计算总权重, 每次所有结点的当前权重都减去总权重, 然后取当前权重最大值的那个结点
#
def select3():
    total = sum(WEIGHT)
    curWeight = [0] * len(NODES)
    for _ in range(PICK_NUM):
        for i in range(len(curWeight)):
            curWeight[i] += WEIGHT[i]

        maxVal = curWeight[0]
        maxIdx = 0
        for i in range(1, len(curWeight)):
            val = curWeight[i]
            if maxVal < val:
                maxVal = val
                maxIdx = i

        curWeight[maxIdx] -= total
        node = NODES[maxIdx]
        print(node)

# Optmization of Round Robin
# smoothly weighted RR, and plus an optimization -- adjustive weight
# 算法核心: current weight 不再只是每轮加上固定权重，而是加上 effective weight (结点连接出异常的话 penalty 权重)
def check(effWeight, ithRound):
    if ithRound == 5:
        # 模拟出错, 到第六轮时, A 出问题了，应该要降权
        effWeight[0] -= 2
    else:
        # 模拟成功，应该要逐步加权重,这里为了 demo 方便，先不加
        pass

def select4():
    curWeight = [0] * len(NODES)
    effWeight = list(WEIGHT)
    for ithRound in range(PICK_NUM):
        for i in range(len(curWeight)):
            curWeight[i] += effWeight[i]

        check(effWeight, ithRound)

        maxVal = curWeight[0]
        maxIdx = 0
        total = sum(effWeight)
        for i in range(1, len(curWeight)):
            val = curWeight[i]
            if maxVal < val:
                maxVal = val
                maxIdx = i

        curWeight[maxIdx] -= total
        node = NODES[maxIdx]
        print(node)


if __name__ == "__main__":
    print('Test round robin')
    # select()
    # select2()
    # select3()
    select4()

