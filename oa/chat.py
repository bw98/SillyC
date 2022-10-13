import re

def chat(members, messages):
    user_set = set()
    for member in members:
        user_set.add(member)

    res = dict()

    for msg in messages:
        split_msg = re.split(',|\ ', msg)
        has_at = False
        for i in range(0, len(split_msg)):
            ids = set()
            if split_msg[i].startswith("@id"):
                ii = i
                while ii < len(split_msg):
                    if split_msg[ii].startswith("@id"):
                        idstr = split_msg[ii].split("@id")[1]
                        if idstr:
                            ids.add(idstr)

                    if split_msg[ii].startswith("id"):
                        idstr = split_msg[ii].split("id")[1]
                        if idstr:
                            ids.add(idstr)

                    ii += 1

                if ii > i:
                    i = ii

            for idstr in ids:
                if idstr not in res:
                    res[idstr] = 0
                else:
                    res[idstr] += 1

    
    return [x+'='+str(y) for x,y in res.items()]
                    


print("\n")

members = [ "id123", "id234", "id7", "id321" ]
messages = [ "This is an example with @id123,id234,id123 with 2 users",
             "Hey @id7 nice appro@ch! This is an example with 0 users",
             "This is an example with @id123,234 with 1 user" ];

print(chat(members, messages))
# 基于上面的例子正确输出应该是 ['123=2', '234=2', '7=1', '321=0']
# 必须出现 @ 与 id 才算是 message 的 id
# 同一个 message 里的多个 id 比如 1st message 中的 123 就只算一个



