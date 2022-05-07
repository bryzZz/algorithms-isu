from datetime import datetime
import os

def find_duplicates(files: 'list[str]', hash_function: callable) -> 'list[str]':
    hashed_files = [hash_function(file) for file in files]
    dupes = [x for n, x in enumerate(hashed_files) if x in hashed_files[:n]]
    return dupes

def hash_CRC(str: str) -> int:
    h = 0
    for c in str:
        highorder = h & 0xf8000000
        h = h << 5
        h = h ^ (highorder >> 27)
        h = h ^ ord(c)
    return h

def hash_PJW(str: str) -> int:
    h = 0
    for c in str:
        h = (h << 4) + ord(c)
        g = h & 0xf0000000
        if (g != 0):
            h = h ^ (g >> 24)
            h = h ^ g
    return h

def hash_BUZ(str: str) -> int:
    # Думаю это можно принять за массив случайных значений
    # Я понимаю что возможно с таким массивом можно поиграть и найти более оптимальные значения
    # для конкретной ситуации но я слишком ленивый чтобы это делать))
    def R(v):
        return hash(v)
    h = 0
    for c in str:
        highorder = h & 0x80000000
        h = h << 1
        h = h ^ (highorder >> 31)
        h = h ^ R(ord(c))
    return h

def read_text_file(file_path):
    with open(file_path, 'r') as f:
        return f.read()

dir_path = 'out'
files = []

for file in os.listdir(dir_path):
    if file.endswith(".txt"):
        file_path = os.path.join(dir_path, file)
        content = read_text_file(file_path).replace('\n','')
        files.append(content)

start_time = datetime.now()
print('hash_PJW: ', len(find_duplicates(files, hash_PJW)), 'execution time: ', datetime.now() - start_time)
start_time = datetime.now()
print('hash_CRC: ', len(find_duplicates(files, hash_CRC)), 'execution time: ', datetime.now() - start_time)
start_time = datetime.now()
print('hash_BUZ: ', len(find_duplicates(files, hash_BUZ)), 'execution time: ', datetime.now() - start_time)
start_time = datetime.now()
print('python native hash: ', len(find_duplicates(files, hash)), 'execution time: ', datetime.now() - start_time)