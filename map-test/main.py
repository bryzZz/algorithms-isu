import sys
import time

test = {}
s = 0

for i in range(5):
    s = 10 ** i
    test.clear()

    t = time.time()
    for j in range(s):
        test[j] = j

    print(str(s) + ' ' + str(sys.getsizeof(test)) + ' ' + str(time.time()-t), end=' ')
print()