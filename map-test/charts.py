import matplotlib.pyplot as plt

dataCpp = input().split()
dataPy = input().split()

plt.subplot(2, 2, 1)
plt.grid(True)
plt.xlabel('Count', color='gray')
plt.ylabel('Size', color='gray')
plt.plot(list(map(float, dataCpp[::3])), list(map(float, dataCpp[1::3])), 'ro-.')
plt.title('C++ map size in time')

plt.subplot(2, 2, 2)
plt.grid(True)
plt.xlabel('Count', color='gray')
plt.ylabel('Size', color='gray')
plt.plot(list(map(float, dataPy[::3])), list(map(float, dataPy[1::3])), 'ro--', color="green")
plt.title('Python dict size in time')

plt.subplot(2, 2, 3)
plt.grid(True)
plt.xlabel('Count', color='gray')
plt.ylabel('Time', color='gray')
plt.plot(list(map(float, dataCpp[::3])), list(map(float, dataCpp[2::3])), 'ro-.')
plt.title('C++ map count in time')

plt.subplot(2, 2, 4)
plt.grid(True)
plt.xlabel('Count', color='gray')
plt.ylabel('Time', color='gray')
plt.plot(list(map(float, dataPy[::3])), list(map(float, dataPy[2::3])), 'ro--', color="green")
plt.title('Python dict count in time')

plt.show()