from itertools import permutations

key = "asdf"

def hash(key):
    result = ord(key[0])
    for symb in key[1:]:
        result = result or ord(symb)
    return result

# def hash(key):
#     result = [0] * 8

#     for char in key:
        # s = ord(char)
        # for j in range(7, 0, -1):
        #     bit = (s >> j) & 1
        #     result[j] = (bit + result[j]) % 2

#     result = ''.join(map(str, result))
#     result = bin(int(result, base=2))
#     return result

# print(bin(hash(key)))

hashes = []
for perm in permutations(key, len(key)):
    s = "".join(perm)
    h = hash(s)
    hashes.append(h)
    print(f"{s} - {h}")

print(hashes)
print(len(hashes) - len(set(hashes)))