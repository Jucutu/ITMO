string = input()

current = ''
words = {"": 0}

for i in string:
    if current + i in words:
        current += i
    else:
        words[current + i] = len(words)
        print(words[current], i)
        current = ''

if current:
    if current in words:
        print(words[current], '\0')
    else:
        ans = current[-1]
        print(words[current[:-1]], ans)
