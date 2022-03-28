import matplotlib.pyplot as plt

data = input().split()

x = list(map(float, data[::2]))
y = list(map(float, data[1::2]))
yr = [i * 4 for i in x]

plt.plot(x, y)
plt.plot(x, yr)
plt.show()