import numpy as np
import matplotlib.pyplot as plt
titles=["Metoda Picarda","Iteracja Newtona","Niejawna RK2"]
files=["picard","newton","rk2"]

for i in range(len(files)):
    fig = plt.figure()
    plt.title(titles[i])

    file = files[i]
    data = np.loadtxt(file+".txt")


    x = data[:, 0]
    y = data[:, 1]
    y_v = data[:, 2]

    plt.plot(x, y, 'r-', label='u(t)')
    plt.plot(x, y_v, 'b-', label='v(t)')

    l1 = plt.legend()

    plt.xlabel('t')
    plt.ylabel('u(t),v(t)')

    plt.savefig("zad1"+files[i]+".png")
    #plt.show()