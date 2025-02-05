def arithmetic_encode_with_ranges(text):
    l = 0
    r = 1
    alphabet = '`abcdefghijklmnopqrstuvwxyz'
    freq = {i: 0 for i in alphabet}

    for i in string:
        freq[i] += 1

    for i in freq:
        if i != 'z':
            freq[chr(ord(i) + 1)] += freq[i]
        freq[i] = freq[i] / len(string)

    for i in text:
        l = (r - l) * freq[chr(ord(i) - 1)] + l
        r = (rc - l) * freq[i] + l

    return l


input_string = input().strip()
if input_string:
    result = arithmetic_encode_with_ranges(string)
    print(f'{result:.6}')
else:
    print(0)
