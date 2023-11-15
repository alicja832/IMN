import numpy as np
import matplotlib.pyplot as plt

method=["rk2","trapez"]
tol=[10e-5,10e-2]
titles=['v(t)','x(t)','dt(t)','v(x)']
files=[["rk20.000100.txt","rk20.100000.txt"],["trapez0.000100.txt","trapez0.100000.txt"]]
colors=['m','c']



z=0
for i in files:
    for k in range(len(titles)):
        plt.figure()
        data = np.loadtxt(i[0])
        if k==3:
            x = data[:, 2]
            y=  data[:, 1]
        else:
            x = data[:, 0]
            y= data[:, k+1]
        plt.title(titles[k])
        plt.plot(x,y,colors[0]+'-',label=tol[0])

        data = np.loadtxt(i[1])
        if k==3:
            x = data[:, 2]
            y=  data[:, 1]
        else:
            x = data[:, 0]
            y= data[:, k+1]
        plt.title(titles[k])
        plt.plot(x,y,colors[1]+'-',label=tol[1])
        plt.legend()
        plt.savefig("lab3"+method[z]+titles[k]+".png")
    z+=1
   