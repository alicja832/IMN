import numpy as np
import matplotlib.pyplot as plt

method=["RK2","trapezow"]
labels=['v(t)','x(t)','dt(t)','v(x)']
files=[["rk20.000010.txt","rk20.010000.txt"],["trapez0.000010.txt","trapez0.010000.txt"]]
colors=['m','c']



z=0
for i in files:
    for k in range(len(labels)):
        plt.figure()
        data = np.loadtxt(i[0])
        if k==3:
            x = data[:, 2]
            y=  data[:, 1]
        else:
            x = data[:, 0]
            y= data[:, k+1]

        plt.plot(x,y,colors[0]+'-',label="TOL="+str(10e-6))
        if k==2:
            plt.scatter(x, y,color= colors[0], marker='o',s=20)
        data = np.loadtxt(i[1])
        if k==3:
            x = data[:, 2]
            y=  data[:, 1]
            plt.xlabel('x')
        else:
            x = data[:, 0]
            y= data[:, k+1]
            plt.xlabel('t')
     
        plt.title("Metoda "+method[z])
       
        plt.ylabel(labels[k])
        plt.plot(x,y,colors[1]+'-',label="TOL="+str(10e-3))
        if k==2:
            plt.scatter(x, y, color=colors[1], marker='o',s=20)
        plt.legend()
        plt.savefig(method[z]+labels[k]+".png")
    z+=1
   