from math import *

def arithmetic_encode_with_ranges(text):
    l = 0
    r = 1
    alphabet = '`abcdefghijklmnopqrstuvwxyz'
    freq = {i: 0 for i in alphabet}

    for char in text:
        if char in freq:
            freq[char] += 1
        else:
            pass

    for char in alphabet:
        if char != 'z':
            next_char = chr(ord(char) + 1)
            if next_char in freq:
                freq[next_char] += freq[char]
        freq[char] = freq[char] / len(text)

    for char in text:
        lower_bound = freq[chr(ord(char) - 1)] if char != '`' else 0
        upper_bound = freq[char]
        l, r = l + (r - l) * lower_bound, l + (r - l) * upper_bound
        if r - l < 1e-6:
            break

    return l

def Arithmetic_encode(text):
    return arithmetic_encode_with_ranges(text)

def answer(text):
    ans = Arithmetic_encode(text)
    print(f'{ans:.6f}')

input_string = input().strip()
if input_string:
    answer(input_string)
else:
    print("0.000000")
