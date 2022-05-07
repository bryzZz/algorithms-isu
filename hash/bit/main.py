with open('out.txt', "r") as f:
    len = 0
    errorsCount = 0
    for line in f.readlines():
        numbers = list(map(int, line.split()))
        res = 0

        for num in numbers[:4]:
            s = bin(num)[2:]
            res += s.count('1')

        res = res % 2

        if res != numbers[4]:
            errorsCount += 1
        
        len += 1

    print(100 * (errorsCount / len))