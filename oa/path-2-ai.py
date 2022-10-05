
def make_timestamp(s):
    # timestr "05:30-0800" -> timestamp [530, 800]
    time1, time2 = s.split('-')
    time1_hour, time1_min = time1.split(':')
    time2_hour, time2_min = time2.split(':')
    return [int(time1_hour) * 100 + int(time1_min), int(time2_hour) * 100 + int(time2_min)]

def make_timestr(interval):
    # timestamp [530, 800] -> timestr "05:30-08:00"
    start = interval[0]
    start_hour = str(start//100)
    if len(start_hour) == 1:
        start_hour = '0' + start_hour 

    start_min = str(start%100)
    if len(start_min) == 1:
        start_min = '0' + start_min 

    end = interval[1]
    end_hour = str(end//100)
    if len(end_hour) == 1:
        end_hour = '0' + end_hour

    end_min = str(end%100)
    if len(end_min) == 1:
        end_min = '0' + end_min

    return start_hour + ":" + start_min + "-" + end_hour + ":" + end_min

print(make_timestr([1230, 2200]))

def f(data, n):
    '''
    data: [[[0, 530]], 
           [[0, 500], [800, 2200]], 
           [[0, 1230]]]
    '''
    res = list()
    person_num = len(data)


# 题目 input 为 list of list of string，与开会数量 n, 每个list of string 存储了一个员工的开会时间 (可能不止一个时间段),
# output 为找出 n 个, 至少两个人员工有空的时间安排会议，如有多个满足要求的时间，首先按照参与人数排列，其次按照时间早晚排列

n = 3  # 会议总数
print("\nn = \n" + str(n))
data = [["00:00-05:30"], 
        ["00:00-05:00", "08:00-22:00"], 
        ["00:00-12:30"]]
print("\ndata = \n" + str(data))

tran_data = list()
for meet_times in data:
    person_times = list()
    for meet_time in meet_times:
        person_times.append(make_timestamp(meet_time))

    tran_data.append(person_times)

print("\ntran_data = \n" + str(tran_data))

res = f(tran_data, n)
print("\nres = \n" + str(res))
# Expected output: ["05:30-08:00", "12:30-22:00", "22:00-24:00"]

