import itertools

n = int(input())

def gray_code(i):
    g = str(i[0])
    for j in range(1, n):
        g += str(i[j - 1] ^ i[j])
    return g

def answer(i):
    res = gray_code(i)
    return res

for i in itertools.product([0, 1], repeat=n):
    result = answer(i)
    print(result)
