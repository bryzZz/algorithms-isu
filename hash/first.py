def hash(key):
    result = [0] * 8

    for char in key:
        s = ord(char)
        for j in range(7, 0, -1):
            bit = (s >> j) & 1
            result[j] = (bit + result[j]) % 2

    result = ''.join(map(str, result))
    result = bin(int(result, base=2))
    return result

print(hash('qwertyasd'))