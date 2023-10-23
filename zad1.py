import numpy as np
import matplotlib.pyplot as plt


t=["0.01","0.10","1."]
zad=["","1.2:","1.3:"]
zera=["","0","0"]
files=[]
colors=["bo","ro","go"]
for i in zad:
    kl=0
    for j in t:
        files.append("wynik"+i+j+zera[kl]+"0000.txt")
        kl+=1
for i in files:

    data = np.loadtxt(i)

    x = data[:, 0]
    y_an = data[:, 2]
    plt.plot(x, y_an, 'k-', lw=2, label='analityczne')

    for j in range(3):
        y = data[:, 1]
        plt.plot(x, y, colors[j], label='dt='+t[j])

        file = "wynik0.100000.txt"
        data = np.loadtxt(file)

        x = data[:, 0]
        y = data[:, 1]
        y_an = data[:, 2]

        plt.plot(x, y, 'ro', label='dt=0.1')

        file = "wynik1.000000.txt"
        data = np.loadtxt(file)

        x = data[:, 0]
        y = data[:, 1]
        y_an = data[:, 2]

        plt.plot(x, y, 'go', label='dt=1')


l1 = plt.legend()

plt.xlabel('t')
plt.ylabel('y(t)')

plt.savefig("zad1.png",bbox_inches='tight', transparent=True)

fig = plt.figure()
x = data[:, 0]
y_num=data[:,3]
plt.plot(x, y_num, 'g-', lw=2, label='dt=1')

file = "wynik0.100000.txt"
data = np.loadtxt(file)
x = data[:, 0]
y_num=data[:,3]
plt.plot(x, y_num, 'r-', lw=2, label='dt=0.1')

file = "wynik0.010000.txt"
data = np.loadtxt(file)
x = data[:, 0]
y_num=data[:,3]

plt.plot(x, y_num, 'b-', lw=2, label='dt=0.01')
plt.xlabel('t')
plt.ylabel('ynum(t)-ydok(t)')

l1 = plt.legend()
plt.savefig("zad1a.png",bbox_inches='tight', transparent=True)
#plt.show()