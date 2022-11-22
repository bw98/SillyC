import numpy as np
import pandas as pd

import dask
import dask.dataframe as dd
import dask.array as da
import dask.bag as db
from dask.distributed import Client


if __name__ == "__main__":
    # 创建 100 * 100 的矩阵, 每个 chunk 为 10 * 10
    # x = da.random.random((100, 100), chunks=(10, 10))
    x = da.random.normal(10, 0.1, size=(100, 100), chunks=(10, 10))
    print(x)
    print(x.compute())

    # 构造 DataFrame
    index = pd.date_range("2021-09-01", periods=2400, freq="1H")
    df = pd.DataFrame({ "a": np.arange(2400), "b": list("abcaddbe" * 300)},
                      index=index)
    ddf = dd.from_pandas(df, npartitions=10)
    print("\n\n\n-------------------------ddf--------------------------")
    print(ddf)

    # 每个分区覆盖的索引值
    print("\n\n\n-------------------------divisions--------------------------")
    print(ddf.divisions)

    # 访问特定分区
    print("\n\n\n-------------------------divisions[1]--------------------------")
    print(ddf.partitions[1])

    # Array 结构
    print("\n\n\n-------------------------Array Structure--------------------------")
    data = np.arange(100_000).reshape(200, 500)
    a = da.from_array(data, chunks=(100, 100))
    print(a)

    # 检查块
    print("\n\n\n-------------------------Chunks of Array--------------------------")
    print(a.chunks)

    # 访问特定的数据块
    print("\n\n\n-------------------------1st to 3rd Chunks of Array--------------------------")
    print(a.blocks[1, 3])

    # 索引
    # 索引 Dask 集合就像切片 numpy 数组或 pandas 的 DataFrame
    print("\n\n\n-------------------------Index--------------------------")
    print(ddf.b)
    print(ddf["2021-10-01": "2021-10-09 5:00"])

    # Array 结构的索引
    print("\n\n\n-------------------------Index of Array--------------------------")
    print(a[:50, 200])

    # 计算
    # Dask 采用懒惰评估机制，直到你要求计算的结果才会被计算出来
    # 相应地，会生成一个用于计算的 Dask 任务图
    # 任何时候你有一个 Dask 对象并且你想得到结果，调用 compute 计算
    print("\n\n\n-------------------------Compute--------------------------")
    print(ddf.a.mean())
    print(ddf.a.mean().compute())
    print(ddf.b.unique())
    print(ddf.b.unique().compute())

    # 方法可以像 pandas 一样链接在一起
    print("\n\n\n-------------------------Compute like Pandas--------------------------")
    result = ddf["2021-10-01": "2021-10-09 5:00"].a.cumsum() - 100
    print(result)
    print(result.compute())


    print("\n\n\n-------------------------Compute Array--------------------------")
    print(a.mean())
    print(a.mean().compute())
    print(np.sin(a))
    print(np.sin(a).compute())
    print(a.T)
    print(a.T.compute())

    print("\n\n\n-------------------------Compute like Numpy--------------------------")
    b = a.max(axis=1)[::-1] + 10
    print(b)
    print(b[:10].compute())


    # 惰性计算
    # 通常在并行化现有代码库或构建自定义算法时, 会遇到可并行化的代码,
    # 但不仅仅是大型 DataFrame 或数组,
    # Dask Delayed 允许将单个函数调用包装到一个延迟构造的任务图中
    print("\n\n\n-------------------------Idle Computing--------------------------")
    @dask.delayed
    def inc(x):
        return x + 1

    @dask.delayed
    def add(x, y):
        return x + y

    x = 0
    y = 0
    x = inc(1)       # 没有开始计算
    y = inc(2)       # 没有开始计算
    z = add(x, y)    # 没有开始计算
    print(z.compute())  # 这会触发上述所有计算


    # Features
    # 与之前描述的接口不同，Futures 是即将执行的(同步阻塞)，提交函数后立即开始计算
    print("\n\n\n-------------------------Features--------------------------")
    client = Client()
    
    def inc(x):
       return x + 1
    
    def add(x, y):
       return x + y
    
    a = client.submit(inc, 1)     # 任务立即开始
    b = client.submit(inc, 2)     # 任务立即开始
    c = client.submit(add, a, b)  # 任务立即开始
    
    print(c.result())                # 阻塞直到任务完成，然后收集结果


    # 调度
    # 生成任务图后，调度程序的工作就是执行它
    # 默认情况下，当您在 Dask 对象上调用 compute 时，Dask 使用计算机上的线程池并行运行计算
    # 如果您想要更多控制，请改用分布式调度程序
    # 尽管名称中有“分布式”，但分布式调度程序在单台和多台机器上都能工作很好, 将其视为“高级调度程序”
    print("\n\n\n-------------------------Schedule and Execute--------------------------")
    # dask.config.set(scheduler='process', num_workers=4)
    client = Client()
    print(client)
    # client = Client("<url-of-scheduler>")
    # print(client)


