import numpy as np


class BankerAlgorithm(object):
    """
    对各进程请求通过银行家算法实现分配资源
    """

    def __init__(self, available, max, allocation, need, safeList, request,
                 request_name):
        self.Available = available  # 可利用各资源总数
        self.Max = max  # 各进程最大需求资源数
        self.Allocation = allocation  # 已分配各进程的资源数
        self.Need = need  # 各进程尚需的资源数
        self.safeList = safeList  # 安全进程执行序列
        self.Request = request  # 各进程对各资源的请求
        self.Request_name = request_name  # 进程名称

    def input_request(self):
        try:
            self.Request_name = input("请输入请求线程的编号：\n 0   1    2    3    4 \n")
            self.Request_name = int(self.Request_name)
            Request_new = input("请输入P{}的请求资源数(如：* * *) :\n".format(self.Request_name))
            Request_new = list(Request_new)

            for x in range(0, 5, 2):  # 去除输入的空格
                i = int(Request_new[x])
                self.Request.append(i)

            self.Request = np.array(self.Request)
        except Exception as e:
            print("输入错误，请重新输入")
            print(e)
            # 回调本身函数
            self.input_request()

    def safeAlgorithm(self):
        work = self.Available  # 分配work向量
        Finish = [False] * 5  # 分配Finish向量

        while False in Finish:
            for i in range(0, 5):
                for j in range(0, 3):
                    if ((Finish[i] == False) and ((self.Need[i] <= work).all())):
                        for m in range(3):
                            work[m] = work[m] + self.Allocation[i][m]
                        Finish[i] = True
                        self.safeList.append(i)
                    else:
                        break

        if False in Finish:
            print("*" * 45)
            print("您输入的请求资源数:{}".format(self.Request))
            print("您输入的请求进程是{}".format(self.Request_name))
            print("系统安全性：不安全状态")
            print("*" * 45)
        else:
            print("*" * 45)
            print("您输入的请求进程是{}".format(self.Request_name))
            print("您输入的请求资源数:{}".format(self.Request))
            print("系统安全性：系统安全")
            print("安全序列为：", self.safeList)
            print("*" * 45)

    def run(self):
        # BUG:调用不了类内其他方法 input_Request
        self.input_Request()

        if ((self.Request <= self.Need[self.Request_name]).all()):
            if ((self.Request <= self.Available).all()):
                self.Available -= self.Request  # 可利用资源减少
                self.Need[self.Request_name] -= self.Request  # 尚需的资源数减少
                self.Allocation[self.Request_name] += self.Request  # 已分配资源增加
                self.safeAlgorithm()  # 执行安全算法
            else:
                print("请求超出可利用的资源，请等待")
        else:
            print("线程请求超出所需总资源数")


if __name__ == "__main__":
    available = np.array([3, 3, 2]),
    max = np.array([[7, 5, 3], [3, 2, 2], [9, 0, 2], [2, 2, 2], [4, 3, 3]]),
    allocation = np.array([[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]]),
    need = np.array([[7, 4, 3], [1, 2, 2], [6, 0, 0], [0, 1, 1], [4, 3, 1]]),
    safeList = [],
    request = [],
    request_name = ""
    b = BankerAlgorithm(available, max, allocation, need, safeList, request, request_name)
    b.run()

