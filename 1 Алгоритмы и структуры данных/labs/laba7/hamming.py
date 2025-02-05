import sys

def ceiled_log2(a):
    return 0 if a <= 0 else (a - 1).bit_length()

def is_power_of_two(a):
    return (a & (a - 1)) == 0 and a > 0

def decode(s):
    length = len(s)
    control_bits = ceiled_log2(length + 1)

    real_control_bitset = 0
    control_bitset = 0

    for i in range(1, length + 1):
        ch = s[i - 1]
        if ch == '0':
            continue

        if is_power_of_two(i):
            log_val = ceiled_log2(i)
            if log_val < control_bits:
                real_control_bitset |= (1 << log_val)
            continue

        j = i
        counter = 0
        while j > 0 and counter < control_bits:
            if j & 1:
                control_bitset ^= (1 << counter)
            counter += 1
            j >>= 1

    error_bit = real_control_bitset ^ control_bitset

    decoded_chars = []
    for i in range(1, length + 1):
        if is_power_of_two(i):
            continue
        ch = s[i - 1]
        if i == error_bit:
            # Инвертируем бит в случае обнаруженной ошибки
            ch = '0' if ch == '1' else '1'
        decoded_chars.append(ch)

    return ''.join(decoded_chars)

def main():
    input = sys.stdin.read().split()
    t = int(input[0])
    index = 1
    results = []
    for _ in range(t):
        s = input[index]
        index += 1
        decoded = decode(s)
        results.append(decoded)
    print('\n'.join(results))

if __name__ == "__main__":
    main()
